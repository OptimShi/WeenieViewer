using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml.Linq;
using WeenieViewer.Db;
using WeenieViewer.Enums;

namespace WeenieViewer.Appraisal
{
    public class ItemExamine
    {
        public string Text;
        private dbWeenie Weenie;

        public ItemExamine(dbWeenie weenie)
        {
            Weenie = weenie;
            /*
             * ItemExamineUI::Appraisal_ShowValueInfo
             * ItemExamineUI::Appraisal_ShowBurdenInfo
             * ItemExamineUI::Appraisal_ShowTinkeringInfo
             * ItemExamineUI::Appraisal_ShowSet
             * ItemExamineUI::Appraisal_ShowRatings
             * ItemExamineUI::Appraisal_ShowWeaponAndArmorData
             * ItemExamineUI::Appraisal_ShowDefenseModData
             * ItemExamineUI::Appraisal_ShowArmorMods
             * ItemExamineUI::Appraisal_ShowShortMagicInfo
             * ItemExamineUI::Appraisal_ShowSpecialProperties
             * ItemExamineUI::Appraisal_ShowUsage
             * ItemExamineUI::Appraisal_ShowLevelLimitInfo
             * ItemExamineUI::Appraisal_ShowWieldRequirements
             * ItemExamineUI::Appraisal_ShowUsageLimitInfo
             * ItemExamineUI::Appraisal_ShowItemLevelInfo
             * ItemExamineUI::Appraisal_ShowActivationRequirements
             * ItemExamineUI::Appraisal_ShowCasterData
             * ItemExamineUI::Appraisal_ShowBoostValue
             * ItemExamineUI::Appraisal_ShowHealKitValues
             * ItemExamineUI::Appraisal_ShowCapacity
             * ItemExamineUI::Appraisal_ShowLockAppraiseInfo
             * ItemExamineUI::Appraisal_ShowManaStoneInfo
             * ItemExamineUI::Appraisal_ShowRemainingUses
             * ItemExamineUI::Appraisal_ShowCraftsman
             * if ( AppraisalProfile::InqBool(v9, 0x45u, (int *)&_prof) && !_prof )
             *   ItemExamineUI::AddItemInfo(v3, "This item cannot be sold.", 0, 1);
             * ItemExamineUI::Appraisal_ShowRareInfo(v3, v9);
             * ItemExamineUI::Appraisal_ShowMagicInfo(v3, v9);
             * ItemExamineUI::Appraisal_ShowDescription(v3, v9);
             */

            Appraisal_ShowValueInfo();
            Appraisal_ShowBurdenInfo();
            Appraisal_ShowTinkeringInfo(); // TODO
            bool hasSet = Appraisal_ShowSet();
            bool hasRatings = Appraisal_ShowRatings();
            if (hasSet || hasRatings)
                AddItemInfo(""); // Add a blank line
            Appraisal_ShowWeaponAndArmorData();
            Appraisal_ShowDefenseModData();
        }
        /*
         * 	Line  10308: int __thiscall AppraisalProfile::InqCreature(AppraisalProfile *this, CreatureAppraisalProfile *cap); // idb
	Line  10322: int __thiscall AppraisalProfile::InqArmor(AppraisalProfile *this, ArmorProfile *aap); // idb
	Line  10330: int __thiscall AppraisalProfile::InqWeapon(AppraisalProfile *this, WeaponProfile *wap); // idb
	Line  10331: int __thiscall AppraisalProfile::InqInt(AppraisalProfile *this, unsigned int stype, int *retval); // idb
	Line  10332: int __thiscall AppraisalProfile::InqInt64(AppraisalProfile *this, unsigned int stype, __int64 *retval); // idb
	Line  10333: int __thiscall AppraisalProfile::InqBool(AppraisalProfile *this, unsigned int stype, int *retval); // idb
	Line  10334: int __thiscall AppraisalProfile::InqFloat(AppraisalProfile *this, unsigned int stype, long double *retval); // idb
	Line  10335: int __thiscall AppraisalProfile::InqDataID(AppraisalProfile *this, unsigned int stype, IDClass<_tagDataID,32,0> *retval); // idb
	Line  10337: int __thiscall AppraisalProfile::InqString(AppraisalProfile *this, unsigned int stype, AC1Legacy::PStringBase<char> *retval); // idb

        */

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
            if (v1 < 1){
			    v1 = v1 * -1;
            }
            string g_szPecentText = $"{Math.Floor(v1 * 100.0 + 0.5)}%";
            return g_szPecentText;
        }

