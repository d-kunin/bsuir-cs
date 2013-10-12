using System;
using System.Collections.Generic;

namespace eBookKeeper.Model
{
    public interface IIndex<T>
    {
        bool Delete(T item);
        List<T> Find(Predicate<T> predicate);
    }

    public interface IBookIndex : IIndex<Book>
    {
        Book CreateBook(string title,
           List<Author> authors = null,
           List<Category> categories = null);

        long NumberOfBooks();
        List<Book> AllBooks { get; } 
    }

    public interface IAuthorIndex : IIndex<Author>
    {
        Author CreateAuthor(string name);
        long NumberOfAuthors();
        List<Author> AllAuthors { get; } 
    }

    public interface ICategoryIndex : IIndex<Category>
    {
        Category CreateCategory(string name);
        long NumberOfCategories();
        List<Category> AllCategories { get; } 
    }

}
