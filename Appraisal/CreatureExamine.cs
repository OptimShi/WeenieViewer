using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WeenieViewer.Db;
using WeenieViewer.Enums;

namespace WeenieViewer.Appraisal
{
    partial class ItemExamine
    {

        public void GetAsCreature()
        {
            int damage_rating = 0;
            int damage_resist_rating = 0;
            int crit_rating = 0;
            int crit_damage_rating = 0;
            int crit_resist_rating = 0;
            int crit_damage_resist_rating = 0;
            int healing_boost_rating = 0;
            int dot_resist_rating = 0;
            int life_resist_rating = 0;
            InqInt((PropertyInt)0x133u, ref damage_rating);
            InqInt((PropertyInt)0x134u, ref damage_resist_rating);
            InqInt((PropertyInt)0x139u, ref crit_rating);
            InqInt((PropertyInt)0x13Au, ref crit_damage_rating);
            InqInt((PropertyInt)0x13Bu, ref crit_resist_rating);
            InqInt((PropertyInt)0x13Cu, ref crit_damage_resist_rating);
            InqInt((PropertyInt)0x143u, ref healing_boost_rating);
            InqInt((PropertyInt)0x15Eu, ref dot_resist_rating);
            InqInt((PropertyInt)0x15Fu, ref life_resist_rating);
                
        }

        public string GetTextAsTable()
        {
            return "";
        }
    }
}
