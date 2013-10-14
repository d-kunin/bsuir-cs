namespace eBookKeeper.Model
{
  public interface ILibraryIndex : IBookIndex, IAuthorIndex, ICategoryIndex
  {
    bool Save();
    ILibraryIndex Restore();
  }
}