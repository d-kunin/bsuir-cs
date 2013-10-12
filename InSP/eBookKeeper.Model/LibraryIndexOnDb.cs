using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class LibraryIndexOnDb : ILibraryIndex
  {
    public LibraryIndexOnDb()
    {
      // TODO: is is not best idea to establish connection in constructor

      MySqlConnectionStringBuilder builder = new MySqlConnectionStringBuilder();

      builder.Server = "ec2-54-218-67-170.us-west-2.compute.amazonaws.com";
      // bsuir is ours everything
      builder.UserID = "bsuir";
      builder.Password = "bsuir";
      builder.Database = "bsuir";
      builder.Port = 3306;

      Connection = new MySqlConnection(builder.ToString());
      Connection.Open();

      if (Connection.State != ConnectionState.Open)
      {
        var message = "Не могу открыть подключение к базе: " + Connection.State;
        throw new IOException(message);
      }

      Books = new List<Book>();
    }


    public List<Book> Books { get; set; }

    public IDbConnection Connection { get; private set; }

    public bool Delete(Book item)
    {
      throw new NotImplementedException();
    }

    public List<Book> Find(Predicate<Book> predicate)
    {
      return Books.ToList().FindAll(predicate);
    }

    public Book CreateBook(string title, List<Author> authors = null, List<Category> categories = null)
    {
      IDbCommand insertBookCommand = 
        new MySqlCommand(DbConsts.BookInsert, (MySqlConnection) Connection);

      Book newBook = new Book();
      newBook.Edition = 1;
      newBook.Title = title;
      newBook.Description = "";
      
      DbConsts.BookTitleParam.Value = newBook.Title;
      DbConsts.BookEditionParam.Value = newBook.Edition;
      DbConsts.BookDescriptionParam.Value = newBook.Description;

      insertBookCommand.Parameters.Add(DbConsts.BookTitleParam);
      insertBookCommand.Parameters.Add(DbConsts.BookDescriptionParam);
      insertBookCommand.Parameters.Add(DbConsts.BookEditionParam);

      insertBookCommand.ExecuteNonQuery();
      newBook.Id = LastInsertId();

      //TODO add mapping 

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
      throw new NotImplementedException();
    }

    public List<Author> Find(Predicate<Author> predicate)
    {
      throw new NotImplementedException();
    }

    public Author CreateAuthor(string name)
    {
      throw new NotImplementedException();
    }

    public long NumberOfAuthors()
    {
      return SelectCountFromTable(DbConsts.TableAuthors);
    }

    public List<Author> AllAuthors
    {
      get { throw new NotImplementedException(); }
    }

    public bool Delete(Category item)
    {
      throw new NotImplementedException();
    }

    public List<Category> Find(Predicate<Category> predicate)
    {
      throw new NotImplementedException();
    }

    public Category CreateCategory(string name)
    {
      throw new NotImplementedException();
    }

    public long NumberOfCategories()
    {
      return SelectCountFromTable(DbConsts.TableCategories);
    }

    public List<Category> AllCategories
    {
      get { throw new NotImplementedException(); }
    }

    public bool Save()
    {
      IDbTransaction transaction = Connection.BeginTransaction();
      try
      {
        // TODO suboptimal
        foreach (var book in Books)
          book.Update(Connection);
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
      Books.Clear();

      IDbCommand selectBooks = 
        new MySqlCommand(DbConsts.BookSelect, (MySqlConnection) Connection);

      IDataReader reader = selectBooks.ExecuteReader();
      while (reader.Read())
      {
        Book newBook = new Book();
        newBook.PopulateFromReader(reader);
        Books.Add(newBook);
      }
      reader.Close();

      return this;
    }

    public void DropTables()
    {
      // drop mappings first
      var tables = new ArrayList()
      {
        DbConsts.TableBook2Author,
        DbConsts.TableBook2Category,
        DbConsts.TableBook2Keyword,
        DbConsts.TableBooks,
        DbConsts.TableAuthors,
        DbConsts.TableCategories,
        DbConsts.TableKeywords
      };

      foreach (var table in tables)
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


      return (long)selectCountCommand.ExecuteScalar();
    }
  }
}
