using eBookKeeper.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace eBookKeeper.Test
{
  [TestClass]
  public class MySqlDbIndexTest
  {
    private LibraryIndexOnDb _index;

    [TestInitialize]
    public void SetUp()
    {
      _index = new LibraryIndexOnDb();

      _index.DropTables();
      _index.InitTables();
    }

    [TestMethod]
    public void EmptyTablesTest()
    {
      Assert.AreEqual(0, _index.NumberOfAuthors());
      Assert.AreEqual(0, _index.NumberOfBooks());
      Assert.AreEqual(0, _index.NumberOfCategories());
    }

    [TestMethod]
    public void CreateBooksTest()
    {
      AddTestBooks(3);

      Assert.AreEqual(3, _index.NumberOfBooks());
      Assert.AreEqual(3, _index.AllBooks.Count);
    }

    [TestMethod]
    public void AddSaveReadTest()
    {
      AddTestBooks(5);
      AddTestAuthors(6);
      AddTestCategories(7);

      _index.Save();

      var restoredIndex = new LibraryIndexOnDb();
      restoredIndex.Restore();

      Assert.AreEqual(5, restoredIndex.AllBooks.Count);
      Assert.AreEqual(5, restoredIndex.NumberOfBooks());

      Assert.AreEqual(6, restoredIndex.AllAuthors.Count);
      Assert.AreEqual(6, restoredIndex.NumberOfAuthors());

      Assert.AreEqual(7, restoredIndex.AllCategories.Count);
      Assert.AreEqual(7, restoredIndex.NumberOfCategories());
    }

    [TestMethod]
    public void DeleteBookTest()
    {
      AddTestBooks(5);

      Assert.AreEqual(5, _index.AllBooks.Count);

      Book b1 = _index.AllBooks[0];
      Book b2 = _index.AllBooks[3];

      _index.Delete(b1);

      Assert.AreEqual(4, _index.NumberOfBooks());

      _index.Delete(b2);

      Assert.AreEqual(3, _index.NumberOfBooks());
    }


    [TestMethod]
    public void CreateAuthorsTest()
    {
      AddTestAuthors(99);

      Assert.AreEqual(99, _index.NumberOfAuthors());
      Assert.AreEqual(99, _index.AllAuthors.Count);
    }

    [TestMethod]
    public void CreateCategoriesTest()
    {
      AddTestCategories(42);

      Assert.AreEqual(42, _index.NumberOfCategories());
      Assert.AreEqual(42, _index.AllCategories.Count);
    }

    [TestMethod]
    public void DeleteAuthorTest()
    {
      AddTestAuthors(42);

      Author a1 = _index.AllAuthors[13];
      Author a2 = _index.AllAuthors[0];

      _index.Delete(a1);

      Assert.AreEqual(41, _index.NumberOfAuthors());
      Assert.AreEqual(41, _index.AllAuthors.Count);

      _index.Delete(a2);

      Assert.AreEqual(40, _index.NumberOfAuthors());
      Assert.AreEqual(40, _index.AllAuthors.Count);
    }

    [TestMethod]
    public void DeleteCategoriesTest()
    {
      AddTestCategories(42);

      Category c1 = _index.AllCategories[41];
      Category c2 = _index.AllCategories[13];
      Category c3 = _index.AllCategories[0];

      _index.Delete(c3);

      Assert.AreEqual(41, _index.NumberOfCategories());
      Assert.AreEqual(41, _index.AllCategories.Count);

      _index.Delete(c2);
      _index.Delete(c1);

      Assert.AreEqual(39, _index.NumberOfCategories());
      Assert.AreEqual(39, _index.AllCategories.Count);
    }

    [TestMethod]
    public void Map2CategoryAuthorKeywordTest()
    {
      AddTestAuthors(5);
      AddTestBooks(5);
      AddTestCategories(5);

      for (int i = 0; i < 5; ++i)
        for (int j = 0; j <= i; ++j)
        {
          var book = _index.AllBooks[i];
          book.AddAuthor(_index.AllAuthors[j]);
          book.AddCategory(_index.AllCategories[j]);
          book.AddKeyword("Keyword " + i + j);
        }

      _index.Save();

      var restoredIndex = new LibraryIndexOnDb();
      restoredIndex.Restore();

      for (int i = 1; i <= 5; ++i)
      {
        Assert.AreEqual(1, restoredIndex.AllBooks.FindAll(b => b.Authors.Count == i).Count);
        Assert.AreEqual(1, restoredIndex.AllBooks.FindAll(b => b.Categories.Count == i).Count);
        Assert.AreEqual(1, restoredIndex.AllBooks.FindAll(b => b.Keywords.Count == i).Count);
      }
    }

    private void AddTestBooks(int count)
    {
      for (int i = 0; i < count; ++i)
        _index.CreateBook("Book " + i).Description = "Lorem Impus Blablabla!";
    }

    private void AddTestAuthors(int count)
    {
      for (int i = 0; i < count; ++i)
        _index.CreateAuthor("Author " + i);
    }

    private void AddTestCategories(int count)
    {
      for (int i = 0; i < count; ++i)
        _index.CreateCategory("Category " + i);
    }
  }
}