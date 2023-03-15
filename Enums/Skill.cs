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
                case 6: return "Melee Defense";
                case 7: return "Missile Defense";
                case 14: return "Arcane Lore";
                case 15: return "Magic Defense";
                case 16: return "Mana Conversion";
                case 18: return "Item Tinkering";
                case 19: return "Assess Person";
                case 20: return "Deception";
                case 21: return "Healing";
                case 22: return "Jump";
                case 23: return "Lockpick";
                case 24: return "Run";
                case 27: return "Assess Creature";
                case 28: return "Weapon Tinkering";
                case 29: return "Armor Tinkering";
                case 30: return "Magic Item Tinkering";
                case 31: return "Creature Enchantment";
                case 32: return "Item Enchantment";
                case 33: return "Life Magic";
                case 34: return "War Magic";
                case 35: return "Leadership";
                case 36: return "Loyalty";
                case 37: return "Fletching";
                case 38: return "Alchemy";
                case 39: return "Cooking";
                case 40: return "Salvaging";
                case 41: return "Two Handed Combat";
                case 43: return "Void Magic";
                case 44: return "Heavy Weapons";
                case 45: return "Light Weapons";
                case 46: return "Finesse Weapons";
                case 47: return "Missile Weapons";
                case 48: return "Shield";
                case 49: return "Dual Wield";
                case 50: return "Recklessness";
                case 51: return "Sneak Attack";
                case 52: return "Dirty Fighting";
                case 54: return "Summoning";
            }
            return "";
        }
    }
}
