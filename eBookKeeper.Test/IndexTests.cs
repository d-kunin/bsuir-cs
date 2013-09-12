using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using eBookKeeper.Model;

namespace eBookKeeper.Test
{
    [TestClass]
    public class IndexTests
    {
        [TestMethod]
        public void StubTestCountOfItems()
        {
            var stubIndex = new StubLibraryIndex();

            Assert.AreEqual(stubIndex.NumberOfAuthors(), 0);
            Assert.AreEqual(stubIndex.NumberOfCategories(), 0);
            Assert.AreEqual(stubIndex.NumberOfBooks(), 0);
        }
    }
}
