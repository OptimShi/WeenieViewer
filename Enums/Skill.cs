using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WeenieViewer.Enums
{
    public enum Skill
    {
        None,
        Axe,                 /* Retired */
        Bow,                 /* Retired */
        Crossbow,            /* Retired */
        Dagger,              /* Retired */
        Mace,                /* Retired */
        MeleeDefense,
        MissileDefense,
        Sling,               /* Retired */
        Spear,               /* Retired */
        Staff,               /* Retired */
        Sword,               /* Retired */
        ThrownWeapon,        /* Retired */
        UnarmedCombat,       /* Retired */
        ArcaneLore,
        MagicDefense,
        ManaConversion,
        Spellcraft,          /* Unimplemented */
        ItemTinkering,
        AssessPerson,
        Deception,
        Healing,
        Jump,
        Lockpick,
        Run,
        Awareness,           /* Unimplemented */
        ArmsAndArmorRepair,  /* Unimplemented */
        AssessCreature,
        WeaponTinkering,
        ArmorTinkering,
        MagicItemTinkering,
        CreatureEnchantment,
        ItemEnchantment,
        LifeMagic,
        WarMagic,
        Leadership,
        Loyalty,
        Fletching,
        Alchemy,
        Cooking,
        Salvaging,
        TwoHandedCombat,
        Gearcraft,           /* Retired */
        VoidMagic,
        HeavyWeapons,
        LightWeapons,
        FinesseWeapons,
        MissileWeapons,
        Shield,
        DualWield,
        Recklessness,
        SneakAttack,
        DirtyFighting,
        Challenge,          /* Unimplemented */
        Summoning
    }

    public static class SkillExtensions
    {
        /// <summary>
        /// Will add a space infront of capital letter words in a string
        /// Taken from ACE
        /// </summary>
        /// <param name="skill"></param>
        /// <returns>string with spaces infront of capital letters</returns>
        public static string ToSentence(this Skill skill)
        {
            return new string(skill.ToString().ToCharArray().SelectMany((c, i) => i > 0 && char.IsUpper(c) ? new char[] { ' ', c } : new char[] { c }).ToArray());
        }

        public static string GetSkillName(Skill skill)
        {
            switch ((int)skill)
            {
                case 6: return "Melee Defense"; break;
                case 7: return "Missile Defense"; break;
                case 14: return "Arcane Lore"; break;
                case 15: return "Magic Defense"; break;
                case 16: return "Mana Conversion"; break;
                case 18: return "Item Tinkering"; break;
                case 19: return "Assess Person"; break;
                case 20: return "Deception"; break;
                case 21: return "Healing"; break;
                case 22: return "Jump"; break;
                case 23: return "Lockpick"; break;
                case 24: return "Run"; break;
                case 27: return "Assess Creature"; break;
                case 28: return "Weapon Tinkering"; break;
                case 29: return "Armor Tinkering"; break;
                case 30: return "Magic Item Tinkering"; break;
                case 31: return "Creature Enchantment"; break;
                case 32: return "Item Enchantment"; break;
                case 33: return "Life Magic"; break;
                case 34: return "War Magic"; break;
                case 35: return "Leadership"; break;
                case 36: return "Loyalty"; break;
                case 37: return "Fletching"; break;
                case 38: return "Alchemy"; break;
                case 39: return "Cooking"; break;
                case 40: return "Salvaging"; break;
                case 41: return "Two Handed Combat"; break;
                case 43: return "Void Magic"; break;
                case 44: return "Heavy Weapons"; break;
                case 45: return "Light Weapons"; break;
                case 46: return "Finesse Weapons"; break;
                case 47: return "Missile Weapons"; break;
                case 48: return "Shield"; break;
                case 49: return "Dual Wield"; break;
                case 50: return "Recklessness"; break;
                case 51: return "Sneak Attack"; break;
                case 52: return "Dirty Fighting"; break;
                case 54: return "Summoning"; break;
            }
            return "";
        }
    }
}
