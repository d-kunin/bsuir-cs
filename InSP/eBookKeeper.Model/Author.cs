using System;
using System.Data;
using System.Data.Common;
using System.Diagnostics;
using System.Windows.Documents.DocumentStructures;
using MySql.Data.MySqlClient;

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
      return Name + " " + Id;
    }

    public override void Update(IDbConnection connection)
    {
      IDbCommand updateCommand = new MySqlCommand(DbConsts.AuthorUpdate, 
        (MySqlConnection) connection);

      BindId(updateCommand, DbConsts.AuthorIdParam);
      BindName(updateCommand, DbConsts.AuthorNameParam);

      updateCommand.ExecuteNonQuery();
    }

    public override void PopulateFromReader(IDataReader reader)
    {
      Id = Convert.ToUInt32(reader.GetInt32(DbConsts.AuthorIdIndex));
      Name = reader.GetString(DbConsts.AuthorNameIndex);
    }

    public void BindName(IDbCommand command, DbParameter param)
    {
      param.Value = Name;
      command.Parameters.Add(param);
    }
  }
}