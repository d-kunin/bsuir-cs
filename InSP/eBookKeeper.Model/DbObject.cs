using System;
using System.Collections.Generic;
using System.Data;
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
    }

    public virtual void PopulateFromReader(IDataReader reader)
    {
    }
     

  }
}
