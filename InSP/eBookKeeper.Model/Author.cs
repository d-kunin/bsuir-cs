using System;

namespace eBookKeeper.Model
{
  public class Author : DbObject, IComparable<Author>
  {
    public string Name { get; set; }

    public int CompareTo(Author other)
    {
      return String.Compare(Name, other.Name, StringComparison.OrdinalIgnoreCase);
    }

    public override string ToString()
    {
      return Name;
    }
  }
}