        private string SmallModifierToString(float rMod)
        {
		    var v1 = 1.0 - rMod;
            if (1.0 - rMod < 0.0 )
			    v1 = v1 * -1;

		    string g_szPecentText = $"{(v1 * 100.0):N1}%";
            return g_szPecentText;
        }

        private string WeaponTimeToString(float wtime)
        {
            if (wtime < 11)
			    return "Very Fast";
            else if(wtime < 31)
			    return "Fast";
            else if(wtime < 50)
                return "Average";
            else if(wtime < 80)
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

        private void AddItemInfo(string text, bool surpressDoubleSpacing = true)
        {
            Text += text + "\n";
            if (!surpressDoubleSpacing) Text += "\n";
        }
        private bool SkillToString(Skill skill, ref string value)
        {
            value = SkillExtensions.ToSentence(skill);
            if(value != "")
                return true;

            return false;
        }

        private void Appraisal_ShowValueInfo()
        {
            int val = 0;

            if(InqInt((PropertyInt)0x13u, ref val))
                AddItemInfo("Value: " + val.ToString("N0"));
            else
                AddItemInfo("Value: ???");
        }

        private void Appraisal_ShowBurdenInfo()
        {
            int val = 0;
            if(InqInt((PropertyInt)5u, ref val))
                AddItemInfo("Burder: " + val.ToString("N0"));
            else
                AddItemInfo("Burden: Unknown");

            AddItemInfo(""); // Insert a blank line
        }

        private void Appraisal_ShowTinkeringInfo()
        {
            int cTinkers = 0;
            if (InqInt((PropertyInt)0xABu, ref cTinkers))
            {
                string plural = "";
                if(cTinkers > 1)
                    plural = "s"; // if it has multiple tinks
                AddItemInfo($"This item has been tinkered {cTinkers} time{plural}.");
            }
            string strTinkerer = "";
            if (InqString((PropertyString)0x27u, ref strTinkerer))
                AddItemInfo($"Last tinkered by {strTinkerer}.");

            string strImbuer = "";
            if (InqString((PropertyString)0x28u, ref strImbuer))
                AddItemInfo($"Imbued by {strImbuer}.");
            /*
            int iWorkmanship = 0;
            if (InqInt((PropertyInt)0x69u, ref iWorkmanship))
            {
                int iNumItems = 0;
                if (InqInt((PropertyInt)0xAAu, ref iNumItems))
                {
                    double fAvg = (double)iWorkmanship / (double)iNumItems;
                    iWorkmanship = fAvg + 0.5;
                    strWorkmanship.m_buffer = (AC1Legacy::PSRefBuffer<char>*)AC1Legacy::PStringBase<char>::s_NullBuffer;
                    InterlockedIncrement((volatile LONG*)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
                    AppraisalSystem::InqWorkmanshipAdjective(iWorkmanship, &strWorkmanship, 0);
                    __snprintf(
                      numtxt,
                      0x7E8u,
                      "Workmanship: %s (%0.2f)\n\nSalvaged from %d items.",
                      strWorkmanship.m_buffer->m_data,
                      fAvg,
                      iNumItems);
                }
                else
                {
                    strWorkmanship.m_buffer = (AC1Legacy::PSRefBuffer<char>*)AC1Legacy::PStringBase<char>::s_NullBuffer;
                    InterlockedIncrement((volatile LONG*)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
                    AppraisalSystem::InqWorkmanshipAdjective(iWorkmanship, &strWorkmanship, 0);
                    __snprintf(numtxt, 0x7E8u, "Workmanship: %s (%d)", strWorkmanship.m_buffer->m_data, iWorkmanship);
                }
                v5 = strWorkmanship.m_buffer;
                if (!InterlockedDecrement((volatile LONG*)&strWorkmanship.m_buffer->m_cRef) && v5 )
      v5->vfptr->__vecDelDtor((ReferenceCountTemplate < 268435456, 0 > *)v5, 1u);
                ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
            }
            ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
            v6 = strImbuer.m_buffer;
            if (!InterlockedDecrement((volatile LONG*)&strImbuer.m_buffer->m_cRef) && v6 )
    v6->vfptr->__vecDelDtor((ReferenceCountTemplate < 268435456, 0 > *)v6, 1u);
            v7 = strTinkerer.m_buffer;
            if (!InterlockedDecrement((volatile LONG*)&strTinkerer.m_buffer->m_cRef) )
  {
                if (v7)
                    v7->vfptr->__vecDelDtor((ReferenceCountTemplate < 268435456, 0 > *)v7, 1u);
            }
        }
            */
    }

    private bool Appraisal_ShowSet()
        {
            int setBonus = 0;
            if (InqInt((PropertyInt)0x109u, ref setBonus))
            {
                string setName = "";
                switch (setBonus)
                {
                    //case 1: setName = "SpellSetID_EnchantmentVersion"; break;
                    //case 2: setName = "Test_EquipmentSet"; break;
                    case 4: setName = "Carraida's Benediction"; break;
                    case 5: setName = "Noble Relic"; break;
                    case 6: setName = "Ancient Relic"; break;
                    case 7: setName = "Relic Alduressa"; break;
                    case 8: setName = "Shou-jen"; break;
                    case 9: setName = "Empyrean Rings"; break;
                    case 10: setName = "Arm, Mind, Heart"; break;
                    case 11: setName = "Coat of the Perfect Light"; break;
                    case 12: setName = "Leggings of Perfect Light"; break;
                    case 13: setName = "Soldier's"; break;
                    case 14: setName = "Adept's"; break;
                    case 15: setName = "Archer's"; break;
                    case 16: setName = "Defender's"; break;
                    case 17: setName = "Tinker's"; break;
                    case 18: setName = "Crafter's"; break;
                    case 19: setName = "Hearty"; break;
                    case 20: setName = "Dexterous"; break;
                    case 21: setName = "Wise"; break;
                    case 22: setName = "Swift"; break;
                    case 23: setName = "Hardenend"; break;
                    case 24: setName = "Reinforced"; break;
                    case 25: setName = "Interlocking"; break;
                    case 26: setName = "Flame Proof"; break;
                    case 27: setName = "Acid Proof"; break;
                    case 28: setName = "Cold Proof"; break;
                    case 29: setName = "Lightning Proof"; break;
                    case 30: setName = "Dedication"; break;
                    case 31: setName = "Gladiatorial Clothing"; break;
                    case 32: setName = "Ceremonial Clothing"; break;
                    case 33: setName = "Protective Clothing"; break;
                    //case 34: setName = "NoobieArmor_EquipmentSet"; break;
                    case 35: setName = "Sigil of Defense"; break;
                    case 36: setName = "Sigil of Destruction"; break;
                    case 37: setName = "Sigil of Fury"; break;
                    case 38: setName = "Sigil of Growth"; break;
                    case 39: setName = "Sigil of Vigor"; break;
                    case 40: setName = "Heroic Protector"; break;
                    case 41: setName = "Heroic Destroyer"; break;
                    //case 42: setName = "OlthoiArmorDRed_Set"; break;
                    //case 43: setName = "OlthoiArmorCRat_Set"; break;
                    //case 44: setName = "OlthoiArmorCRed_Set"; break;
                    //case 45: setName = "OlthoiArmorDRat_Set"; break;
                    //case 46: setName = "AlduressaRelicUpgrade_EquipmentSet"; break;
                    //case 47: setName = "Upgraded Ancient Relic"; break;
                    //case 48: setName = "NobleRelicUpgrade_EquipmentSet"; break;
                    case 49: setName = "Weave of Alchemy"; break;
                    case 50: setName = "Weave of Arcane Lore"; break;
                    case 51: setName = "Weave of Armor Tinkering"; break;
                    case 52: setName = "Weave of Assess Person"; break;
                    case 53: setName = "Weave of Light Weapons"; break;
                    case 54: setName = "Weave of Missile Weapons"; break;
                    case 55: setName = "Weave of Cooking"; break;
                    case 56: setName = "Weave of Creature Enchantment"; break;
                    case 57: setName = "Weave of Missile Weapons"; break;
                    case 58: setName = "Weave of Finesse"; break;
                    case 59: setName = "Weave of Deception"; break;
                    case 60: setName = "Weave of Fletching"; break;
                    case 61: setName = "Weave of Healing"; break;
                    case 62: setName = "Weave of Item Enchantment"; break;
                    case 63: setName = "Weave of Item Tinkering"; break;
                    case 64: setName = "Weave of Leadership"; break;
                    case 65: setName = "Weave of Life Magic"; break;
                    case 66: setName = "Weave of Loyalty"; break;
                    case 67: setName = "Weave of Light Weapons"; break;
                    case 68: setName = "Weave of Magic Defense"; break;
                    case 69: setName = "Weave of Magic Item Tinkering"; break;
                    case 70: setName = "Weave of Mana Conversion"; break;
                    case 71: setName = "Weave of Melee Defense"; break;
                    case 72: setName = "Weave of Missile Defense"; break;
                    case 73: setName = "Weave of Salvaging"; break;
                    case 74: setName = "Weave of Light Weapons"; break;
                    case 75: setName = "Weave of Light Weapons"; break;
                    case 76: setName = "Weave of Heavy Weapons"; break;
                    case 77: setName = "Weave of Missile Weapons"; break;
                    case 78: setName = "Weave of Two Handed Combat"; break;
                    case 79: setName = "Weave of Light Weapons"; break;
                    case 80: setName = "Weave of Void Magic"; break;
                    case 81: setName = "Weave of War Magic"; break;
                    case 82: setName = "Weave of Weapon Tinkering"; break;
                    case 83: setName = "Weave of Assess Creature "; break;
                    case 84: setName = "Weave of Dirty Fighting"; break;
                    case 85: setName = "Weave of Dual Wield"; break;
                    case 86: setName = "Weave of Recklessness"; break;
                    case 87: setName = "Weave of Shield"; break;
                    case 88: setName = "Weave of Sneak Attack"; break;
                    case 89: setName = "Shou-Jen Shozoku"; break;
                    case 90: setName = "Weave of Summoning"; break;
                    case 91: setName = "Shrouded Soul"; break;
                    case 92: setName = "Darkened Mind"; break;
                    case 93: setName = "Clouded Spirit"; break;
                    case 94: setName = "Minor Stinging Shrouded Soul"; break;
                    case 95: setName = "Minor Sparking Shrouded Soul"; break;
                    case 96: setName = "Minor Smoldering Shrouded Soul"; break;
                    case 97: setName = "Minor Shivering Shrouded Soul"; break;
                    case 98: setName = "Minor Stinging Darkened Mind"; break;
                    case 99: setName = "Minor Sparking Darkened Mind"; break;
                    case 100: setName = "Minor Smoldering Darkened Mind"; break;
                    case 101: setName = "Minor Shivering Darkened Mind"; break;
                    case 102: setName = "Minor Stinging Clouded Spirit"; break;
                    case 103: setName = "Minor Sparking Clouded Spirit"; break;
                    case 104: setName = "Minor Smoldering Clouded Spirit"; break;
                    case 105: setName = "Minor Shivering Clouded Spirit"; break;
                    case 106: setName = "Major Stinging Shrouded Soul"; break;
                    case 107: setName = "Major Sparking Shrouded Soul"; break;
                    case 108: setName = "Major Smoldering Shrouded Soul"; break;
                    case 109: setName = "Major Shivering Shrouded Soul"; break;
                    case 110: setName = "Major Stinging Darkened Mind"; break;
                    case 111: setName = "Major Sparking Darkened Mind"; break;
                    case 112: setName = "Major Smoldering Darkened Mind"; break;
                    case 113: setName = "Major Shivering Darkened Mind"; break;
                    case 114: setName = "Major Stinging Clouded Spirit"; break;
                    case 115: setName = "Major Sparking Clouded Spirit"; break;
                    case 116: setName = "Major Smoldering Clouded Spirit"; break;
                    case 117: setName = "Major Shivering Clouded Spirit"; break;
                    case 118: setName = "Blackfire Stinging Shrouded Soul"; break;
                    case 119: setName = "Blackfire Sparking Shrouded Soul"; break;
                    case 120: setName = "Blackfire Smoldering Shrouded Soul"; break;
                    case 121: setName = "Blackfire Shivering Shrouded Soul"; break;
                    case 122: setName = "Blackfire Stinging Darkened Mind"; break;
                    case 123: setName = "Blackfire Sparking Darkened Mind"; break;
                    case 124: setName = "Blackfire Smoldering Darkened Mind"; break;
                    case 125: setName = "Blackfire Shivering Darkened Mind"; break;
                    case 126: setName = "Blackfire Stinging Clouded Spirit"; break;
                    case 127: setName = "Blackfire Sparking Clouded Spirit"; break;
                    case 128: setName = "Blackfire Smoldering Clouded Spirit"; break;
                    case 129: setName = "Blackfire Shivering Clouded Spirit"; break;
                    case 130: setName = "Shimmering Shadows"; break;
                }

                if (setName != "")
                {
                    AddItemInfo("Set: " + setName, true);
                    return true;
                }

            }

            return false;
        }

        private bool Appraisal_ShowRatings()
        {
            int damage_rating = 0;
            int damage_resist_rating = 0;
            int crit_rating = 0;
            int crit_damage_rating = 0;
            int crit_resist_rating = 0;
            int crit_damage_resist_rating = 0;
            int healing_boost_rating = 0;
            int life_resist_rating = 0;
            int nether_resist_rating = 0;
            int gear_max_health = 0;
            InqInt((PropertyInt)0x172u, ref damage_rating);
            InqInt((PropertyInt)0x173u, ref damage_resist_rating);
            InqInt((PropertyInt)0x174u, ref crit_rating);
            InqInt((PropertyInt)0x176u, ref crit_damage_rating);
            InqInt((PropertyInt)0x175u, ref crit_resist_rating);
            InqInt((PropertyInt)0x177u, ref crit_damage_resist_rating);
            InqInt((PropertyInt)0x178u, ref healing_boost_rating);
            InqInt((PropertyInt)0x17Au, ref life_resist_rating);
            InqInt((PropertyInt)0x179u, ref nether_resist_rating);
            InqInt((PropertyInt)0x17Bu, ref gear_max_health);

            string output = "";

            if (damage_rating > 0)
                output += $"Dam {damage_rating}, ";
            if (damage_resist_rating > 0)
                output += $"Dam Resist {damage_resist_rating}, ";
            if (crit_rating > 0)
                output += $"Crit {crit_rating}, ";
            if (crit_damage_rating > 0)
                output += $"Crit Dam {crit_damage_rating}, ";
            if (crit_resist_rating > 0)
                output += $"Crit Dam Resist {crit_resist_rating}, ";
            if (healing_boost_rating > 0)
                output += $"Heal Boost {healing_boost_rating}, ";
            if (nether_resist_rating > 0)
                output += $"Nether Resist {nether_resist_rating}, ";
            if (life_resist_rating > 0)
                output += $"Life Resist {life_resist_rating}, ";

            if(output != "")
            {
                output = "Ratings: " + output.TrimEnd(new Char[] { ' ', ',' }) + "."; // remove the last ", " and add a perdiod
                AddItemInfo(output);
            }

            if(gear_max_health > 0)
                AddItemInfo($"This item adds {gear_max_health} Vitality.");

            if (output != "" || gear_max_health > 0)
            {
                AddItemInfo(""); // add an extra line
                return true;
            }

            return false;
        }

        void Appraisal_ShowWeaponAndArmorData()
        {
            int _valid_locations = 0; // GET THIS
            InqInt(PropertyInt.LOCATIONS_INT, ref _valid_locations);

            int _ammoType = 0;
            InqInt(PropertyInt.AMMO_TYPE_INT, ref _ammoType);

            if ((_valid_locations & 0x3F00000) > 0) // Weapon Slot
            {
                if ((_valid_locations & 0x200000) > 0)
                {
                    int shieldLevel = -1;
                    if (InqInt((PropertyInt)0x1Cu, ref shieldLevel))
                        AddItemInfo($"Base Shield Level: {shieldLevel}");
                    else
                        AddItemInfo("Shield Level: Unknown");
                }

                var IsMissile = ((_valid_locations & 0x400000) > 0) && (_ammoType > 0);

                int itemType = 0;
                InqInt(PropertyInt.ITEM_TYPE_INT, ref itemType);
                // Check if this is a weapon
                if (itemType == 1 || itemType == 256 || itemType == 257 || itemType == 32768 || itemType == 0x8101)
                {
                    bool missileSlot = (_valid_locations & 0x400000) > 0;
                    int oldSkill_Id = 0;

                    int iWeaponSkill = 0;
                    if (InqInt(PropertyInt.WEAPON_SKILL_INT, ref iWeaponSkill))
                    {
                        string ps = "Skill: ";
                        string rhs = "";
                        if (InqInt((PropertyInt)0x161u, ref oldSkill_Id))
                        {
                            switch (oldSkill_Id)
                            {
                                case 1: rhs = " (Unarmed Weapon)"; break;
                                case 2: rhs = " (Sword)"; break;
                                case 3: rhs = " (Axe)"; break;
                                case 4: rhs = " (Mace)"; break;
                                case 5: rhs = " (Spear)"; break;
                                case 6: rhs = " (Dagger)"; break;
                                case 7: rhs = " (Staff)"; break;
                                case 8: rhs = " (Bow)"; break;
                                case 9: rhs = " (Crossbow)"; break;
                                case 10: rhs = " (Thrown)"; break;
                            }
                        }
                        string weaponSkill = "";
                        SkillToString((Skill)iWeaponSkill, ref weaponSkill);
                        AddItemInfo(ps + weaponSkill + rhs);
                    }

                    string damageTxt;
                    if (IsMissile)
                        damageTxt = "Damage Bonus: ";
                    else
                        damageTxt = "Damage: ";

                    int weaponDamage = 0;
                    int _damageType = 0;

                    InqInt((PropertyInt)45, ref _damageType);
                    if (InqInt((PropertyInt)44, ref weaponDamage))
                    {
                        if (weaponDamage < 0)
                            AddItemInfo(damageTxt + "Unknown");
                        else
                        {
                            string Dest = "";
                            string buf;
                            if (!IsMissile)
                            {
                                Dest = ", unknown type";
                                if (weaponDamage > 0)
                                {
                                    buf = DamageTypeExtensions.GetDamageTypes((DamageType)_damageType);
                                    Dest = $", {buf}";
                                }
                            }
                            float damage_variance = 0;
                            InqFloat((PropertyFloat)22, ref damage_variance);
                            float rhs = (1.0f - damage_variance) * weaponDamage;

                            string ability_txt;
                            if ((weaponDamage - rhs) > 0.00019999999)
                            {
                                if (rhs >= 10.0)
                                    ability_txt = $"{damageTxt}{rhs:g4} - {weaponDamage}{Dest}";
                                else
                                    ability_txt = $"{damageTxt}{rhs:g3} - {weaponDamage}{Dest}";
                            }
                            else
                            {
                                ability_txt = $"{damageTxt}{weaponDamage}{Dest}";
                            }
                            AddItemInfo(ability_txt);
                        }
                    }
             
                int retval = 0;
                InqInt((PropertyInt)0xCCu, ref retval); // ELEMENTAL_DAMAGE_BONUS_INT
                if (retval > 0)
                {
                    string damageType = DamageTypeExtensions.GetDamageTypes((DamageType)_damageType);
                    string rhs = $"Elemental Damage Bonus: {retval}, {damageType}.";
                    AddItemInfo(rhs);
                }

                if (IsMissile)
                {
                    float damageMod = 0;
                    if (InqFloat(PropertyFloat.DAMAGE_MOD_FLOAT, ref damageMod)) {
                        string modifier_txt = ModifierToString(damageMod);
                        AddItemInfo($"Damage Modifier: {modifier_txt}.");
                    }
                }

                if((_valid_locations & 0x2500000) > 0) // Melee, Missile, Two-Handed
                {
                    int wap_weapon_time = 0;
                    InqInt(PropertyInt.WEAPON_TIME_INT, ref wap_weapon_time);
                    if(wap_weapon_time <= 0)
                    {
                        AddItemInfo("Speed:  Unknown");
                        if (IsMissile)
                            AddItemInfo("Range:  Unknown");
                    }
                    else
                    {
                        string ps = "Speed: " + WeaponTimeToString(wap_weapon_time) + " (" + wap_weapon_time + ")";
                        AddItemInfo(ps);
                        if (IsMissile)
                        {
                            float wap_max_velocity = 0;
                            InqFloat(PropertyFloat.MAXIMUM_VELOCITY_FLOAT, ref wap_max_velocity);
                            double fRange = Math.Pow(wap_max_velocity, 2.0) * 0.1020408163265306 * 1.094;
                            if (fRange > 85) fRange = 85; // Max Range

                            double range;
                            if (fRange >= 10)
                                range = fRange - (int)fRange % 5;
                            else
                                range = fRange;

                            AddItemInfo($"Range: {Math.Floor(range):N0} yds.");
                        }
                    }
                    }
                }

                if ((_valid_locations & 0x400000) > 0)
                {
                    switch (_ammoType)
                    {
                        case 1:
                            AddItemInfo("Uses arrows as ammunition.");
                            break;
                        case 2:
                            AddItemInfo("Uses quarrels as ammunition.");
                            break;
                        case 4:
                            AddItemInfo("Uses atlatl darts as ammunition.");
                            break;
                    }
                }
                else
                {
                    switch (_ammoType)
                    {
                        case 1:
                            AddItemInfo("Used as ammunition by bows.");
                            break;
                        case 2:
                            AddItemInfo("Used as ammunition by crossbows.");
                            break;
                        case 4:
                            AddItemInfo("Uses atlatl darts as atlatls.");
                            break;
                    }
                }

                /*
                 * _sprintf(&ability_txt, "Bonus to Attack Skill: %s%d%%.", v21, (unsigned __int64)(v22 * 100.0 + 0.5));
                 */
            }
            /*
             * Note Quite Sure what this is? Adds "Covers: <area>" for weapons??
            if (lm & 0x8007FFF && AppraisalSystem::ClothingPriorityToString(v3->cur_weenobj->pwd._priority, ps))
            {
                v33 = ps[0].m_buffer->m_data;
                ItemExamineUI::AddItemInfo(v3, v33, 0, 1);
            }
            */

        }

        void Appraisal_ShowDefenseModData()
        {
            float rDefenseModifier = 0;
            if (InqFloat((PropertyFloat)0x1Du, ref rDefenseModifier) && rDefenseModifier != -1)
            {
                string v3 = SmallModifierToString(rDefenseModifier);
                AddItemInfo($"Bonus to Melee Defense: {v3}.");
            }

            if (InqFloat((PropertyFloat)0x95u, ref rDefenseModifier) && rDefenseModifier != -1)
            {
                string v3 = SmallModifierToString(rDefenseModifier);
                AddItemInfo($"Bonus to Missile Defense: {v3}.");
            }

            if (InqFloat((PropertyFloat)0x96u, ref rDefenseModifier) && rDefenseModifier != -1)
            {
                string v3 = SmallModifierToString(rDefenseModifier);
                AddItemInfo($"Bonus to Magic Defense: {v3}.");
            }
        }
    }
}
