using System;
using System.Collections.Generic;

namespace eBookKeeper.Model
{
    interface IIndex<T>
    {
        bool Delete(T item);
        List<T> Find(Predicate<T> predicate);
    }

    interface IBookIndex : IIndex<Book>
    {
        Book CreateBook(string title,
           List<Author> authors = null,
           List<Category> categories = null,
           List<string> tableOfContent = null);

        int NumberOfBooks();
        List<Book> AllBooks { get; } 
    }

    interface IAuthorIndex : IIndex<Author>
    {
        Author CreateAuthor(string name);
        int NumberOfAuthors();
        List<Author> AllAuthors { get; } 
    }

    interface ICategoryIndex : IIndex<Category>
    {
        Category CreateCategory(string name);
        int NumberOfCategories();
        List<Category> AllCategories { get; } 
    }

}
