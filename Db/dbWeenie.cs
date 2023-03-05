using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Xml.Linq;

namespace WeenieViewer.Db
{
    internal class dbWeenie
    {
        public Dictionary<int, int> Ints;
        public Dictionary<int, long> Int64s;
        public Dictionary<int, string> Strings;
        public Dictionary<int, float> Floats;
        public Dictionary<int, bool> Bools;
        public Dictionary<int, int> DIDs;
        public Dictionary<int, int> IIDs;

        public int WeenieType;
        public string WeenieClass;
        public string AppraisalText;

    }
}
