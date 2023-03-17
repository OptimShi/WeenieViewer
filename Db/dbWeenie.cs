using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Xml.Linq;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;
using Skill = WeenieViewer.Db.weenie.Skill;

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
        public List<SpellBook> SpellBook; // SpellID, Probability

        public Book Book;
        public Dictionary<int, BookPageData> BookData;

        public Dictionary<int, Attributes> Attributes;
        public Dictionary<int, Attributes2nd> Attributes2nd;
        public Dictionary<int, Skill> Skills;

        public int WeenieType;
        public string WeenieClass;
        public string AppraisalText;

        public bool IsCreature()
        {
            if (Bools.ContainsKey(PropertyBool.NPC_LOOKS_LIKE_OBJECT_BOOL) && Bools[PropertyBool.NPC_LOOKS_LIKE_OBJECT_BOOL] == true)
                return false;

            if (Ints.ContainsKey(PropertyInt.ITEM_TYPE_INT) && Ints[PropertyInt.ITEM_TYPE_INT] == 16) // ItemType.Creature
                return true;


            return false;
        }
    }
}
