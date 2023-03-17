using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WeenieViewer.Db;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;

namespace WeenieViewer.Appraisal
{
    partial class ItemExamine
    {
        public string GetCreatureInfo()
        {
            string info = "";

            string name = "";
            InqString(PropertyString.NAME_STRING, ref name);
            info = "Name: " + name + "\n\n";

            info += $"WeenieType: {(WeenieType)Weenie.WeenieType}\nWeenieClass: {Weenie.WeenieClass}\n\n";

            int level = 0;
            if(InqInt(PropertyInt.LEVEL_INT, ref level))
                info += $"Character Level: {level}\n\n";
            else
                info += $"Character Level: ???\n\n";

            int creatureType = 0;
            if(InqInt(PropertyInt.CREATURE_TYPE_INT, ref creatureType))
            {
                string strCreatureType = GetCreatureType(creatureType);
                if (strCreatureType != "")
                    info += strCreatureType + "\n";
            }
            else
            {
                // NPC
            }


            return info;
        }

        public Dictionary<string, string> GetCreatureRatings()
        {
            Dictionary<string, string> ratings = new Dictionary<string, string>();

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

            if (damage_rating > 0 || crit_rating > 0 || crit_damage_rating > 0)
            {
                //ratings.Add("Dmg/CritDmg", )
            }

                return ratings;
        }

        public string GetTextAsTable()
        {
            return "";
        }

        public string GetCreatureType(int creature)
        {
            switch (creature)
            {
                case 0: return "Invalid";
                case 1: return "Olthoi";
                case 2: return "Banderling";
                case 3: return "Drudge";
                case 4: return "Mosswart";
                case 5: return "Lugian";
                case 6: return "Tumerok";
                case 7: return "Mite";
                case 8: return "Tusker";
                case 9: return "Phyntos Wasp";
                case 10: return "Rat";
                case 11: return "Auroch";
                case 12: return "Cow";
                case 13: return "Golem";
                case 14: return "Undead";
                case 15: return "Gromnie";
                case 16: return "Reedshark";
                case 17: return "Armoredillo";
                case 18: return "Fae";
                case 19: return "Virindi";
                case 20: return "Wisp";
                case 21: return "Knathtead";
                case 22: return "Shadow";
                case 23: return "Mattekar";
                case 24: return "Mumiyah";
                case 25: return "Rabbit";
                case 26: return "Sclavus";
                case 27: return "Shallows Shark";
                case 28: return "Monouga";
                case 29: return "Zefir";
                case 30: return "Skeleton";
                case 31: return "Human";
                case 32: return "Shreth";
                case 33: return "Chittick";
                case 34: return "Moarsman";
                case 35: return "Olthoi Larvae";
                case 36: return "Slithis";
                case 37: return "Deru";
                case 38: return "Fire Elemental";
                case 39: return "Snowman";
                case 40: return "Unknown";
                case 41: return "Bunny";
                case 42: return "Lightning Elemental";
                case 43: return "Rockslide";
                case 44: return "Grievver";
                case 45: return "Niffis";
                case 46: return "Ursuin";
                case 47: return "Crystal";
                case 48: return "Hollow Minion";
                case 49: return "Scarecrow";
                case 50: return "Idol";
                case 51: return "Empyrean";
                case 52: return "Hopeslayer";
                case 53: return "Doll";
                case 54: return "Marionette";
                case 55: return "Carenzi";
                case 56: return "Siraluun";
                case 57: return "Aun Tumerok";
                case 58: return "Hea Tumerok";
                case 59: return "Simulacrum";
                case 60: return "Acid Elemental";
                case 61: return "Frost Elemental";
                case 62: return "Elemental";
                case 63: return "Statue";
                case 64: return "Wall";
                case 65: return "Altered Human";
                case 66: return "Device";
                case 67: return "Harbinger";
                case 68: return "Dark Sarcophagus";
                case 69: return "Chicken";
                case 70: return "Gotrok Lugian";
                case 71: return "Margul";
                case 72: return "Bleached Rabbit";
                case 73: return "Nasty Rabbit";
                case 74: return "Grimacing Rabbit";
                case 75: return "Burun";
                case 76: return "Target";
                case 77: return "Ghost";
                case 78: return "Fiun";
                case 79: return "Eater";
                case 80: return "Penguin";
                case 81: return "Ruschk";
                case 82: return "Thrungus";
                case 83: return "Viamontian Knight";
                case 84: return "Remoran";
                case 85: return "Swarm";
                case 86: return "Moar";
                case 87: return "Enchanted Arms";
                case 88: return "Sleech";
                case 89: return "Mukkir";
                case 90: return "Merwart";
                case 91: return "Food";
                case 92: return "Paradox Olthoi";
                case 93: return "Harvest";
                case 94: return "Energy";
                case 95: return "Apparition";
                case 96: return "Aerbax";
                case 97: return "Touched";
                case 98: return "Blighted Moarsman";
                case 99: return "Gear Knight";
                case 100: return "Gurog";
                case 101: return "A'nekshay";
                default: return "";
            }
        }
    }
}
