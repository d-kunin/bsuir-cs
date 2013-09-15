using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Xml.Serialization;

namespace eBookKeeper.Model
{
    [Serializable]
    [XmlRoot(ElementName = "LibraryIndex")]
    public class StubLibraryIndex : ILibraryIndex
    {
        private string _mFilePath = "book_index.xml";

        [XmlElement(ElementName = "Categories", Namespace = "http://kunin.dk")]
        public List<Category> AllCategories { get; set; }
        [XmlElement(ElementName = "Authors", Namespace = "http://kunin.dk")]
        public List<Author>   AllAuthors    { get; set; }
        [XmlElement(ElementName = "Books", Namespace = "http://kunin.dk")]
        public List<Book>   AllBooks    { get; set; }

        public StubLibraryIndex()
        {
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
            var book = new Book
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
            var author = new Author
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
            var category = new Category
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

        

        public bool Save()
        {
            try
            {
                using (TextWriter writer = new StreamWriter(_mFilePath))
                {
                    XmlSerializer xmlSerializer = new XmlSerializer(typeof (StubLibraryIndex));
                    xmlSerializer.Serialize(writer, this);
                }
                return true;
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception on saving file: " + e);
                return false;
            }
        }

        public ILibraryIndex Restore()
        {
            try
            {
                using (TextReader reader = new StreamReader(_mFilePath))
                {
                    XmlSerializer xmlSerializer = new XmlSerializer(typeof(StubLibraryIndex));
                    StubLibraryIndex sb = (StubLibraryIndex)xmlSerializer.Deserialize(reader);
                    return sb;
                }
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception on loading from file: " + e);
                return null;
            }
        }
    }
}
