using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class DbConsts
  {
    public const string TableBooks = "books";
    public const string TableCategories = "categories";
    public const string TableAuthors = "authors";
    public const string TableKeywords = "keywords";
    public const string TableBook2Author = "book_to_author_map";
    public const string TableBook2Category = "book_to_category_map";

    public const string CreateTables = "CREATE TABLE IF NOT EXISTS bsuir.books (" +
                                       "Id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT," +
                                       "Title varchar(255) character set cp1251 DEFAULT 'no name' ," +
                                       "Description TEXT   character set cp1251," +
                                       "Edition TINYINT UNSIGNED DEFAULT 1" +
                                       ");" +
                                       "CREATE TABLE IF NOT EXISTS bsuir.authors (" +
                                       "Id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT," +
                                       "Name varchar(255)character set cp1251 NOT NULL" +
                                       ");" +
                                       "CREATE TABLE IF NOT EXISTS bsuir.categories (" +
                                       "Id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT," +
                                       "Name varchar(255) character set cp1251 NOT NULL" +
                                       ");" +
                                       "CREATE TABLE IF NOT EXISTS bsuir.keywords (" +
                                       "Id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT," +
                                       "Name varchar(255) character set cp1251 NOT NULL," +
                                       "BookId INT UNSIGNED NOT NULL," +
                                       "constraint foreign key (BookId) references bsuir.books(Id)" +
                                       ");";


    public const string CreateMappingTables = "CREATE TABLE IF NOT EXISTS bsuir.book_to_category_map (" +
                                              "BookId INT UNSIGNED NOT NULL," +
                                              "CategoryId INT UNSIGNED NOT NULL," +
                                              "constraint fk_bookId2Category " +
                                              "foreign key (BookId) references bsuir.books(Id)," +
                                              "constraint fk_categoryId2Book " +
                                              "foreign key (CategoryId) references bsuir.categories(Id)" +
                                              ");" +
                                              "CREATE TABLE IF NOT EXISTS bsuir.book_to_author_map (" +
                                              "BookId INT UNSIGNED NOT NULL," +
                                              "AuthorId INT UNSIGNED NOT NULL," +
                                              "constraint fk_bookId2Author " +
                                              "foreign key (BookId) references bsuir.books(Id)," +
                                              "constraint fk_authorId2Book " +
                                              "foreign key (AuthorId) references bsuir.authors(Id)" +
                                              ");";

    public const string DropTable = "DROP TABLE IF EXISTS ";

    public const string SelectLastInsertId = "SELECT LAST_INSERT_ID()";
    public const string SelectCountFrom = "SELECT COUNT(*) FROM ";

    // insert book2X
    public const string InsertBook2Category = "INSERT INTO " + TableBook2Category +
                                              " (BookId, CategoryId) VALUE (@idBook, @idCat)";

    public const string InsertBook2Author = "INSERT INTO " + TableBook2Author +
                                            "(BookId, AuthorId) VALUE (@idBook, @idAuth)";

    public const string SelectBase = "SELECT * FROM ";

    #region book

    // Book stuff
    public const string BookInsert =
      "INSERT INTO " + TableBooks + " (Title, Description, Edition) values (@title, @descr, @edition)";

    public const string BookUpdate =
      "UPDATE " + TableBooks + " SET Title=@title, Description=@descr, Edition=@edition WHERE Id=@idBook";

    public const string BookDelete =
      "DELETE FROM " + TableBooks + " WHERE Id=@idBook";

    public const string BookSelect =
      "SELECT * FROM " + TableBooks + " ORDER BY Title";

    public static readonly MySqlParameter BookIdParam = new MySqlParameter("@idBook", MySqlDbType.Int32);
    public static readonly MySqlParameter BookTitleParam = new MySqlParameter("@title", MySqlDbType.VarChar);
    public static readonly MySqlParameter BookDescriptionParam = new MySqlParameter("@descr", MySqlDbType.Text);
    public static readonly MySqlParameter BookEditionParam = new MySqlParameter("@edition", MySqlDbType.UByte);

    public static readonly int BookIdIndex = 0;
    public static readonly int BookTitleIndex = 1;
    public static readonly int BookDescriptionIndex = 2;
    public static readonly int BookEditionIndex = 3;

    #endregion

    #region category

    // Category stuff

    public const string CategoryInsert =
      "INSERT INTO " + TableCategories + " (Name) values (@name)";

    public const string CategoryUpdate =
      "UPDATE " + TableCategories + " SET Name=@name WHERE Id=@idCat";

    public const string CategoryDelete =
      "DELETE FROM " + TableCategories + " WHERE Id=@idCat";

    public const string CategorySelect =
      "SELECT * FROM " + TableCategories + " ORDER BY Name";

    public static readonly MySqlParameter CategoryIdParam = new MySqlParameter("@idCat", MySqlDbType.Int32);
    public static readonly MySqlParameter CategoryNameParam = new MySqlParameter("@name", MySqlDbType.VarChar);
    public static readonly int CategoryIdIndex = 0;
    public static readonly int CategoryNameIndex = 1;

    #endregion

    #region author

    // Author stuff

    public const string AuthorInsert =
      "INSERT INTO " + TableAuthors + " (Name) values (@name)";

    public const string AuthorUpdate =
      "UPDATE " + TableAuthors + " SET Name=@name WHERE Id=@idAuth";

    public const string AuthorDelete =
      "DELETE FROM " + TableAuthors + " WHERE Id=@idAuth";

    public const string AuthorSelect =
      "SELECT * FROM " + TableAuthors + " ORDER BY Name";

    public static readonly MySqlParameter AuthorIdParam = new MySqlParameter("@idAuth", MySqlDbType.VarChar);
    public static readonly MySqlParameter AuthorNameParam = new MySqlParameter("@name", MySqlDbType.VarChar);
    public static readonly int AuthorIdIndex = 0;
    public static readonly int AuthorNameIndex = 1;

    #endregion

    #region keyword

    // Keyword stuff

    public const string KeywordInsert =
      "INSERT INTO " + TableKeywords + " (Name, BookId) values (@name, @idBook)";

    public const string KeywordUpdate =
      "UPDATE " + TableKeywords + " SET Name=@name WHERE Id=@idKeyword";

    public const string KeywordDeleteById =
      "DELETE FROM " + TableKeywords + " WHERE Id=@idKeyword";

    public const string KeywordDeleteByBookId =
      "DELETE FROM " + TableKeywords + " WHERE BookId=@idBook";

    public const string KeywordSelect =
      "SELECT * FROM " + TableKeywords + " ORDER BY Name";

    public static readonly MySqlParameter KeywordIdParam = new MySqlParameter("@idKeyword", MySqlDbType.VarChar);
    public static readonly MySqlParameter KeywordNameParam = new MySqlParameter("@name", MySqlDbType.VarChar);
    public static readonly int KeywordIdIndex = 0;
    public static readonly int KeywordNameIndex = 1;
    public static readonly int KeywordBookIdIndex = 2;

    #endregion
  }
}