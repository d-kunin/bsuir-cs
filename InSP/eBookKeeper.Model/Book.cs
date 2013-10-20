using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data;
using System.Data.Common;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class Book : DbObject, IComparable<Book>
  {
    private readonly List<Author>   _authors    = new List<Author>();
    private readonly List<Category> _categories = new List<Category>();
    private readonly List<string>   _keywords   = new List<string>();
    private string _title = String.Empty;

    internal Book(LibraryIndexOnDb index) : base(index)
    {
      Edition = 1;
      Description = String.Empty;
    }

    public string Title
    {
      get { return _title; }
      set { _title = value ?? String.Empty; }
    }

    public ReadOnlyCollection<Author> Authors
    {
      get { return _authors.AsReadOnly(); }
    }

    public ReadOnlyCollection<Category> Categories
    {
      get { return _categories.AsReadOnly(); }
    }

    public ReadOnlyCollection<string> Keywords
    {
      get { return _keywords.AsReadOnly(); }
    }
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
      Id = Convert.ToUInt32(reader.GetInt32(Db.BookIdIndex));
      Title = reader.GetString(Db.BookTitleIndex);
      Description = reader.GetString(Db.BookDescriptionIndex);
      Edition = Convert.ToUInt16(reader.GetInt16(Db.BookEditionIndex));
    }

    public override void Update(IDbConnection connection)
    {
      IDbCommand updateCommand =
        new MySqlCommand(Db.BookUpdate, (MySqlConnection) connection);

      BindId(updateCommand, Db.BookIdParam);
      BindTitle(updateCommand, Db.BookTitleParam);
      BindEdition(updateCommand, Db.BookEditionParam);
      BindDescription(updateCommand, Db.BookDescriptionParam);

      updateCommand.ExecuteNonQuery();
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

#region Mappings

    public void AddAuthor(Author author)
    {
      if (!_authors.Contains(author))
      {
        _authors.Add(author);
        _index.InsertInto(Db.TableBook2Author, "BookId, AuthorId", Id + ", " + author.Id);
      }
    }

    public bool Remove(Author author)
    {
      if (_authors.Contains(author))
      {
        _authors.Remove(author);
        _index.DeleteFrom(Db.TableBook2Author, "BookId=" + Id + " AND AuthorId=" + author.Id);
        return true;
      }
      return false;
    }

    public void AddCategory(Category category)
    {
      if (!_categories.Contains(category))
      {
        _categories.Add(category);
        _index.InsertInto(Db.TableBook2Category, "BookId, CategoryId", Id + ", " + category.Id);
      }
    }

    public bool Remove(Category category)
    {
      if (_categories.Contains(category))
      {
        _categories.Remove(category);
        _index.DeleteFrom(Db.TableBook2Category, "BookId=" + Id + " AND CategoryId=" + category.Id);
        return true;
      }
      return false;
    }

    public void AddKeyword(string keyword)
    {
      if (!_keywords.Contains(keyword))
      {
        _keywords.Add(keyword);
        _index.InsertInto(Db.TableKeywords, "Name, BookId", keyword.Quoted()+ ", " + Id);
      }
    }

    public bool RemoveKeyword(string keyword)
    {
      if (_keywords.Contains(keyword))
      {
        _keywords.Remove(keyword);
        _index.DeleteFrom(Db.TableKeywords, "Name=" + keyword.Quoted() + " AND BookId=" + Id);
        return true;
      }
      return false;
    }

#endregion 

    internal void Add(Author author) { _authors.Add(author); }
    internal void Add(Category category) { _categories.Add(category); }
    internal void Add(string keyword) { _keywords.Add(keyword); }
  }
}