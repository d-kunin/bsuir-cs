using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eBookKeeper.Model
{
  public class MySqlStatements
  {
    public const string TableBooks = "books";
    public const string TableCategories = "categories";
    public const string TableAuthors = "authors";
    public const string TableBook2Author = "book_to_author_map";
    public const string TableBook2Category = "book_to_category_map";

    public const string CreateTables = "CREATE TABLE IF NOT EXISTS bsuir.books (" +
                                       "Id INT PRIMARY KEY AUTO_INCREMENT," +
                                       "Title varchar(255) character set cp1251 DEFAULT 'no name' ," +
                                       "Description TEXT   character set cp1251," +
                                       "Edition TINYINT UNSIGNED DEFAULT 1" +
                                       ");" +

                                       "CREATE TABLE IF NOT EXISTS bsuir.authors (" +
                                       "Id INT PRIMARY KEY AUTO_INCREMENT," +
                                       "Name varchar(255)character set cp1251 DEFAULT 'Какой-то автор.'" +
                                       ");" + 
                                       
                                       "CREATE TABLE IF NOT EXISTS bsuir.categories (" +
	                                     "Id INT PRIMARY KEY AUTO_INCREMENT," +
	                                     "Name varchar(255) character set cp1251 DEFAULT 'Ниочем'" +
                                       ");";

    public const string CreateMappingTables = "CREATE TABLE IF NOT EXISTS bsuir.book_to_category_map (" +
                                              "BookId int NOT NULL," +
                                              "CategoryId int NOT NULL," +

                                              "constraint fk_bookId2Category " +
                                              "foreign key (BookId) references bsuir.books(Id)," +
                                              "constraint fk_categoryId2Book " +
                                              "foreign key (CategoryId) references bsuir.categories(Id)" +
                                              ");" +

                                              "CREATE TABLE IF NOT EXISTS bsuir.book_to_author_map (" +
                                              "BookId int NOT NULL," +
                                              "AuthorId int NOT NULL," +

                                              "constraint fk_bookId2Author " +
                                              "foreign key (BookId) references bsuir.categories(Id)," +
                                              "constraint fk_authorId2Book " +
                                              "foreign key (AuthorId) references bsuir.authors(Id)" +
                                              ");";

    public const string DropTable   = "DROP TABLE IF EXISTS ";

    public const string SelectLastInsertId = "SELECT LAST_INSERT_ID()";
    public const string SelectCountFrom = "SELECT COUNT(*) FROM ";
  }
}
