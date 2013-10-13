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
  public class DbObject
  {

    public uint Id { get; internal set; }

    public virtual void Update(IDbConnection connection)
    {
      // we do not want to force client to override this methods
      // but we client must not rely on them
      throw new NotSupportedException();
    }

    public virtual void PopulateFromReader(IDataReader reader)
    {
      throw new NotSupportedException();
    }

    public void BindId(IDbCommand command, DbParameter param)
    {
      param.Value = Id;
      command.Parameters.Add(param);
    }
  }
}
