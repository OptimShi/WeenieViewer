using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WeenieViewer.Enums;

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
            var v2 = time / 0x278D00; // months
            var v3 = time % 0x278D00 / 0x15180; // days
            var v4 = time % 0x278D00 % 0x15180;
            var v5 = v4 / 0xE10; // hours
            v4 %= 0xE10; 
            var v12 = v4 % 0x3C; // seconds
            var v13 = v4 / 0x3C; // minutes
            var buf = "";
            return "COOLDOWN_TIME_TODO";
            /*
            if (sprintf("%d", v2) > 0)
            $buf.= sprintf("%dmo ", $v2);
            if (sprintf("%d", $v3) > 0)
            $buf.= sprintf("%dd ", $v3);
            if (sprintf("%d", $v5) > 0)
            $buf.= sprintf("%dh ", $v5);
            if (sprintf("%d", $v13) > 0)
            $buf.= sprintf("%dm ", $v13);
        $buf.= sprintf("%ds ", $v12);
            return $buf;
            */
        }
    }
}
