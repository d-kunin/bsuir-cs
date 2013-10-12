using System;
using eBookKeeper.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace eBookKeeper.Test
{
  [TestClass]
  public class MySqlDbIndexTest
  {

    private LibraryIndexOnDb _index;

    [ClassInitialize]
    public void SetUp()
    {
      _index = new LibraryIndexOnDb();
      
      _index.DropTables();
      _index.InitTables();
    }

    [TestMethod]
    public void FooTest()
    {
      Assert.IsTrue(false);

      Assert.Fail("Must fail");
    }

    [TestMethod]
    public void EmptyTablesTest()
    {
      
    }
  }
}
