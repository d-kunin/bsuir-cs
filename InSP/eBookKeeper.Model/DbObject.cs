using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eBookKeeper.Model
{
  abstract class DbObject
  {

    public int Id { get; private set; }

    protected DbObject(int id)
    {
      Id = id;
    }

    /// <summary>
    /// Helps is to save, update
    /// </summary>
    /// <param name="command"></param>
    /// <returns></returns>
    public abstract IDbCommand AddParams(IDbCommand command);

    /// <summary>
    /// Helps to read
    /// </summary>
    /// <param name="reader"></param>
    /// <returns></returns>
    public abstract bool PopualateFromReader(IDataReader reader);

  }
}
