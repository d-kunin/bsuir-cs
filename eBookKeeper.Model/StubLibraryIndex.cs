using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
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

        public static void PopulateWithStubData(ILibraryIndex index)
        {
            const int booksToGenerate = 42*7; // Some magic numbers. Because 42.

            string[] bookNames =
            {
                "WTF", "WPF", "J2E",
                "Introduction", "Depth",
                "C++", "Java", "iOS", "Android",
                "Bugs", "Monkeys",
                "Rails", "Ruby", "Advanced",
                "Concurrency", "Optimazation", "CookBook",
                "Beginning", "Design", "Pattern"
            };

            string[] preps =
            {
                "For", "On", "In", "To"
            };

            string[] authors =
            {
                "Semmy Fixter",
                "Max Issueman",
                "Steve Looper",
                "Mark Deadlock",
                "Bill Goto",
                "Garry Template"
            };
            string[] categories =
            {
                "Success story", "Love story",
                "Textbook", "Novel",
                "Computer Science", "Pseudoscience",
                "Horror", "Software"
            };

            foreach (var author in authors)
                index.CreateAuthor(author);

            foreach (var category in categories)
                index.CreateCategory(category);

            var rand = new Random();
            for (var i = 0; i < booksToGenerate; ++i)
            {
                int wordsInTitle = rand.Next(2, 5);
                string title = "";
                HashSet<int> usedIndeces = new HashSet<int>();
                for (var j = 0; j < wordsInTitle; ++j)
                {
                    // genarate index 
                    int nameIndex;

                    while (usedIndeces.Contains((nameIndex = rand.Next(bookNames.Length))))
                    {
                        // noop
                    }
                    usedIndeces.Add(nameIndex);

                    title = String.Join(" ", title, bookNames[nameIndex]);

                    if (j != 0 && j != wordsInTitle - 1)
                    {
                        bool addPreposition = rand.Next()%2 == 0;
                        if (addPreposition)
                            title = String.Join(" ", title, preps[rand.Next(preps.Length)]);
                    }

                }

                var bookAuthors = new List<Author> {index.AllAuthors[rand.Next(authors.Length)]};

                var bookCategories = new List<Category> {index.AllCategories[rand.Next(categories.Length)]};

                index.CreateBook(title.Trim(), bookAuthors, bookCategories);
            }
        }
    }
}
