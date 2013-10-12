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
  }
}
