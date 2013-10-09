using System;
using System.Collections.Generic;
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
        var message = "Не могу отрыть подключение к базе: " + Connection.State;
        Console.WriteLine(message);
        throw new IOException(message);
      }
    }

    public IDbConnection Connection { get; private set; }

    public bool Delete(Book item)
    {
      throw new NotImplementedException();
    }

    public List<Book> Find(Predicate<Book> predicate)
    {
      throw new NotImplementedException();
    }

    public Book CreateBook(string title, List<Author> authors = null, List<Category> categories = null, List<string> tableOfContent = null)
    {
      throw new NotImplementedException();
    }

    public int NumberOfBooks()
    {
      throw new NotImplementedException();
    }

    public List<Book> AllBooks
    {
      get { throw new NotImplementedException(); }
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

    public int NumberOfAuthors()
    {
      throw new NotImplementedException();
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

    public int NumberOfCategories()
    {
      throw new NotImplementedException();
    }

    public List<Category> AllCategories
    {
      get { throw new NotImplementedException(); }
    }

    public bool Save()
    {
      throw new NotImplementedException();
    }

    public ILibraryIndex Restore()
    {
      InitTables();

      return this;
    }

    private void InitTables()
    {
      IDbCommand createTablesCommand = 
        new MySqlCommand(MySqlStatements.CreateTables,
                         (MySqlConnection) Connection);

      createTablesCommand.ExecuteNonQuery();

      IDbCommand createMappingCommand = 
        new MySqlCommand(MySqlStatements.CreateMappingTables,
                          (MySqlConnection) Connection);

      createMappingCommand.ExecuteNonQuery();
    }
  }
}
