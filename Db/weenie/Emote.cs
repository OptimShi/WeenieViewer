using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WeenieViewer.Db.weenie
{
    public class Emote
    {
        public Emote()
        {
            EmoteAction = new List<EmoteAction>();
        }

        public int Id { get; set; }
        public int ObjectId { get; set; }
        public int Category { get; set; }
        public float Probability { get; set; }
        public int? WeenieClassId { get; set; }
        public uint? Style { get; set; }
        public uint? Substyle { get; set; }
        public string Quest { get; set; }
        public int? VendorType { get; set; }
        public float? MinHealth { get; set; }
        public float? MaxHealth { get; set; }

        public List<EmoteAction> EmoteAction { get; set; }
    }
}
