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
    List<Book> AllBooks { get; }

    Book CreateBook(string title,
      List<Author> authors = null,
      List<Category> categories = null);

    long NumberOfBooks();
  }

  public interface IAuthorIndex : IIndex<Author>
  {
    List<Author> AllAuthors { get; }
    Author CreateAuthor(string name);
    long NumberOfAuthors();
  }

  public interface ICategoryIndex : IIndex<Category>
  {
    List<Category> AllCategories { get; }
    Category CreateCategory(string name);
    long NumberOfCategories();
  }
}