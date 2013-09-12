using System;
using System.Collections.Generic;

namespace eBookKeeper.Model
{
    public class StubLibraryIndex : IELibraryIndex
    {
        private ulong _mBookId;
        private ulong _mAuthorId;
        private ulong _mCategoryId;

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
            var book = new Book(++_mBookId)
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

        public List<Book> AllBooks { get; private set; }

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
            var author = new Author(++_mAuthorId)
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

        public List<Author> AllAuthors { get; private set; }

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
            var category = new Category(++_mCategoryId)
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

        public List<Category> AllCategories { get; private set; }

        public bool Save()
        {
            throw new NotImplementedException();
        }

        public bool Restore()
        {
            throw new NotImplementedException();
        }
    }
}
