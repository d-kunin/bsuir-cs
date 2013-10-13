﻿using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
    public class Book : DbObject, IComparable<Book>
    {
        public Book()
        {
          Edition = 1;
          Description = "";
        }

        private List<Author>   _mAuthors    = new List<Author>(); 
        private List<Category> _mCategories = new List<Category>();
        private string         _mTitle      = String.Empty;

        public string Title
        {
            get { return _mTitle;  }
            set { _mTitle = value ?? String.Empty;  }
        }
        public List<Author>   Authors 
        {
            get { return _mAuthors; }
            set { _mAuthors = value ?? new List<Author>(); }
        }
        public List<Category> Categories
        {
            get { return _mCategories; }
            set { _mCategories = value ?? new List<Category>(); }
        }

        public List<string> Keywords    { get; set; }
        public string       Description { get; set; }
        public ushort       Edition     { get; set; }

        public string FormatedAuthors
        {
            get
            {
                return string.Join(", ", Authors);
            }
        }

        public int CompareTo(Book other)
        {
            if (other == null)
                return 1;
            int compareByTitle =
                String.Compare(Title, other.Title, StringComparison.OrdinalIgnoreCase);
            if (compareByTitle != 0)
                return compareByTitle;
            return (int) (Edition - other.Edition);
        }

        public override string ToString()
        {
            return string.Format("{0} by {1}, {2} edition", Title, FormatedAuthors, Edition);
        }

      public override void PopulateFromReader(IDataReader reader)
      {
        Id          = Convert.ToUInt32(reader.GetInt32(DbConsts.BookIdIndex));
        Title       = reader.GetString(DbConsts.BookTitleIndex);
        Description = reader.GetString(DbConsts.BookDescriptionIndex);
        Edition     = Convert.ToUInt16(reader.GetInt16(DbConsts.BookEditionIndex));
      }

      public override void Update(IDbConnection connection)
      {
        IDbCommand updateCommand = 
          new MySqlCommand(DbConsts.BookUpdate, (MySqlConnection) connection);

        DbConsts.BookTitleParam.Value = Title;
        DbConsts.BookDescriptionParam.Value = Description;
        DbConsts.BookEditionParam.Value = Edition;
        DbConsts.BookIdParam.Value = Id;

        updateCommand.Parameters.Add(DbConsts.BookTitleParam);
        updateCommand.Parameters.Add(DbConsts.BookDescriptionParam);
        updateCommand.Parameters.Add(DbConsts.BookEditionParam);
        updateCommand.Parameters.Add(DbConsts.BookIdParam);

        updateCommand.ExecuteNonQuery();
      }
    }
}