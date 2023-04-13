using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows;
using WeenieViewer.Enums;
using System.Diagnostics;

namespace WeenieViewer.Appraisal
{
    partial class ItemExamine
    {

        private bool InqCreature()
        {
            return false;
        }
        private bool InqArmor()
        {
            return false;
        }
        private bool InqWeapon()
        {
            return false;
        }
        private bool InqInt(PropertyInt prop, ref int value)
        {
            if (Weenie.Ints.ContainsKey(prop))
            {
                value = Weenie.Ints[prop];
                return true;
            }
            return false;
        }
        private bool InqInt64(PropertyInt64 prop, ref long value)
        {
            if (Weenie.Int64s.ContainsKey(prop))
            {
                value = Weenie.Int64s[prop];
                return true;
            }
            return false;
        }
        private bool InqBool(PropertyBool prop, ref bool value)
        {
            if (Weenie.Bools.ContainsKey(prop))
            {
                value = Weenie.Bools[prop];
                return true;
            }
            return false;
        }

        private bool InqFloat(PropertyFloat prop, ref float value)
        {
            if (Weenie.Floats.ContainsKey(prop))
            {
                value = Weenie.Floats[prop];
                return true;
            }
            return false;
        }
        private bool InqDataID(PropertyDID prop, ref int value)
        {
            if (Weenie.DIDs.ContainsKey(prop))
            {
                value = Weenie.DIDs[prop];
                return true;
            }
            return false;
        }
        private bool InqString(PropertyString prop, ref string value)
        {
            if (Weenie.Strings.ContainsKey(prop))
            {
                value = Weenie.Strings[prop];
                return true;
            }
            return false;
        }

        private string ModifierToString(float rMod)
        {
            var v1 = 1 - rMod;
            if (v1 < 1)
            {
                v1 = v1 * -1;
            }
            string g_szPecentText = $"{Math.Floor(v1 * 100.0 + 0.5)}%";
            return g_szPecentText;
        }

        private string SmallModifierToString(float rMod)
        {
            var v1 = 1.0 - rMod;
            if (1.0 - rMod < 0.0)
                v1 = v1 * -1;

            string g_szPecentText = $"{(v1 * 100.0):N1}%";
            return g_szPecentText;
        }

        private string WeaponTimeToString(float wtime)
        {
            if (wtime < 11)
                return "Very Fast";
            else if (wtime < 31)
                return "Fast";
            else if (wtime < 50)
                return "Average";
            else if (wtime < 80)
                return "Slow";
            else
                return "Very Slow";
        }

        private string ClothingPriorityToString(int priority)
        {
            var byte1 = (priority >> 8 & 0xFF);
            string cover = "";
            if ((byte1 & 0x40) != 0)
                cover += "Head, ";
            if ((priority & 8) != 0 || (priority & 0x400) != 0)
                cover += "Chest, ";
            if ((priority & 0x10) != 0 || (byte1 & 8) != 0)
                cover += "Abdomen, ";
            if ((priority & 0x20) != 0 || (byte1 & 0x10) != 0)
                cover += "Upper Arms, ";
            if ((priority & 0x40) != 0 || (byte1 & 0x20) != 0)
                cover += "Lower Arms, ";
            if ((priority & 0x8000) != 0)
                cover += "Hands, ";
            if ((priority & 0x2) != 0 || (byte1 & 0x1) != 0)
                cover += "Upper Legs, ";
            if ((priority & 0x4) != 0 || (byte1 & 0x2) != 0)
                cover += "Lower Legs, ";
            if ((priority & 0x10000) != 0)
                cover += "Feet, ";
            cover = cover.TrimEnd(new Char[] { ',', ' ' }); // trims comma and space
            if (cover != "")
                return "Covers " + cover;
            else
                return "";
        }

