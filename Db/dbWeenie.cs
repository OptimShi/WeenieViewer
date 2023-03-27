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

        public List<CreateListItem> CreateList;
        public List<CreateListItem> SoldBy;
        public List<Position> Positions;

        public List<Emote> Emotes;

        public bool IsCreature()
        {
            if (Bools.ContainsKey(PropertyBool.NPC_LOOKS_LIKE_OBJECT_BOOL) && Bools[PropertyBool.NPC_LOOKS_LIKE_OBJECT_BOOL] == true)
                return false;

            if (Ints.ContainsKey(PropertyInt.ITEM_TYPE_INT) && Ints[PropertyInt.ITEM_TYPE_INT] == 16) // ItemType.Creature
                return true;


            return false;
        }

        public int GetSkillLevel(int skillID)
        {
            if (!Skills.ContainsKey(skillID)) return 0;

            int STRENGTH = 1;
            int ENDURANCE = 2;
            int QUICKNESS = 3;
            int COORDINATION = 4;
            int FOCUS = 5;
            int SELF = 6;

            int skill_base = Skills[skillID].init_level;

            double value;

            switch (skillID)
            {
                case 1: // Axe
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 2: // Bow
                    value = (Attributes[COORDINATION].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 3: // Crossbow
                    value = (Attributes[COORDINATION].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 4: // Dagger
                    value = (Attributes[QUICKNESS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 5: // Mace
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 6: // Melee Defense
                    value = (Attributes[QUICKNESS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 7: // Missile Defense
                    value = (Attributes[QUICKNESS].init_level + Attributes[COORDINATION].init_level) / 5 + skill_base;
                    return (int)Math.Ceiling(value);
                case 9: // Spear
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 10: // Staff
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 11: // Sword
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 12: // Thrown Weapons
                    value = (Attributes[COORDINATION].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 13: // Unarmed Combat
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 14: // Arcane Lore
                    value = (Attributes[FOCUS].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 15: // Magic Defense
                    value = (Attributes[SELF].init_level + Attributes[FOCUS].init_level) / 7 + skill_base;
                    return (int)Math.Ceiling(value);
                case 16: // Mana Conversion
                    value = (Attributes[SELF].init_level + Attributes[FOCUS].init_level) / 6 + skill_base;
                    return (int)Math.Ceiling(value);
                case 18: // Item Tinkering
                    value = (Attributes[FOCUS].init_level) + skill_base;
                    return (int)Math.Ceiling(value);
                case 19: // Assess Person
                    value = skill_base;
                    return (int)Math.Ceiling(value);
                case 20: // Deception
                    value = skill_base;
                    return (int)Math.Ceiling(value);
                case 21: // Healing
                    value = (Attributes[FOCUS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 22: // Jump
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 23: // Lockpick
                    value = (Attributes[FOCUS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 24: // Run
                    value = (Attributes[QUICKNESS].init_level) + skill_base;
                    return (int)Math.Ceiling(value);
                case 27: // Assess Creature
                    value = skill_base;
                    return (int)Math.Ceiling(value);
                case 28: // Weapon Tinkering
                    value = (Attributes[FOCUS].init_level + Attributes[STRENGTH].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 29: // Armor Tinkering
                    value = (Attributes[FOCUS].init_level + Attributes[ENDURANCE].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 30: // Magic Item Tinkering
                    value = (Attributes[FOCUS].init_level) + skill_base;
                    return (int)Math.Ceiling(value);
                case 31: // Creature Enchantment
                    value = (Attributes[FOCUS].init_level + Attributes[SELF].init_level) / 4 + skill_base;
                    return (int)Math.Ceiling(value);
                case 32: // Item Enchantment
                    value = (Attributes[FOCUS].init_level + Attributes[SELF].init_level) / 4 + skill_base;
                    return (int)Math.Ceiling(value);
                case 33: // Life Magic
                    value = (Attributes[FOCUS].init_level + Attributes[SELF].init_level) / 4 + skill_base;
                    return (int)Math.Ceiling(value);
                case 34: // War Magic
                    value = (Attributes[FOCUS].init_level + Attributes[SELF].init_level) / 4 + skill_base;
                    return (int)Math.Ceiling(value);
                case 35: // Leadership
                    value = skill_base;
                    return (int)Math.Ceiling(value);
                case 36: // Loyalty
                    value = skill_base;
                    return (int)Math.Ceiling(value);
                case 37: // Fletching
                    value = (Attributes[FOCUS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 38: // Alchemy
                    value = (Attributes[FOCUS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 39: // Cooking
                    value = (Attributes[FOCUS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 40: // Salvaging
                    value = skill_base;
                    return (int)Math.Ceiling(value);
                case 41: // Two Handed Combat
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 43: // Void Magic
                    value = (Attributes[FOCUS].init_level + Attributes[SELF].init_level) / 4 + skill_base;
                    return (int)Math.Ceiling(value);
                case 44: // Heavy Weapons
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 45: // Light Weapons
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 46: // Finesse Weapons
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 47: // Missile Weapons
                    value = Attributes[COORDINATION].init_level / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 48: // Shield
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 2 + skill_base;
                    return (int)Math.Ceiling(value);
                case 49: // Dual Wield
                    value = (Attributes[COORDINATION].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 50: // Recklessness
                    value = (Attributes[STRENGTH].init_level + Attributes[QUICKNESS].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 51: // Sneak Attack
                    value = (Attributes[QUICKNESS].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 52: // Dirty Fighting
                    value = (Attributes[STRENGTH].init_level + Attributes[COORDINATION].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                case 54: // Summoning					
                    value = (Attributes[ENDURANCE].init_level + Attributes[SELF].init_level) / 3 + skill_base;
                    return (int)Math.Ceiling(value);
                default:
                    return skill_base;
            }
        }

        private int GetAttributeValue(int attribute)
        {
            if (Attributes.ContainsKey(attribute))
                return Attributes[attribute].init_level;

            return 0;
        }
    }
}
