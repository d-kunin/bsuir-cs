using System;
using System.Data;

namespace eBookKeeper.Model
{
  public class Category : DbObject, IComparable<Category>
  {
    public string Name { get; set; }

    public int CompareTo(Category other)
    {
      return String.Compare(Name, other.Name, StringComparison.OrdinalIgnoreCase);
    }

    public override string ToString()
    {
      return Name;
    }

    public override void Update(IDbConnection connection)
    {
      
    }
  }
}