        private string DamageResistanceToString(int dtype, int al, double modifier)
        {
            string d_text;
            string modTxt = "";
            if (modifier >= 0)
            {
                switch (dtype)
                {
                    case 1: d_text = "Slashing: "; break;
                    case 2: d_text = "Piercing: "; break;
                    case 4: d_text = "Bludgeoning: "; break;
                    case 8: d_text = "Cold: "; break;
                    case 16: d_text = "Fire: "; break;
                    case 32: d_text = "Acid: "; break;
                    case 64: d_text = "Electric: "; break;
                    case 1024: d_text = "Nether: "; break;
                    default: return "";
                }

                if (modifier >= 2)
                {
                    modTxt = "Unparalleled";
                    modifier = 2.0;
                }
                else if (modifier >= 1.6)
                    modTxt = "Excellent";
                else if (modifier >= 1.2)
                    modTxt = "Above Average";
                else if (modifier >= 0.8)
                    modTxt = "Average";
                else if (modifier >= 0.4)
                    modTxt = "Below Average";
                else if (modifier >= 0)
                    modTxt = "Poor";
            }
            else
            {
                switch (dtype)
                {
                    case 1: d_text = "Your armor will rend and slash you if hit."; break;
                    case 2: d_text = "Your armor will cave in and pierce you if hit."; break;
                    case 4: d_text = "Your armor will shatter and bruise you if hit."; break;
                    case 8: d_text = "Your armor is unnaturally cold."; break;
                    case 16: d_text = "Your armor is flammable."; break;
                    case 32: d_text = "Your armor itches and burns your skin."; break;
                    case 64: d_text = "Your armor is extremely conductive."; break;
                    case 1024: d_text = "Your armor is infused with shadow."; break;
                    default: return "";
                }
            }

            var al_mod = al * modifier;
            return $"{d_text}{modTxt}  ({al_mod:F0})";
        }

        private string DeltaTimeToString(float time)
        {
            int months = (int)(time / 0x278D00); // months
            int days = (int)(time % 0x278D00 / 0x15180); // days
            var v4 = time % 0x278D00 % 0x15180;
            int hours = (int)(v4 / 0xE10); // hours
            v4 %= 0xE10;
            int seconds = (int)(v4 % 0x3C); // seconds
            int minutes = (int)(v4 / 0x3C); // minutes
            string buf = "";
            //return "COOLDOWN_TIME_TODO";

            if (months > 1)
                buf += $"{months} months, ";
            if (days > 1)
                buf += $"{days} days, ";
            if (hours > 1)
                buf += $"{hours} hours, ";
            if (minutes > 0)
                buf += $"{minutes} minutes, ";
            buf += $"{seconds} seconds.";
            return buf;
        }

        private bool InqHeritageGroupDisplayName(int type, ref string heritage_group)
        {
            switch (type) {
                case 1: heritage_group = "Aluvian"; break;
                case 2: heritage_group = "Gharu'ndim"; break;
                case 3: heritage_group = "Sho"; break;
                case 4: heritage_group = "Viamontian"; break;
                case 5: heritage_group = "Umbraen"; break;
                case 6: heritage_group = "Gearknight"; break;
                case 7: heritage_group = "Tumerok"; break;
                case 8: heritage_group = "Lugian"; break;
                case 9: heritage_group = "Empyrean"; break;
                case 10: heritage_group = "Penumbraen"; break;
                case 11: heritage_group = "Undead"; break;
                case 12:
                case 13: heritage_group = "Olthoi"; break;
            }
            if (heritage_group != "" && heritage_group != null)
                return true;

            return false;
        }

        private string GetAppraisalStringFromRequirements(int iReq, int iSkill, int iDiff)
        {
            string result = "";
            if (iReq == 2 || iReq == 4 || iReq == 6) result = "base ";
            switch (iReq) {
                case 1:
                case 2:
                case 8: result += InqSkillName(iSkill); break;
                case 3:
                case 4: result += InqAttributeName(iSkill); break;
                case 5:
                case 6: result += InqAttribute2ndName(iSkill); break;
                case 9:
                case 10:
                    switch (iSkill) {
                        case 287: result = "Standing with the Celestial Hand"; break;
                        case 288: result = "Standing with the Eldrytch Web"; break;
                        case 289: result = "Standing with the Radiant Blood"; break;
                        default: result = "unknown quality"; break;
                    }
                    break;
                case 7: result = "level"; break;
                case 11: result = InqCreatureDisplayName(iDiff); break;
                case 12:
                    {
                        string heritage_group = "";
                        if (InqHeritageGroupDisplayName(iDiff, ref heritage_group))
                            result = heritage_group;
                        break;
                    }

            }

            return result;
        }

