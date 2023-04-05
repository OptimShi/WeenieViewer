using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WeenieViewer.Db.weenie
{
    public class BookPageData
    {
        public int PageId;
        public long AuthorId;
        public string AuthorName;
        public string AuthorAccount;
        public bool IgnoreAuthor;
        public string PageText;
    }
}
