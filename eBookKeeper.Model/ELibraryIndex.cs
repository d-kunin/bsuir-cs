using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eBookKeeper.Model
{
    public interface ILibraryIndex : IBookIndex, IAuthorIndex, ICategoryIndex
    {
        bool Save();
        ILibraryIndex Restore();
    }

}