        private string InqSkillName(int iSkill)
        {
            return SkillExtensions.GetSkillName((Skill)iSkill);
        }

        private string InqAttributeName(int iSkill)
        {
            switch (iSkill)
            {
                case 1:
                    return "Strength";
                case 2:
                    return "Endurance";
                case 3:
                    return "Quickness";
                case 4:
                    return "Coordination";
                case 5:
                    return "Focus";
                case 6:
                    return "Self";
            }
            return "";
        }

        private string InqAttribute2ndName(int iSkill)
        {
            switch (iSkill)
            {
                case 1: return "Maximum Health";
                case 2: return "Health";
                case 3: return "Maximum Stamina";
                case 4: return "Stamina";
                case 5: return "Maximum Mana";
                case 6: return "Mana";
            }
            return "";
        }

        private string InqCreatureDisplayName(int iType)
        {
            switch (iType)
            {
                case 1: return "Olthoi";
                case 2: return "Banderling";
                case 3: return "Drudge";
                case 4: return "Mosswart";
                case 5: return "Lugian";
                case 6: return "Tumerok";
                case 7: return "Mite";
                case 8: return "Tusker";
                case 9: return "Phyntos_Wasp";
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
                case 27: return "Shallows_Shark";
                case 28: return "Monouga";
                case 29: return "Zefir";
                case 30: return "Skeleton";
                case 31: return "Human";
                case 32: return "Shreth";
                case 33: return "Chittick";
                case 34: return "Moarsman";
                case 35: return "Olthoi_Larvae";
                case 36: return "Slithis";
                case 37: return "Deru";
                case 38: return "Fire_Elemental";
                case 39: return "Snowman";
                case 40: return "Unknown";
                case 41: return "Bunny";
                case 42: return "Lightning_Elemental";
                case 43: return "Rockslide";
                case 44: return "Grievver";
                case 45: return "Niffis";
                case 46: return "Ursuin";
                case 47: return "Crystal";
                case 48: return "Hollow_Minion";
                case 49: return "Scarecrow";
                case 50: return "Idol";
                case 51: return "Empyrean";
                case 52: return "Hopeslayer";
                case 53: return "Doll";
                case 54: return "Marionette";
                case 55: return "Carenzi";
                case 56: return "Siraluun";
                case 57: return "Aun_Tumerok";
                case 58: return "Hea_Tumerok";
                case 59: return "Simulacrum";
                case 60: return "Acid_Elemental";
                case 61: return "Frost_Elemental";
                case 62: return "Elemental";
                case 63: return "Statue";
                case 64: return "Wall";
                case 65: return "Altered_Human";
                case 66: return "Device";
                case 67: return "Harbinger";
                case 68: return "Dark_Sarcophagus";
                case 69: return "Chicken";
                case 70: return "Gotrok_Lugian";
                case 71: return "Margul";
                case 72: return "Bleached_Rabbit";
                case 73: return "Nasty_Rabbit";
                case 74: return "Grimacing_Rabbit";
                case 75: return "Burun";
                case 76: return "Target";
                case 77: return "Ghost";
                case 78: return "Fiun";
                case 79: return "Eater";
                case 80: return "Penguin";
                case 81: return "Ruschk";
                case 82: return "Thrungus";
                case 83: return "Viamontian_Knight";
                case 84: return "Remoran";
                case 85: return "Swarm";
                case 86: return "Moar";
                case 87: return "Enchanted_Arms";
                case 88: return "Sleech";
                case 89: return "Mukkir";
                case 90: return "Merwart";
                case 91: return "Food";
                case 92: return "Paradox_Olthoi";
                case 93: return "Harvest";
                case 94: return "Energy";
                case 95: return "Apparition";
                case 96: return "Aerbax";
                case 97: return "Touched";
                case 98: return "Blighted_Moarsman";
                case 99: return "Gear_Knight";
                case 100: return "Gurog";
                case 101: return "A'nekshay";
            }
            return "";
        }

