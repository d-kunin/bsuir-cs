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

        public Book CreateBook(string title, List<Author> authors = null, List<Category> categories = null)
        {
            var book = new Book
            {
                Title = title,
                Authors = authors,
                Categories = categories,
            };

            AllBooks.Add(book);
            return book;
        }

        public long NumberOfBooks()
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

        public long NumberOfAuthors()
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

        public long NumberOfCategories()
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

        private static Random _random = new Random();
        public static void PopulateWithStubData(ILibraryIndex index)
        {
            const int booksToGenerate = 42*7; // Some magic numbers. Because 42.

            string[] bookNames =
            {
                "WTF", "WPF", "J2E","C#",
                "Introduction", "Depth",
                "C++", "Java", "iOS", "Android",
                "Bugs", "Monkeys",
                "Rails", "Ruby", "Advanced",
                "Concurrency", "Optimazation", "CookBook",
                "Beginning", "Design", "Pattern", ".NET",
                "DirectX", "OpenGl"
            };

            string[] preps =
            {
                "for", "on", "in", "to", "with"
            };

            string[] authors =
            {
                "Semmy Fixter",
                "Max Issueman",
                "Steve Looper",
                "Mark Deadlock",
                "Bill Goto",
                "Garry Template",
                "Joel Howto",
                "John Skeetles"
            };
            string[] categories =
            {
                "Success story", "Love story",
                "Textbook", "Novel",
                "Computer Science", "Pseudoscience",
                "Horror", "Software",
                "Programming Languages", "Web Development",
                "System Programming", "Mobile Devices",
                "Big Data"
                };

            string[] keywords =
            {
                    "WTF", "WPF", "J2E", "C#",
                    "C++", "Java", "iOS", "Android",
                    "Rails", "Ruby", "Management",
                    "Concurrency", "Optimazation", "CookBook",
                    "Design", "Pattern", ".NET"
            };

            foreach (var author in authors)
                index.CreateAuthor(author);
            foreach (var category in categories)
                index.CreateCategory(category);

            Chooser<string> keyWordsChooser = new Chooser<string>(keywords.ToList());
            Chooser<Author> authorChooser = new Chooser<Author>(index.AllAuthors);
            Chooser<Category> categoryChooser = new Chooser<Category>(index.AllCategories);



            for (var i = 0; i < booksToGenerate; ++i)
            {
                int wordsInTitle = _random.Next(2, 5);
                string title = "";
                var usedIndeces = new HashSet<int>();
                for (var j = 0; j < wordsInTitle; ++j)
                {
                    // genarate index 
                    int nameIndex;

                    while (usedIndeces.Contains((nameIndex = _random.Next(bookNames.Length))))
                    {
                        // noop
                    }
                    usedIndeces.Add(nameIndex);

                    title = String.Join(" ", title, bookNames[nameIndex]);

                    if (j != 0 && j != wordsInTitle - 1) // preposition must not be in the and or beginning
                    {
                        bool addPreposition = _random.Next()%2 == 0;
                        if (addPreposition)
                            title = String.Join(" ", title, preps[_random.Next(preps.Length)]);
                    }

                }

                var book = index.CreateBook(title.Trim(), authorChooser.ChooseRandom(1, 3), categoryChooser.ChooseRandom(1,2));
                book.Keywords =  keyWordsChooser.ChooseRandom(1, 5);
                book.Description =
                    "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.";
            }
        }

        class Chooser<T>
        {
            readonly List<T> _mInput;

            public Chooser(List<T> input)
            {
                _mInput = input;
            }

            public List<T> ChooseRandom(int minCount, int maxCount)
            {
                if (maxCount > _mInput.Count)
                    throw new ArgumentException(
                        String.Format("Can't get {0} items from {1}-size collection.", maxCount, _mInput.Count));

                var indeces = GetRandomUniqueSeries(minCount, maxCount, _mInput.Count);

                return indeces.Select(index => _mInput[index]).ToList();
            }
        }

        private static List<int> GetRandomUniqueSeries(int minCount, int maxCount, int maxValue)
        {
            var addedIndeces = new HashSet<int>();
            int numberToGenerate = _random.Next(minCount, maxCount);

            while (addedIndeces.Count < numberToGenerate)
            {
                int nextIndex = _random.Next(maxValue);
                if (addedIndeces.Contains(nextIndex))
                    continue;
                else
                    addedIndeces.Add(nextIndex);
            }
            return addedIndeces.ToList();
        }


    }
}
