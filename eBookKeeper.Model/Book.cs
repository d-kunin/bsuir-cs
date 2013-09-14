using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;

namespace eBookKeeper.Model
{

    [Serializable]
    public class Book : IComparable<Book>
    {
        public string         Title { get; set; }
        public List<Author>   Authors { get; set; }
        public List<Category> Categories { get; set; }

        public List<string> TableOfContent { get; set; }
        public string       Description { get; set; }
        public uint         Edition { get; set; }

        public Book()
        {
            Authors        = new List<Author>();
            Categories     = new List<Category>();
            TableOfContent = new List<string>();
        }

        public int CompareTo(Book other)
        {
            if (other == null)
                return 1;
            int compareByTitle =
                String.Compare(Title, other.Title, StringComparison.OrdinalIgnoreCase);
            if (compareByTitle != 0)
                return compareByTitle;
            else
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
    }

}
