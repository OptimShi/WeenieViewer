using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Xml.Linq;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;

namespace WeenieViewer.Db
{
    public class dbWeenie
    {
        public Dictionary<PropertyBool, bool> Bools;
        public Dictionary<PropertyFloat, float> Floats;
        public Dictionary<PropertyDID, int> DIDs;
        public Dictionary<PropertyIID, int> IIDs;
        public Dictionary<PropertyInt, int> Ints;
        public Dictionary<PropertyInt64, long> Int64s;
        public Dictionary<PropertyString, string> Strings;
        public Dictionary<int, float> SpellBook; // SpellID, Probability

        public int BookMaxPages;
        public int BookMaxCharsPerPage;
        public Dictionary<int, BookPageData> BookData;
        
        public int WeenieType;
        public string WeenieClass;
        public string AppraisalText;

    }
}
