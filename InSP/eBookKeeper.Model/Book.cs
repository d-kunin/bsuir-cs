using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class Book : DbObject, IComparable<Book>
  {
    private List<Author> _mAuthors = new List<Author>();
    private List<Category> _mCategories = new List<Category>();
    private string _mTitle = String.Empty;

    public Book()
    {
      Edition = 1;
      Description = String.Empty;
      Keywords = new List<string>();
    }

    public string Title
    {
      get { return _mTitle; }
      set { _mTitle = value ?? String.Empty; }
    }

    public List<Author> Authors
    {
      get { return _mAuthors; }
      set { _mAuthors = value ?? new List<Author>(); }
    }

    public List<Category> Categories
    {
      get { return _mCategories; }
      set { _mCategories = value ?? new List<Category>(); }
    }

    public List<string> Keywords { get; set; }
    public string Description { get; set; }
    public ushort Edition { get; set; }

    public string FormatedAuthors
    {
      get { return string.Join(", ", Authors); }
    }

    public int CompareTo(Book other)
    {
      if (other == null)
        return 1;
      int compareByTitle =
        String.Compare(Title, other.Title, StringComparison.OrdinalIgnoreCase);
      if (compareByTitle != 0)
        return compareByTitle;
      return Edition - other.Edition;
    }

    public override string ToString()
    {
      return string.Format("{0} by {1}, {2} edition", Title, FormatedAuthors, Edition);
    }

    public override void PopulateFromReader(IDataReader reader)
    {
      Id = Convert.ToUInt32(reader.GetInt32(DbConsts.BookIdIndex));
      Title = reader.GetString(DbConsts.BookTitleIndex);
      Description = reader.GetString(DbConsts.BookDescriptionIndex);
      Edition = Convert.ToUInt16(reader.GetInt16(DbConsts.BookEditionIndex));
    }

    public override void Update(IDbConnection connection)
    {
      IDbCommand updateCommand =
        new MySqlCommand(DbConsts.BookUpdate, (MySqlConnection) connection);

      BindId(updateCommand, DbConsts.BookIdParam);
      BindTitle(updateCommand, DbConsts.BookTitleParam);
      BindEdition(updateCommand, DbConsts.BookEditionParam);
      BindDescription(updateCommand, DbConsts.BookDescriptionParam);

      updateCommand.ExecuteNonQuery();

      // write categories
      foreach (Category category in Categories)
      {
        IDbCommand map2Category = new MySqlCommand(DbConsts.InsertBook2Category,
          (MySqlConnection) connection);

        BindId(map2Category, DbConsts.BookIdParam);
        category.BindId(map2Category, DbConsts.CategoryIdParam);
        map2Category.ExecuteNonQuery();
      }

      // write authors
      foreach (Author author in  Authors)
      {
        IDbCommand map2Author = new MySqlCommand(DbConsts.InsertBook2Author,
          (MySqlConnection) connection);

        BindId(map2Author, DbConsts.BookIdParam);
        author.BindId(map2Author, DbConsts.AuthorIdParam);
        map2Author.ExecuteNonQuery();
      }

      // write keywords
      foreach (string keyword in Keywords)
      {
        IDbCommand keywordInsert = new MySqlCommand(DbConsts.KeywordInsert,
          (MySqlConnection) connection);

        BindId(keywordInsert, DbConsts.BookIdParam);
        keywordInsert.Parameters.Add(DbConsts.KeywordNameParam);
        DbConsts.KeywordNameParam.Value = keyword;

        keywordInsert.ExecuteNonQuery();
      }
    }

    public void BindTitle(IDbCommand command, DbParameter param)
    {
      param.Value = Title;
      command.Parameters.Add(param);
    }

    public void BindEdition(IDbCommand command, DbParameter param)
    {
      param.Value = Edition;
      command.Parameters.Add(param);
    }

    public void BindDescription(IDbCommand command, DbParameter param)
    {
      param.Value = Description;
      command.Parameters.Add(param);
    }
  }
}