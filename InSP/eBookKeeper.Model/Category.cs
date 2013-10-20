using System;
using System.Data;
using System.Data.Common;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class Category : DbObject, IComparable<Category>
  {
    internal Category(LibraryIndexOnDb index) : base(index)
    {}


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
      IDbCommand updateCommand = new MySqlCommand(Db.CategoryUpdate,
        (MySqlConnection) connection);

      BindId(updateCommand, Db.CategoryIdParam);
      BindName(updateCommand, Db.CategoryNameParam);

      updateCommand.ExecuteNonQuery();
    }

    public override void PopulateFromReader(IDataReader reader)
    {
      Id = Convert.ToUInt32(reader.GetInt32(Db.CategoryIdIndex));
      Name = reader.GetString(Db.CategoryNameIndex);
    }

    public void BindName(IDbCommand command, DbParameter param)
    {
      param.Value = Name;
      command.Parameters.Add(param);
    }
  }
}