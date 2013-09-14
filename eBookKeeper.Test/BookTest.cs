using System;
using System.Collections.Generic;
using System.Runtime;
using eBookKeeper.Model;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace eBookKeeper.Test
{
    [TestClass]
    public class BookTest
    {
        [TestMethod]
        public void BooksEqualTest()
        {
            Book b1 = new Book();
            Book b2 = new Book();
            
            Assert.AreEqual(b1, b2);
            Assert.AreEqual(b1.GetHashCode(), b2.GetHashCode());

            b1.Title = "Title";
            Assert.AreNotEqual(b1, b2);

            b2.Title = "NotTitle";
            Assert.AreNotEqual(b1, b2);

            b2.Title = "Title";
            Assert.AreEqual(b1, b2);
            Assert.AreEqual(b1.GetHashCode(), b2.GetHashCode());

            Author a1 = new Author()
            {
                Name = "X"
            };

            Author a2 = new Author()
            {
                Name = "Y"
            };

            b1.Authors.Add(a1);
            Assert.AreNotEqual(b1, b2);

            b2.Authors.Add(a1);
            b2.Authors.Add(a2);
            b1.Authors.Add(a2);
            Assert.AreEqual(b1,b2);
            Assert.AreEqual(b1.GetHashCode(), b2.GetHashCode());

            b1.Title = null;
            Assert.AreNotEqual(b1, b2);
        }
    }
}
