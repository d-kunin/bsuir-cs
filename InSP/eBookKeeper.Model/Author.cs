using System;
using System.Data;
using System.Data.Common;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public class Author : DbObject, IComparable<Author>
  {
    internal Author(LibraryIndexOnDb index) : base(index)
    {}

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
      IDbCommand updateCommand = new MySqlCommand(Db.AuthorUpdate,
        (MySqlConnection) connection);

      BindId(updateCommand, Db.AuthorIdParam);
      BindName(updateCommand, Db.AuthorNameParam);

      updateCommand.ExecuteNonQuery();
    }

    public override void PopulateFromReader(IDataReader reader)
    {
      Id = Convert.ToUInt32(reader.GetInt32(Db.AuthorIdIndex));
      Name = reader.GetString(Db.AuthorNameIndex);
    }

    public void BindName(IDbCommand command, DbParameter param)
    {
      param.Value = Name;
      command.Parameters.Add(param);
    }
  }
}