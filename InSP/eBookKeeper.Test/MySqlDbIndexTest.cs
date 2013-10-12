using System;
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
      Assert.AreEqual(_index.NumberOfBooks(), 3);
    }

    [TestMethod]
    public void AddSaveReadTest()
    {
      AddTestBooks(5);
      _index.Save();
      _index.Restore();

      Assert.AreEqual(5, _index.Books.Count);
    }


    private void AddTestBooks(int count)
    {
      for (int i = 0; i < count; ++i)
        _index.CreateBook("Book " + i);
    }
  }
}
