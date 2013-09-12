using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eBookKeeper.Model
{
    interface IELibraryIndex : IBookIndex, IAuthorIndex, ICategoryIndex
    {
        bool Save();
        bool Restore();
    }

}
