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
      // is is not best idea projection establish connection in constructor
      // but lets keep it simple
      OpenConnection();

      // thats why it is a bad idea
      if (Connection.State != ConnectionState.Open)
      {
        string message = "Не могу открыть подключение к базе: " + Connection.State;
        throw new IOException(message);
      }

      Books = new List<Book>();
      Authors = new List<Author>();
      Categories = new List<Category>();
    }

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

      if (categories != null)
        foreach (var category in categories)
          newBook.AddCategory(category);

      if (authors != null)
        foreach (var author in authors)
          newBook.AddAuthor(author);  

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
        // remove from mapping
        DeleteFrom(Db.TableBook2Author, "AuthorId=" + item.Id);

        IDbCommand deleteAuthor = new MySqlCommand(Db.AuthorDelete,
          (MySqlConnection) Connection);

        item.BindId(deleteAuthor, Db.AuthorIdParam);
        deleteAuthor.ExecuteNonQuery();

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
        // remove from mapping
        DeleteFrom(Db.TableBook2Category, "CategoryId=" + item.Id);

        IDbCommand deleteCategory = new MySqlCommand(Db.CategoryDelete,
          (MySqlConnection) Connection);

        item.BindId(deleteCategory, Db.CategoryIdParam);
        deleteCategory.ExecuteNonQuery();
        
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
        // TODO updating everything is suboptimal

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

      ReadBook2Catetory();
      ReadBook2Author();

      return this;
    }

#endregion

#region Read data

    private void ReadBook2Author()
    {
      Action<IDataReader> readMapping = reader =>
      {
        uint bookId = Convert.ToUInt32(reader.GetInt32(0));
        uint authorId = Convert.ToUInt32(reader.GetInt32(1));
        AllBooks.Find(b => b.Id == bookId).Add(AllAuthors.Find(a => a.Id == authorId));
      };

      Read(Db.SelectAllFrom + Db.TableBook2Author, readMapping);
    }

    private void ReadBook2Catetory()
    {
      Action<IDataReader> readMapping = reader =>
      {
        uint bookId = Convert.ToUInt32(reader.GetInt32(0));
        uint categoryId = Convert.ToUInt32(reader.GetInt32(1));
        AllBooks.Find(b => b.Id == bookId).Add(AllCategories.Find(a => a.Id == categoryId));
      };

      Read(Db.SelectAllFrom + Db.TableBook2Category, readMapping);
    }

    private void ReadCategories()
    {
      Categories.Clear();
      Action<IDataReader> readCategory = reader =>
      {
        var newCategory = new Category(this);
        newCategory.PopulateFromReader(reader);
        Categories.Add(newCategory);
      };
      Read(Db.CategorySelect, readCategory);
    }

    private void ReadKeyword()
    {
      Action<IDataReader> readKeyword = reader =>
      {
        var id = Convert.ToUInt32(reader.GetInt32(Db.KeywordBookIdIndex));
        // there must not exists any id when there is no book for it, so we don't check for null
        Books.Find(b => b.Id == id).Add(reader.GetString(Db.KeywordNameIndex));
      };
 
      Read(Db.SelectAllFrom + Db.TableKeywords, readKeyword);
    }

    private void ReadAuthors()
    {
      Authors.Clear();

      Action<IDataReader> readAuthor = reader =>
      {
        var newAuthor = new Author(this);
        newAuthor.PopulateFromReader(reader);
        Authors.Add(newAuthor);
      };

      Read(Db.AuthorSelect, readAuthor);
    }

    private void ReadBooks()
    {
      Books.Clear();

      Action<IDataReader> readBook = reader =>
      {
                var newBook = new Book(this);
                newBook.PopulateFromReader(reader);
                Books.Add(newBook);
      };

      Read(Db.BookSelect, readBook);
    }

#endregion

#region CommonUtilities

    internal void Read(string selectStmt, Action<IDataReader> readAction)
    {
      IDbCommand readCommand = 
        new MySqlCommand(selectStmt, (MySqlConnection) Connection);

      IDataReader reader = readCommand.ExecuteReader();
      while (reader.Read())
        readAction(reader);
      reader.Close();
    }

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

    private uint LastInsertId()
    {
      IDbCommand lastIdCommand = new MySqlCommand(
        Db.SelectLastInsertId,
        (MySqlConnection)Connection);

      return Convert.ToUInt32(lastIdCommand.ExecuteScalar());
    }

    private long SelectCountFromTable(string tableName)
    {
      IDbCommand selectCountCommand = new MySqlCommand(
        Db.SelectCountFrom + tableName,
        (MySqlConnection)Connection);

      return (long)selectCountCommand.ExecuteScalar();
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

    public IDbConnection Connection { get; private set; }

    private List<Book> Books { get; set; }
    private List<Author> Authors { get; set; }
    private List<Category> Categories { get; set; }
  }
}