        // Thanks to ACE for these two functions! 
        private int ItemTotalXPToLevel(long _gained_xp, long _base_xp, int _max_level, int _xp_scheme)
        {
            var level = 0;

            switch (_xp_scheme)
            {
                case 1:
                    level = (int)Math.Floor((double)_gained_xp / _base_xp);
                    break;

                case 2:

                    var levelXP = _base_xp;
                    var remainXP = _gained_xp;

                    while (remainXP >= levelXP)
                    {
                        level++;

                        remainXP -= levelXP;
                        levelXP *= 2;
                    }
                    break;

                case 3:

                    if (_gained_xp >= _base_xp && _gained_xp < _base_xp * 3)
                        level = 1;
                    else
                        level = (int)Math.Floor((double)(_gained_xp - _base_xp) / _base_xp);

                    break;
            }

            if (level > _max_level)
                level = _max_level;

            return level;
        }

        public static long ItemLevelToTotalXP(int itemLevel, long baseXP, int maxLevel, int xpScheme)
        {
            if (itemLevel < 1)
                return 0;

            if (itemLevel > maxLevel)
                itemLevel = maxLevel;

            if (itemLevel == 1)
                return baseXP;

            switch (xpScheme)
            {
                case 1:
                    return (long)itemLevel * baseXP;

                case 2:
                default:
                    var levelXP = baseXP;
                    var totalXP = baseXP;

                    for (var i = itemLevel - 1; i > 0; i--)
                    {
                        levelXP *= 2;
                        totalXP += levelXP;
                    }

                    return totalXP;

                case 3:

                    return (long)itemLevel * baseXP + baseXP;
            }
        }

        public float GetElementalModPKModifier(float elementalModifier)
        {
            float CombatSystem__ElementalModPKModifier = 0.25F;
            return ((elementalModifier - 1.0F) * CombatSystem__ElementalModPKModifier + 1.0F);
        }

        /*
         * This code would return based on the % chance sent by the server. 
         * We're going to assume a skill level of 200 for this.
         */
        public string pseudo_LockpickSuccessPercentToString(int resistance)
        {
            int lockpick_skill = 200;
            var lr = GetSkillChance(lockpick_skill, resistance) * 100;
            if (lr <= 0) return "impossible";
            if (lr < 5) return "ridiculously difficult";
            if (lr < 15) return "extremely difficult";
            if (lr < 35) return "quite difficult";
            if (lr < 50) return "difficult";
            if (lr < 70) return "challenging";
            if (lr < 85) return "mildly challenging";
            if (lr < 95) return "easy";

            return "trivial";
        }

        public double GetSkillChance(int skill, int difficulty, float factor = 0.03f)
        {
            var chance = 1.0 - (1.0 / (1.0 + Math.Exp(factor * (skill - difficulty))));
            return Math.Min(1.0, Math.Max(0.0, chance));
        }

        public string InqWorkmanshipAdjective(int wlevel, int iGemType)
        {
            /*
            if (wlevel > 10) {
                wlevel = 10;
            }

            string workmanship = getWorkmanship(wlevel);
            if ($wlevel <= 4){
                if ($isGem == true){
				$workmanship.= "cut";
                }else
                {
				$workmanship.= "crafted";
                }
            }
            return $workmanship;
            */
            return "InqWorkmanshipAdjective--TODO";

        }

        public string getWorkmanship(int wlevel)
        { 
            string workmanship = "";
            switch (wlevel)
            {
			    case 1: workmanship = "Poorly "; break;
			    case 2: workmanship = "Well-"; break;
			    case 3: workmanship = "Finely "; break;
			    case 4: workmanship = "Exquisitely "; break;
			    case 5: workmanship = "Magnificent "; break;
			    case 6: workmanship = "Nearly flawless "; break;
			    case 7: workmanship = "Flawless "; break; 
			    case 8: workmanship = "Utterly flawless "; break;
			    case 9: workmanship = "Incomparable "; break; 
			    case 10: workmanship = "Priceless "; break;
            }
            return workmanship;
        }

    }
}
