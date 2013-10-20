using System.Data;
using System.Data.Common;

namespace eBookKeeper.Model
{
  public abstract class DbObject
  {
    public uint Id { get; internal set; }
    public abstract void Update(IDbConnection connection);
    public abstract void PopulateFromReader(IDataReader reader);

    protected LibraryIndexOnDb _index;

    protected DbObject(LibraryIndexOnDb index)
    {
      _index = index;
    }

    public void BindId(IDbCommand command, DbParameter param)
    {
      param.Value = Id;
      command.Parameters.Add(param);
    }
  }
}