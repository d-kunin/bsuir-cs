using System;
using System.Linq;
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

        [TestMethod]
        public void SaveRestoreTest()
        {
            var stubIndex = new StubLibraryIndex();
            var a = stubIndex.CreateAuthor("Billy");
            var c = stubIndex.CreateCategory("Sci-Fi");
            var b1 = stubIndex.CreateBook("The Book");

            b1.Authors.Add(a);
            b1.Categories.Add(c);

            stubIndex.Save();
            var sb2 = stubIndex.Restore();

            Assert.IsTrue(stubIndex.AllAuthors.SequenceEqual(sb2.AllAuthors));
            Assert.IsTrue(stubIndex.AllBooks.SequenceEqual(sb2.AllBooks));
            Assert.IsTrue(stubIndex.AllCategories.SequenceEqual(sb2.AllCategories));
        }
    }
}
