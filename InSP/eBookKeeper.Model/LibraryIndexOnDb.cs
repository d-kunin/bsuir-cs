using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class LibraryIndexOnDb : ILibraryIndex, IDisposable
  {
    public LibraryIndexOnDb()
    {
      // TODO: is is not best idea to establish connection in constructor
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

    public bool Delete(Book item)
    {
      if (Books.Remove(item))
      {
        IDbCommand deleteBook =
          new MySqlCommand(DbConsts.BookDelete, (MySqlConnection) Connection);

        DbConsts.BookIdParam.Value = item.Id;
        deleteBook.Parameters.Add(DbConsts.BookIdParam);
        deleteBook.ExecuteNonQuery();

        //delete from mappings
        DeleteFromMappingTable(DbConsts.TableBook2Author, "BookId=" + item.Id);
        DeleteFromMappingTable(DbConsts.TableBook2Category, "BookId=" + item.Id);

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
        new MySqlCommand(DbConsts.BookInsert, (MySqlConnection) Connection);

      var newBook = new Book {Title = title};


      newBook.BindTitle(insertBookCommand, DbConsts.BookTitleParam);
      newBook.BindDescription(insertBookCommand, DbConsts.BookDescriptionParam);
      newBook.BindEdition(insertBookCommand, DbConsts.BookEditionParam);


      insertBookCommand.ExecuteNonQuery();

      newBook.Id = LastInsertId();
      Books.Insert(0, newBook);

      //TODO add mapping to author, key, category

      return newBook;
    }

    public long NumberOfBooks()
    {
      return SelectCountFromTable(DbConsts.TableBooks);
    }

    public List<Book> AllBooks
    {
      get { return Books; }
    }

    public bool Delete(Author item)
    {
      if (AllAuthors.Remove(item))
      {
        IDbCommand deleteAuthor = new MySqlCommand(DbConsts.AuthorDelete,
          (MySqlConnection) Connection);

        item.BindId(deleteAuthor, DbConsts.AuthorIdParam);
        deleteAuthor.ExecuteNonQuery();
        // remove from mapping
        DeleteFromMappingTable(DbConsts.TableBook2Author, "AuthorId=" + item.Id);

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
      IDbCommand insertAuthor = new MySqlCommand(DbConsts.AuthorInsert,
        (MySqlConnection) Connection);

      var newAuthor = new Author {Name = name};

      newAuthor.BindName(insertAuthor, DbConsts.AuthorNameParam);

      insertAuthor.ExecuteNonQuery();
      newAuthor.Id = LastInsertId();

      AllAuthors.Insert(0, newAuthor);

      return newAuthor;
    }

    public long NumberOfAuthors()
    {
      return SelectCountFromTable(DbConsts.TableAuthors);
    }

    public List<Author> AllAuthors
    {
      get { return Authors; }
    }

    public bool Delete(Category item)
    {
      if (Categories.Remove(item))
      {
        IDbCommand deleteCategory = new MySqlCommand(DbConsts.CategoryDelete,
          (MySqlConnection) Connection);

        item.BindId(deleteCategory, DbConsts.CategoryIdParam);
        deleteCategory.ExecuteNonQuery();
        // remove from mapping
        DeleteFromMappingTable(DbConsts.TableBook2Category, "CategoryId=" + item.Id);

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
      IDbCommand insertCategory = new MySqlCommand(DbConsts.CategoryInsert,
        (MySqlConnection) Connection);

      var newCategory = new Category {Name = name};

      newCategory.BindName(insertCategory, DbConsts.CategoryNameParam);
      insertCategory.ExecuteNonQuery();

      newCategory.Id = LastInsertId();

      Categories.Insert(0, newCategory);
      return newCategory;
    }

    public long NumberOfCategories()
    {
      return SelectCountFromTable(DbConsts.TableCategories);
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

    private void OpenConnection()
    {
      var builder = new MySqlConnectionStringBuilder();

      builder.Server = "ec2-54-218-67-170.us-west-2.compute.amazonaws.com";
      // bsuir is ours everything
      builder.UserID = "bsuir";
      builder.Password = "bsuir";
      builder.Database = "bsuir";
      builder.Port = 3306;

      Connection = new MySqlConnection(builder.ToString());
      Connection.Open();
    }

    private void Book2Author()
    {
      IDbCommand selectBook2Author =
        new MySqlCommand(DbConsts.SelectBase + DbConsts.TableBook2Author,
          (MySqlConnection) Connection);

      IDataReader reader = selectBook2Author.ExecuteReader();
      while (reader.Read())
      {
        uint bookId = Convert.ToUInt32(reader.GetInt32(0));
        uint authorId = Convert.ToUInt32(reader.GetInt32(1));

        AllBooks.Find(b => b.Id == bookId).Authors.Add(AllAuthors.Find(a => a.Id == authorId));
      }
      reader.Close();
    }

    private void Book2Catetory()
    {
      IDbCommand selectBook2Category =
        new MySqlCommand(DbConsts.SelectBase + DbConsts.TableBook2Category,
          (MySqlConnection) Connection);

      IDataReader reader = selectBook2Category.ExecuteReader();
      while (reader.Read())
      {
        uint bookId = Convert.ToUInt32(reader.GetInt32(0));
        uint categoryId = Convert.ToUInt32(reader.GetInt32(1));

        AllBooks.Find(b => b.Id == bookId).Categories.Add(AllCategories.Find(a => a.Id == categoryId));
      }
      reader.Close();
    }

    private void ReadCategories()
    {
      Categories.Clear();
      IDbCommand selectCategories =
        new MySqlCommand(DbConsts.CategorySelect, (MySqlConnection) Connection);

      IDataReader reader = selectCategories.ExecuteReader();
      while (reader.Read())
      {
        var newCategory = new Category();
        newCategory.PopulateFromReader(reader);
        Categories.Add(newCategory);
      }
      reader.Close();
    }


    private void ReadKeyword()
    {
      IDbCommand selectKeywords =
        new MySqlCommand(DbConsts.KeywordSelect, (MySqlConnection) Connection);

      IDataReader reader = selectKeywords.ExecuteReader();
      while (reader.Read())
      {
        var id = Convert.ToUInt32(reader.GetInt32(DbConsts.KeywordBookIdIndex));
        // there must not exists any id when there is no book for it, so we don't check for null
        Books.Find(b => b.Id == id).Keywords.Add(reader.GetString(DbConsts.KeywordNameIndex));
      }
      reader.Close();
    }

    private void ReadAuthors()
    {
      Authors.Clear();
      IDbCommand selectAuthors =
        new MySqlCommand(DbConsts.AuthorSelect, (MySqlConnection) Connection);

      IDataReader reader = selectAuthors.ExecuteReader();
      while (reader.Read())
      {
        var newAuthor = new Author();
        newAuthor.PopulateFromReader(reader);
        Authors.Add(newAuthor);
      }
      reader.Close();
    }

    private void ReadBooks()
    {
      Books.Clear();
      IDbCommand selectBooks =
        new MySqlCommand(DbConsts.BookSelect, (MySqlConnection) Connection);

      IDataReader reader = selectBooks.ExecuteReader();
      while (reader.Read())
      {
        var newBook = new Book();
        newBook.PopulateFromReader(reader);
        Books.Add(newBook);
      }
      reader.Close();
    }

    public void DropTables()
    {
      // drop mappings first
      var tables = new ArrayList
      {
        DbConsts.TableBook2Author,
        DbConsts.TableBook2Category,
        DbConsts.TableKeywords,
        DbConsts.TableBooks,
        DbConsts.TableAuthors,
        DbConsts.TableCategories
      };

      foreach (object table in tables)
      {
        IDbCommand dropTable = new MySqlCommand(DbConsts.DropTable + table,
          (MySqlConnection) Connection);
        dropTable.ExecuteNonQuery();
      }
    }

    public void InitTables()
    {
      // init books, authors, categories
      IDbCommand createTablesCommand =
        new MySqlCommand(DbConsts.CreateTables,
          (MySqlConnection) Connection);

      createTablesCommand.ExecuteNonQuery();

      // init mappings
      IDbCommand createMappingCommand =
        new MySqlCommand(DbConsts.CreateMappingTables,
          (MySqlConnection) Connection);

      createMappingCommand.ExecuteNonQuery();
    }


    private uint LastInsertId()
    {
      IDbCommand lastIdCommand = new MySqlCommand(
        DbConsts.SelectLastInsertId,
        (MySqlConnection) Connection);

      return Convert.ToUInt32(lastIdCommand.ExecuteScalar());
    }

    private long SelectCountFromTable(string tableName)
    {
      IDbCommand selectCountCommand = new MySqlCommand(
        DbConsts.SelectCountFrom + tableName,
        (MySqlConnection) Connection);

      return (long) selectCountCommand.ExecuteScalar();
    }

    private void DeleteFromMappingTable(string mappingTable, string where)
    {
      IDbCommand deleteCommand =
        new MySqlCommand("DELETE FROM " + mappingTable + " WHERE " + where,
          (MySqlConnection) Connection);

      deleteCommand.ExecuteNonQuery();
    }
  }
}