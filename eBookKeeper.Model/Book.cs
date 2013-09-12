using System.Collections.Generic;

namespace eBookKeeper.Model
{
    public abstract class UniqueObject
    {
        public ulong Id { get; private set; }

        protected UniqueObject(ulong id)
        {
            Id = id;
        }
    }

    public class Book : UniqueObject
    {
        internal Book(ulong id) : base(id) {}

        public string         Title      { get; set; }
        public List<Author>   Authors    { get; set; }
        public List<Category> Categories { get; set; }
        public List<string>   TableOfContent { get; set; }

        /*
         *  Additional data, may use it later
         */
//      public string    ISBN            { get; set; }
//      public Publisher Publisher       { get; set; }
//      public DateTime  PublicationDate { get; set; }
//      public uint      NumberOfPager  { get; set; }
//      public uint      Edition         { get; set; }
    }

    public class Category : UniqueObject
    {
        public Category(ulong id) : base(id) {}

        // TODO: may add parent/child categories
        public string Name { get; set; }
    }

    public class Author : UniqueObject
    {
        public Author(ulong id) : base(id) {}

        public string Name { get; set; }
    }
}
