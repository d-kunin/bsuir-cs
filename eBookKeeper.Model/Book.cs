using System;
using System.Collections.Generic;
using System.Linq;

namespace eBookKeeper.Model
{

    [Serializable]
    public class Book : IComparable<Book>
    {
        private List<Author> _mAuthors = new List<Author>(); 
        private List<Category> _mCategories = new List<Category>();
        private string _mTitle = String.Empty;

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

        public List<string> Keywords { get; set; }
        public List<string> TableOfContent { get; set; }
        public string       Description { get; set; }
        public uint         Edition { get; set; }

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

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;

            Book other = (Book) obj;
            return String.Equals(Title, other.Title, StringComparison.OrdinalIgnoreCase)
                   && (Edition == other.Edition) 
                   && (Authors != null 
                        ? Authors.SequenceEqual(other.Authors) 
                        : other.Authors == null)
                   && (Categories != null
                        ? Categories.SequenceEqual(other.Categories) 
                        : other.Categories == null);
        }

        public override int GetHashCode()
        {
            return Tuple.Create(Title, 
                Authors != null ? Authors.Count : 0, 
                Categories != null ? Categories.Count: 0, 
                Edition)
              .GetHashCode();
        }

        public override string ToString()
        {
            return string.Format("{0} by {1}, {2} edition", Title, FormatedAuthors, Edition);
        }
    }

    [Serializable]
    public class Category : IComparable<Category>
    {
        // TODO: may add parent/child categories
        public string Name { get; set; }

        public int CompareTo(Category other)
        {
            return String.Compare(Name, other.Name, StringComparison.OrdinalIgnoreCase);
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;
            return String.Equals(Name, ((Category)obj).Name, StringComparison.OrdinalIgnoreCase);
        }

        public override int GetHashCode()
        {
            return Name == null ? 0 : Name.GetHashCode();
        }

        public override string ToString()
        {
            return Name;
        }
    }

    [Serializable]
    public class Author : IComparable<Author>
    {
        public string Name { get; set; }

        public int CompareTo(Author other)
        {
            return String.Compare(Name, other.Name, StringComparison.OrdinalIgnoreCase);
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;
            return String.Equals(Name, ((Author)obj).Name);
        }

        public override int GetHashCode()
        {
            return Name == null ? 0 : Name.GetHashCode();
        }

        public override string ToString()
        {
            return Name;
        }
    }

}
