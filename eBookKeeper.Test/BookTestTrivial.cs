using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using eBookKeeper.Model;

namespace eBookKeeper.Test
{
    [TestClass]
    public class BookTestTrivial
    {
        [TestMethod]
        public void TestMethodEmptyBook()
        {
            var book = new Book();

            Assert.AreEqual(book.Authors.Count, 0);
        }
    }
}
