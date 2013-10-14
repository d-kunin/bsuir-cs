using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace eBookKeeper.Model
{
  public abstract class DbObject
  {
    public abstract void Update(IDbConnection connection);
    public abstract void PopulateFromReader(IDataReader reader);

    public uint Id { get; internal set; }

    public void BindId(IDbCommand command, DbParameter param)
    {
      param.Value = Id;
      command.Parameters.Add(param);
    }
  }
}
