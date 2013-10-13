using System;
using System.Data;
using System.Data.Common;
using System.Windows.Documents.DocumentStructures;
using MySql.Data.MySqlClient;

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
      IDbCommand updateCommand = new MySqlCommand(DbConsts.CategoryUpdate, 
        (MySqlConnection) connection);

      BindId(updateCommand, DbConsts.CategoryIdParam);
      BindName(updateCommand, DbConsts.CategoryNameParam);

      updateCommand.ExecuteNonQuery();
    }

    public override void PopulateFromReader(IDataReader reader)
    {
      Id = Convert.ToUInt32(reader.GetInt32(DbConsts.CategoryIdIndex));
      Name = reader.GetString(DbConsts.CategoryNameIndex);
    }

    public void BindName(IDbCommand command, DbParameter param)
    {
      param.Value = Name;
      command.Parameters.Add(param);
    }
  }
}