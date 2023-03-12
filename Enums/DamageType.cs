using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace WeenieViewer.Enums
{
    // Taken from ACE 
    public enum DamageType
    {
        Undef = 0x0,
        Slash = 0x1,
        Pierce = 0x2,
        Bludgeon = 0x4,
        Cold = 0x8,
        Fire = 0x10,
        Acid = 0x20,
        Electric = 0x40,
        Health = 0x80,
        Stamina = 0x100,
        Mana = 0x200,
        Nether = 0x400,
        Prismatic = 0x10000000,
        //Base = 0x10000000,

        // helpers
        Physical = Slash | Pierce | Bludgeon,
        Elemental = Cold | Fire | Acid | Electric,
    };

    public static class DamageTypeExtensions
    {
        public static string GetName(this DamageType damageType)
        {
            switch (damageType)
            {
                case DamageType.Undef: return "Undefined";
                case DamageType.Slash: return "Slashing";
                case DamageType.Pierce: return "Piercing";
                case DamageType.Bludgeon: return "Bludgeoning";
                case DamageType.Cold: return "Cold";
                case DamageType.Fire: return "Fire";
                case DamageType.Acid: return "Acid";
                case DamageType.Electric: return "Electric";
                case DamageType.Health: return "Health";
                case DamageType.Stamina: return "Stamina";
                case DamageType.Mana: return "Mana";
                case DamageType.Nether: return "Nether";
                case DamageType.Prismatic: return "Prismatic";
                //case DamageType.Base: return "Base";
                default:
                    return null;
            }
        }

        public static string GetDamageTypes(this DamageType damageType)
        {
            string damageTypeString = "";
            foreach (DamageType type in Enum.GetValues(typeof(DamageType)))
            {
                if ((damageType & type) > 0){
                    damageType = damageType & ~type; // remove the current type from the full damage type .. 
                    if (damageTypeString != ""){
                        damageTypeString += '/' + GetName(type);
                        return damageTypeString;
                    }
                    else
                    {
                        damageTypeString = GetName(type);
                    }
                }

            }

            return damageTypeString;
        }
    }
}
