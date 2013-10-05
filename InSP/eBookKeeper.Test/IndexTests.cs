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

            Assert.AreEqual(stubIndex.AllBooks.Select(b => sb2.AllBooks.Find(x => x.Authors.SequenceEqual(b.Authors))).Count(), sb2.AllBooks.Count);
            Assert.AreEqual(stubIndex.AllCategories.Select(b => sb2.AllCategories.Find(x => x.Name.Equals(b.Name))).Count(), sb2.AllCategories.Count);
            Assert.AreEqual(stubIndex.AllAuthors.Select(b => sb2.AllAuthors.Find(x => x.Name.Equals(b.Name))).Count(), sb2.AllAuthors.Count);
        }
    }
}
