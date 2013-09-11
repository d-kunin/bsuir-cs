using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eBookKeeper.Model
{
    public class Book
    {
        public Book()
        {
            Title = string.Empty;
            Authors    = new List<Author>();
            Categories = new List<Category>();

            ISBN = "0000000000";
            Publisher = new Publisher();
            PublicationDate = new DateTime(0);
            Edition = 1;

            NumberOfPager = 1;
            TableOfContent = new List<string>();
        }

        public string         Title      { get; set; }
        public List<Author>   Authors    { get; set; }
        public List<Category> Categories { get; set; }

        public string    ISBN            { get; set; }
        public Publisher Publisher       { get; set; }
        public DateTime  PublicationDate { get; set; }
        public uint      Edition         { get; set; }


        public uint         NumberOfPager  { get; set; }
        public List<string> TableOfContent { get; set; } 
    }

    public class Category
    {
        public string Name { get; set; }
    }

    public class Author
    {
        public string Name { get; set; }
    }

    public class Publisher
    {
        public string Name { get; set; }
    }
}
