using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Windows.Media.Animation;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class LibraryIndexOnDb : ILibraryIndex, IDisposable
  {
    public LibraryIndexOnDb()
    {
      // TODO: is is not best idea projection establish connection in constructor
      OpenConnection();

      // Exception in constructor =(
      if (Connection.State != ConnectionState.Open)
      {
        string message = "Не могу открыть подключение к базе: " + Connection.State;
        throw new IOException(message);
      }

      Books = new List<Book>();
      Authors = new List<Author>();
      Categories = new List<Category>();
    }

    private List<Book> Books { get; set; }
    private List<Author> Authors { get; set; }
    private List<Category> Categories { get; set; }

    public IDbConnection Connection { get; private set; }

    public void Dispose()
    {
      Connection.Close();
    }

    private void OpenConnection()
    {
      var builder = new MySqlConnectionStringBuilder
      {
        Server = "ec2-54-218-67-170.us-west-2.compute.amazonaws.com",
        UserID = "bsuir",
        Password = "bsuir",
        Database = "bsuir",
        Port = 3306
      };

      Connection = new MySqlConnection(builder.ToString());
      Connection.Open();
    }

#region LibraryInterface

    public bool Delete(Book item)
    {
      if (Books.Remove(item))
      {
        //delete from mappings
        DeleteFrom(Db.TableBook2Author, "BookId=" + item.Id);
        DeleteFrom(Db.TableBook2Category, "BookId=" + item.Id);
        DeleteFrom(Db.TableKeywords, "BookId=" + item.Id);

        IDbCommand deleteBook =
          new MySqlCommand(Db.BookDelete, (MySqlConnection) Connection);

        Db.BookIdParam.Value = item.Id;
        deleteBook.Parameters.Add(Db.BookIdParam);
        deleteBook.ExecuteNonQuery();

        return true;
      }
      return false;
    }

    public List<Book> Find(Predicate<Book> predicate)
    {
      return Books.ToList().FindAll(predicate);
    }

    public Book CreateBook(string title, List<Author> authors = null, List<Category> categories = null)
    {
      IDbCommand insertBookCommand =
        new MySqlCommand(Db.BookInsert, (MySqlConnection) Connection);

      var newBook = new Book(this) {Title = title};


      newBook.BindTitle(insertBookCommand, Db.BookTitleParam);
      newBook.BindDescription(insertBookCommand, Db.BookDescriptionParam);
      newBook.BindEdition(insertBookCommand, Db.BookEditionParam);


      insertBookCommand.ExecuteNonQuery();

      newBook.Id = LastInsertId();
      Books.Insert(0, newBook);

      //TODO add mapping projection author, key, category

      return newBook;
    }

    public long NumberOfBooks()
    {
      return SelectCountFromTable(Db.TableBooks);
    }

    public List<Book> AllBooks
    {
      get { return Books; }
    }

    public bool Delete(Author item)
    {
      if (AllAuthors.Remove(item))
      {
        IDbCommand deleteAuthor = new MySqlCommand(Db.AuthorDelete,
          (MySqlConnection) Connection);

        item.BindId(deleteAuthor, Db.AuthorIdParam);
        deleteAuthor.ExecuteNonQuery();
        // remove from mapping
        DeleteFrom(Db.TableBook2Author, "AuthorId=" + item.Id);

        return true;
      }
      return false;
    }

    public List<Author> Find(Predicate<Author> predicate)
    {
      return AllAuthors.FindAll(predicate);
    }

    public Author CreateAuthor(string name)
    {
      IDbCommand insertAuthor = new MySqlCommand(Db.AuthorInsert,
        (MySqlConnection) Connection);

      var newAuthor = new Author(this) {Name = name};

      newAuthor.BindName(insertAuthor, Db.AuthorNameParam);

      insertAuthor.ExecuteNonQuery();
      newAuthor.Id = LastInsertId();

      AllAuthors.Insert(0, newAuthor);

      return newAuthor;
    }

    public long NumberOfAuthors()
    {
      return SelectCountFromTable(Db.TableAuthors);
    }

    public List<Author> AllAuthors
    {
      get { return Authors; }
    }

    public bool Delete(Category item)
    {
      if (Categories.Remove(item))
      {
        IDbCommand deleteCategory = new MySqlCommand(Db.CategoryDelete,
          (MySqlConnection) Connection);

        item.BindId(deleteCategory, Db.CategoryIdParam);
        deleteCategory.ExecuteNonQuery();
        // remove from mapping
        DeleteFrom(Db.TableBook2Category, "CategoryId=" + item.Id);

        return true;
      }
      return false;
    }

    public List<Category> Find(Predicate<Category> predicate)
    {
      return Categories.FindAll(predicate);
    }

    public Category CreateCategory(string name)
    {
      IDbCommand insertCategory = new MySqlCommand(Db.CategoryInsert,
        (MySqlConnection) Connection);

      var newCategory = new Category(this) {Name = name};

      newCategory.BindName(insertCategory, Db.CategoryNameParam);
      insertCategory.ExecuteNonQuery();

      newCategory.Id = LastInsertId();

      Categories.Insert(0, newCategory);
      return newCategory;
    }

    public long NumberOfCategories()
    {
      return SelectCountFromTable(Db.TableCategories);
    }

    public List<Category> AllCategories
    {
      get { return Categories; }
    }

    public bool Save()
    {
      IDbTransaction transaction = Connection.BeginTransaction();
      try
      {
        // TODO updating everyting is suboprimal

        foreach (Book book in Books)
          book.Update(Connection);

        foreach (Category category in Categories)
          category.Update(Connection);

        foreach (Author author in Authors)
          author.Update(Connection);
      }
      finally
      {
        transaction.Commit();
      }

      return true;
    }

    public ILibraryIndex Restore()
    {
      InitTables();

      ReadBooks();
      ReadAuthors();
      ReadCategories();
      ReadKeyword();

      Book2Catetory();
      Book2Author();

      return this;
    }

#endregion

#region Read data

    private void Book2Author()
    {
      IDbCommand selectBook2Author =
        new MySqlCommand(Db.SelectBase + Db.TableBook2Author,
          (MySqlConnection) Connection);

      IDataReader reader = selectBook2Author.ExecuteReader();
      while (reader.Read())
      {
        uint bookId = Convert.ToUInt32(reader.GetInt32(0));
        uint authorId = Convert.ToUInt32(reader.GetInt32(1));

        AllBooks.Find(b => b.Id == bookId).Add(AllAuthors.Find(a => a.Id == authorId));
      }
      reader.Close();
    }

    private void Book2Catetory()
    {
      IDbCommand selectBook2Category =
        new MySqlCommand(Db.SelectBase + Db.TableBook2Category,
          (MySqlConnection) Connection);

      IDataReader reader = selectBook2Category.ExecuteReader();
      while (reader.Read())
      {
        uint bookId = Convert.ToUInt32(reader.GetInt32(0));
        uint categoryId = Convert.ToUInt32(reader.GetInt32(1));

        AllBooks.Find(b => b.Id == bookId).Add(AllCategories.Find(a => a.Id == categoryId));
      }
      reader.Close();
    }

    private void ReadCategories()
    {
      Categories.Clear();
      IDbCommand selectCategories =
        new MySqlCommand(Db.CategorySelect, (MySqlConnection) Connection);

      IDataReader reader = selectCategories.ExecuteReader();
      while (reader.Read())
      {
        var newCategory = new Category(this);
        newCategory.PopulateFromReader(reader);
        Categories.Add(newCategory);
      }
      reader.Close();
    }

    private void ReadKeyword()
    {
      IDbCommand selectKeywords =
        new MySqlCommand(Db.KeywordSelect, (MySqlConnection) Connection);

      IDataReader reader = selectKeywords.ExecuteReader();
      while (reader.Read())
      {
        var id = Convert.ToUInt32(reader.GetInt32(Db.KeywordBookIdIndex));
        // there must not exists any id when there is no book for it, so we don't check for null
        Books.Find(b => b.Id == id).Add(reader.GetString(Db.KeywordNameIndex));
      }
      reader.Close();
    }

    private void ReadAuthors()
    {
      Authors.Clear();
      IDbCommand selectAuthors =
        new MySqlCommand(Db.AuthorSelect, (MySqlConnection) Connection);

      IDataReader reader = selectAuthors.ExecuteReader();
      while (reader.Read())
      {
        var newAuthor = new Author(this);
        newAuthor.PopulateFromReader(reader);
        Authors.Add(newAuthor);
      }
      reader.Close();
    }

    private void ReadBooks()
    {
      Books.Clear();
      IDbCommand selectBooks =
        new MySqlCommand(Db.BookSelect, (MySqlConnection) Connection);

      IDataReader reader = selectBooks.ExecuteReader();
      while (reader.Read())
      {
        var newBook = new Book(this);
        newBook.PopulateFromReader(reader);
        Books.Add(newBook);
      }
      reader.Close();
    }

#endregion

#region MapData

    internal void InsertInto(string tableName, string projection, string values)
    {
      IDbCommand insertCommand =
        new MySqlCommand("INSERT INTO " + tableName + " (" + projection + ") VALUE (" + values + ")",
          (MySqlConnection) Connection);

      insertCommand.ExecuteNonQuery();
    }

    internal void DeleteFrom(string mappingTable, string where)
    {
      IDbCommand deleteCommand =
        new MySqlCommand("DELETE FROM " + mappingTable + " WHERE " + where,
          (MySqlConnection)Connection);

      deleteCommand.ExecuteNonQuery();
    }

#endregion

    public void DropTables()
    {
      // drop mappings first
      var tables = new ArrayList
      {
        Db.TableBook2Author,
        Db.TableBook2Category,
        Db.TableKeywords,
        Db.TableBooks,
        Db.TableAuthors,
        Db.TableCategories
      };

      foreach (object table in tables)
      {
        IDbCommand dropTable = new MySqlCommand(Db.DropTable + table,
          (MySqlConnection) Connection);
        dropTable.ExecuteNonQuery();
      }
    }

    public void InitTables()
    {
      // init books, authors, categories
      IDbCommand createTablesCommand =
        new MySqlCommand(Db.CreateTables,
          (MySqlConnection) Connection);

      createTablesCommand.ExecuteNonQuery();

      // init mappings
      IDbCommand createMappingCommand =
        new MySqlCommand(Db.CreateMappingTables,
          (MySqlConnection) Connection);

      createMappingCommand.ExecuteNonQuery();
    }


    private uint LastInsertId()
    {
      IDbCommand lastIdCommand = new MySqlCommand(
        Db.SelectLastInsertId,
        (MySqlConnection) Connection);

      return Convert.ToUInt32(lastIdCommand.ExecuteScalar());
    }

    private long SelectCountFromTable(string tableName)
    {
      IDbCommand selectCountCommand = new MySqlCommand(
        Db.SelectCountFrom + tableName,
        (MySqlConnection) Connection);

      return (long) selectCountCommand.ExecuteScalar();
    }

  }
}