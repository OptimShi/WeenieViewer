using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WeenieViewer.Db.weenie
{
    public class CreateListItem
    {
        public int objectId { get; set; }
        public int destinationType;
        public int wcid { get; set; } // Needs the getter/setting to load in DataGrid
        public int stackSize;
        public int palette;
        public float shade;
        public bool tryToBond;

        // 
        public string name { get; set; }
        public int value { get; set; }

        // Used for looking up items in inventories
        public int ownerWcid { get; set; }
        public string ownerName { get; set; }
    }
}
