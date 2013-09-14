using System;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;

namespace eBookKeeper.Model
{
    [Serializable]
    public class StubLibraryIndex : ILibraryIndex
    {
        public StubLibraryIndex()
        {
            // Populate with foo data
            AllBooks      = new List<Book>();
            AllAuthors    = new List<Author>();
            AllCategories = new List<Category>();
        }


        public bool Delete(Book book)
        {
            return AllBooks.RemoveAll(x => x.Equals(book)) > 0;
        }

        public List<Book> Find(Predicate<Book> predicate)
        {
            return AllBooks.FindAll(predicate);
        }

        public Book CreateBook(string title, List<Author> authors = null, List<Category> categories = null, List<string> tableOfContent = null)
        {
            if (authors == null)
                authors = new List<Author>();
            if (categories == null)
                categories = new List<Category>();
            if (tableOfContent == null)
                tableOfContent = new List<string>();

            var book = new Book()
            {
                Title = title,
                Authors = authors,
                Categories = categories,
                TableOfContent = tableOfContent
            };

            AllBooks.Add(book);
            return book;
        }

        public int NumberOfBooks()
        {
            return AllBooks.Count;
        }

        public List<Book> AllBooks { get; set; }

        public bool Delete(Author author)
        {
            return AllAuthors.RemoveAll(x => x.Equals(author)) > 0;
        }

        public List<Author> Find(Predicate<Author> predicate)
        {
            return AllAuthors.FindAll(predicate);
        }

        public Author CreateAuthor(string name)
        {
            var author = new Author()
            {
                Name = name
            };

            AllAuthors.Add(author);
            return author;
        }

        public int NumberOfAuthors()
        {
            return AllAuthors.Count;
        }

        public List<Author> AllAuthors { get; set; }

        public bool Delete(Category category)
        {
            return AllCategories.RemoveAll(x => x.Equals(category)) > 0;
        }

        public List<Category> Find(Predicate<Category> predicate)
        {
            return AllCategories.FindAll(predicate);
        }

        public Category CreateCategory(string name)
        {
            var category = new Category()
            {
                Name = name
            };

            AllCategories.Add(category);
            return category;
        }

        public int NumberOfCategories()
        {
            return AllCategories.Count;
        }

        public List<Category> AllCategories { get; set; }

        public bool Save()
        {
            using (TextWriter writer = new StreamWriter("book_index.xml"))
            {
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(StubLibraryIndex));
                xmlSerializer.Serialize(writer, this);
            }
            return true;
        }

        public ILibraryIndex Restore()
        {
            using (TextReader reader = new StreamReader("book_index.xml"))
            {
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(StubLibraryIndex));
                StubLibraryIndex sb = (StubLibraryIndex) xmlSerializer.Deserialize(reader);
                return sb;
            }
        }
    }
}
