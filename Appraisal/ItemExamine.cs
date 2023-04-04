using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection.Emit;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Xml.Linq;
using WeenieViewer.Db;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;
using static System.Net.Mime.MediaTypeNames;

namespace WeenieViewer.Appraisal
{
    public partial class ItemExamine
    {
        public string Text;
        private dbWeenie Weenie;

        public ItemExamine(dbWeenie weenie)
        {
            Weenie = weenie;

            Appraisal_ShowValueInfo();
            Appraisal_ShowBurdenInfo();
            Appraisal_ShowTinkeringInfo(); // TODO
            bool hasSet = Appraisal_ShowSet();
            bool hasRatings = Appraisal_ShowRatings();
            if (hasSet || hasRatings)
                AddItemInfo(""); // Add a blank line
            Appraisal_ShowWeaponAndArmorData();
            Appraisal_ShowDefenseModData();
            Appraisal_ShowArmorMods();
            Appraisal_ShowShortMagicInfo();
            Appraisal_ShowSpecialProperties();
            Appraisal_ShowUsage();
            Appraisal_ShowLevelLimitInfo();
            Appraisal_ShowWieldRequirements();
            Appraisal_ShowUsageLimitInfo();
            Appraisal_ShowItemLevelInfo();
            Appraisal_ShowActivationRequirements();
            Appraisal_ShowCasterData();
            Appraisal_ShowBoostValue();
            Appraisal_ShowHealKitValues();
            Appraisal_ShowCapacity();
            Appraisal_ShowLockAppraiseInfo();
            Appraisal_ShowManaStoneInfo();
            Appraisal_ShowRemainingUses();
            Appraisal_ShowCraftsman();

            bool isSellbable = false;
            if (InqBool(PropertyBool.IS_SELLABLE_BOOL, ref isSellbable))
                AddItemInfo("This item cannot be sold.");

            Appraisal_ShowRareInfo();
            Appraisal_ShowMagicInfo();
            Appraisal_ShowDescription();
        }
    
        private void AddItemInfo(string text, bool surpressDoubleSpacing = true)
        {
            Text += text + "\n";
            if (!surpressDoubleSpacing) Text += "\n";
        }
        private bool SkillToString(Enums.Skill skill, ref string value)
        {
            value = SkillExtensions.ToSentence(skill);
            if (value != "")
                return true;

            return false;
        }

        private void Appraisal_ShowValueInfo()
        {
            int val = 0;

            if (InqInt((PropertyInt)0x13u, ref val))
                AddItemInfo("Value: " + val.ToString("N0"));
            else
                AddItemInfo("Value: ???");
        }

        private void Appraisal_ShowBurdenInfo()
        {
            int val = 0;
            if (InqInt((PropertyInt)5u, ref val))
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
                if (cTinkers > 1)
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

            if (output != "")
            {
                output = "Ratings: " + output.TrimEnd(new Char[] { ' ', ',' }) + "."; // remove the last ", " and add a perdiod
                AddItemInfo(output);
            }

            if (gear_max_health > 0)
                AddItemInfo($"This item adds {gear_max_health} Vitality.");

            if (output != "" || gear_max_health > 0)
            {
                AddItemInfo(""); // add an extra line
                return true;
            }

            return false;
        }

        private void Appraisal_ShowWeaponAndArmorData()
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
                        SkillToString((Enums.Skill)iWeaponSkill, ref weaponSkill);
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
                        if (InqFloat(PropertyFloat.DAMAGE_MOD_FLOAT, ref damageMod))
                        {
                            string modifier_txt = ModifierToString(damageMod);
                            AddItemInfo($"Damage Modifier: {modifier_txt}.");
                        }
                    }

                    if ((_valid_locations & 0x2500000) > 0) // Melee, Missile, Two-Handed
                    {
                        int wap_weapon_time = 0;
                        InqInt(PropertyInt.WEAPON_TIME_INT, ref wap_weapon_time);
                        if (wap_weapon_time <= 0)
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

                float wap_weapon_offense = 0;
                if (InqFloat(PropertyFloat.WEAPON_OFFENSE_FLOAT, ref wap_weapon_offense) && wap_weapon_offense != 1)
                {
                    double bonus = wap_weapon_offense - 1;
                    string mod_sign;
                    if (bonus < 0)
                        mod_sign = "-";
                    else
                        mod_sign = "+";

                    bonus = bonus * 100;// + 0.5;
                    AddItemInfo($"Bonus to Attack Skill: {mod_sign}{bonus:F0}%.");
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

            int priority = 0;
            InqInt(PropertyInt.CLOTHING_PRIORITY_INT, ref priority);
            if ((_valid_locations & 0x8007FFF) > 0 && priority > 0)
            {
                string coverage = ClothingPriorityToString(priority);
                AddItemInfo(coverage);
            }

        }

        private void Appraisal_ShowDefenseModData()
        {
            float rDefenseModifier = 0;
            if (InqFloat((PropertyFloat)0x1Du, ref rDefenseModifier) && rDefenseModifier != 1)
            {
                string v3 = SmallModifierToString(rDefenseModifier);
                AddItemInfo($"Bonus to Melee Defense: {v3}.");
            }

            if (InqFloat((PropertyFloat)0x95u, ref rDefenseModifier) && rDefenseModifier != 1)
            {
                string v3 = SmallModifierToString(rDefenseModifier);
                AddItemInfo($"Bonus to Missile Defense: {v3}.");
            }

            if (InqFloat((PropertyFloat)0x96u, ref rDefenseModifier) && rDefenseModifier != 1)
            {
                string v3 = SmallModifierToString(rDefenseModifier);
                AddItemInfo($"Bonus to Magic Defense: {v3}.");
            }
        }

        private void Appraisal_ShowArmorMods()
        {
            int ItemType = 0;
            int ArmorLevel = 0;
            if (InqInt(PropertyInt.ITEM_TYPE_INT, ref ItemType) && InqInt(PropertyInt.ARMOR_LEVEL_INT, ref ArmorLevel) && ArmorLevel > 0)
            {
                AddItemInfo($"\nArmor Level: {ArmorLevel}");

                float mod_vs_slash = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_SLASH_FLOAT, ref mod_vs_slash))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Slash, ArmorLevel, mod_vs_slash);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                float mod_vs_pierce = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_PIERCE_FLOAT, ref mod_vs_pierce))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Pierce, ArmorLevel, mod_vs_pierce);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                float mod_vs_bludgeon = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_BLUDGEON_FLOAT, ref mod_vs_bludgeon))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Bludgeon, ArmorLevel, mod_vs_bludgeon);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                float mod_vs_fire = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_FIRE_FLOAT, ref mod_vs_fire))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Fire, ArmorLevel, mod_vs_fire);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                float mod_vs_cold = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_COLD_FLOAT, ref mod_vs_cold))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Cold, ArmorLevel, mod_vs_cold);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                float mod_vs_acid = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_ACID_FLOAT, ref mod_vs_acid))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Acid, ArmorLevel, mod_vs_acid);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                float mod_vs_electric = 0;
                if (InqFloat(PropertyFloat.ARMOR_MOD_VS_ELECTRIC_FLOAT, ref mod_vs_electric))
                {
                    string dmg_resist = DamageResistanceToString((int)DamageType.Electric, ArmorLevel, mod_vs_electric);
                    if (dmg_resist != "") AddItemInfo(dmg_resist);
                }

                // Always 1 unless otherwise set
                float mod_vs_nether = 1;
                InqFloat(PropertyFloat.ARMOR_MOD_VS_NETHER_FLOAT, ref mod_vs_nether);
                string nether_resist = DamageResistanceToString((int)DamageType.Nether, ArmorLevel, mod_vs_nether);
                if (nether_resist != "") AddItemInfo(nether_resist);

            }
        }

        /// <summary>
        /// Adds any spells this item has on it
        /// </summary>
        private void Appraisal_ShowShortMagicInfo()
        {
            int spellDID = 0;
            int procSpellDID = 0;
            if (InqDataID(PropertyDID.SPELL_DID, ref spellDID) || InqDataID(PropertyDID.PROC_SPELL_DID, ref procSpellDID) || Weenie.SpellBook.Count > 0)
            {
                string spellTxt = "Spells: ";
                if (spellDID > 0)
                    spellTxt += GetSpellName(spellDID) + ", ";

                if (procSpellDID > 0)
                    spellTxt += GetSpellName(procSpellDID) + ", ";

                foreach (var spell in Weenie.SpellBook)
                {
                    spellTxt += spell.Name + ", ";
                }

                spellTxt = spellTxt.TrimEnd(new Char[] { ' ', ',' });

                AddItemInfo($"{spellTxt}", false);
            }

        }

        private void Appraisal_ShowSpecialProperties()
        {
            AddItemInfo("");

            int iUnique = 0;
            if (InqInt((PropertyInt)0x117u, ref iUnique))
                AddItemInfo($"You can only carry {iUnique} of these items.");

            float iCooldown = 0;
            if (InqFloat(PropertyFloat.COOLDOWN_DURATION_FLOAT, ref iCooldown))
            {
                AddItemInfo("Cooldown When Used: " + DeltaTimeToString(iCooldown));
            }

            int cleaving = 0;
            if (InqInt((PropertyInt)0x124u, ref cleaving))
            {
                AddItemInfo($"Cleave: {cleaving} enemies in front arc.");
            }

            int creatureType = 0;
            string properties = "";

            if (InqInt((PropertyInt)0xA6u, ref creatureType))
            {
                if (creatureType == 31)
                    properties += "Bael'Zharon's Hate, ";
                else
                {
                    string slayer = CreatureExtensions.ToSentence((CreatureType)creatureType);
                    properties += $"{slayer} slayer, ";
                }
            }

            int attacktype = 0;
            if (InqInt((PropertyInt)0x2Fu, ref attacktype) && (attacktype & 0x79E0) > 0)
                properties += "Multi-Strike, ";

            int imbuedCheck = 0;
            int iTmp = 0;
            if (InqInt((PropertyInt)0xB3u, ref iTmp))
                imbuedCheck = iTmp;
            if (InqInt((PropertyInt)0x12Fu, ref iTmp))
                imbuedCheck |= iTmp;
            if (InqInt((PropertyInt)0x130u, ref iTmp))
                imbuedCheck |= iTmp;
            if (InqInt((PropertyInt)0x131u, ref iTmp))
                imbuedCheck |= iTmp;
            if (InqInt((PropertyInt)0x132u, ref iTmp))
                imbuedCheck |= iTmp;

            if (imbuedCheck > 0)
            {
                if ((imbuedCheck & 1) > 0)
                    properties += "Critical Strike, ";
                if ((imbuedCheck & 2) > 0)
                    properties += "Crippling Blow, ";
                if ((imbuedCheck & 4) > 0)
                    properties += "Armor Rending, ";
                if ((imbuedCheck & 8) > 0)
                    properties += "Slash Rending, ";
                if ((imbuedCheck & 0x10) > 0)
                    properties += "Pierce Rending, ";
                if ((imbuedCheck & 0x20) > 0)
                    properties += "Bludgeon Rending, ";
                if ((imbuedCheck & 0x40) > 0)
                    properties += "Acid Rending, ";
                if ((imbuedCheck & 0x4000) > 0)
                    properties += "Nether Rending, ";
                if ((imbuedCheck & 0x80) > 0)
                    properties += "Cold Rending, ";
                if ((imbuedCheck & 0x100) > 0)
                    properties += "Lightning Rending, ";
                if ((imbuedCheck & 0x200) > 0)
                    properties += "Fire Rending, ";
                if ((imbuedCheck & 0x400) > 0)
                    properties += "+1 Melee Defense, ";
                if ((imbuedCheck & 0x800) > 0)
                    properties += "+1 Missile Defense, ";
                if ((imbuedCheck & 0x1000) > 0)
                    properties += "+1 Magic Defense, ";
                if (imbuedCheck < 0)
                    properties += "Phantasmal, ";
            }

            float absorb_magic = 0;
            if (InqFloat((PropertyFloat)0x9Fu, ref absorb_magic))
                properties += "Magic Absorbing, ";
            int magic_resist = 0;
            if (InqInt((PropertyInt)0x24u, ref magic_resist) && magic_resist >= 9999)
                properties += "Unenchantable, ";
            int attuned = 0;
            if (InqInt((PropertyInt)0x72u, ref attuned) && attuned > 0 && attuned < 2)
                properties += "Attuned, ";
            int bonded = 0;
            if (InqInt((PropertyInt)0x21u, ref bonded))
            {
                switch (bonded)
                {
                    case -2: properties += "Destroyed on Death, "; break;
                    case -1: properties += "Dropped on Death, "; break;
                    case 1: properties += "Bonded, "; break;
                }
            }

            bool retained = false;
            if (InqBool((PropertyBool)0x5Bu, ref retained) && retained == true)
                properties += "Retained, ";
            float fCrit = 0;
            if (InqFloat((PropertyFloat)0x88u, ref fCrit))
                properties += "Crushing Blow, ";
            if (InqFloat((PropertyFloat)0x93u, ref fCrit))
                properties += "Biting Strike, ";
            if (InqFloat((PropertyFloat)0x9Bu, ref fCrit))
                properties += "Armor Cleaving, ";

            float fResMod = 1;
            int damageType = 0;
            if (InqFloat((PropertyFloat)0x9Du, ref fResMod) && InqInt((PropertyInt)0x107u, ref damageType))
            {
                string txt_tmp = DamageTypeExtensions.GetDamageTypes((DamageType)damageType);
                properties += $"Resistance Cleaving: {txt_tmp}, ";
            }

            int spellDID = 0;
            if (InqDataID((PropertyDID)0x37u, ref spellDID))
                properties += "Cast on Strike, ";
            bool bIvoryable = false;
            if (InqBool((PropertyBool)0x63u, ref bIvoryable) && bIvoryable == true)
                properties += "Ivoryable, ";
            bool bDyable = false;
            if (InqBool((PropertyBool)0x64u, ref bDyable) && bDyable == true)
                properties += "Dyeable, ";

            if (properties.Length > 0)
            {
                properties = properties.TrimEnd(new Char[] { ' ', ',' });
                AddItemInfo($"Properties: {properties}");
            }
            if (imbuedCheck != 0)
                AddItemInfo("This item cannot be further imbued.");
            bool bAutowieldLeft = false;
            if (InqBool((PropertyBool)0x82u, ref bAutowieldLeft) && bAutowieldLeft == true)
            {
                AddItemInfo("This item is tethered to the left side.");
                AddItemInfo("");
            }
            if (imbuedCheck != 0 && bAutowieldLeft == false)
                AddItemInfo("");

        }

        private void Appraisal_ShowUsage()
        {
            string strUsage = "";
            if (InqString((PropertyString)0xEu, ref strUsage))
                AddItemInfo(strUsage, false);

        }

        private void Appraisal_ShowLevelLimitInfo()
        {
            int min = 0, max = 0;
            InqInt((PropertyInt)0x56u, ref min);
            InqInt((PropertyInt)0x57u, ref max);
            if (min > 0 || max > 0)
            {
                string numtxt;
                if (max <= 0)
                    numtxt = $"Restricted to characters of Level {min} or greater.";
                else if (min <= 0)
                    numtxt = $"Restricted to characters of Level {max} or below.";
                else if (max == min)
                    numtxt = $"Restricted to characters of Level {min}.";
                else
                    numtxt = $"Restricted to characters of Levels {min} to {max}.";

                AddItemInfo(numtxt, false);
            }

            string portal_dest = "";
            if (InqString((PropertyString)0x26u, ref portal_dest))
                AddItemInfo("Destination: " + portal_dest, false);
        }

        private void Appraisal_ShowWieldRequirements()
        {
            bool has_allowed_wielder = false;
            if (InqBool((PropertyBool)0x55u, ref has_allowed_wielder) && has_allowed_wielder == true)
            {
                string strSkill = "the original owner";
                InqString((PropertyString)0x19u, ref strSkill);
                AddItemInfo("Wield requires " + strSkill);
            }

            int iAcctReqs = 0;
            if (InqInt((PropertyInt)0x1Au, ref iAcctReqs) && iAcctReqs > 0)
                AddItemInfo("Use requires Throne of Destiny.");

            int heritage_specific = 0;
            if (InqInt((PropertyInt)0x144u, ref heritage_specific))
            {
                string strSkill = "";
                if (InqHeritageGroupDisplayName(heritage_specific, ref strSkill) && strSkill != "")
                    AddItemInfo("Wield requires " + strSkill);
            }

            int iReq = 0;
            int iSkill = 0;
            int iDiff = 0;
            if (InqInt((PropertyInt)0x9Eu, ref iReq) && InqInt((PropertyInt)0x9Fu, ref iSkill) && InqInt((PropertyInt)0xA0u, ref iDiff))
                Appraisal_ShowWieldRequirements_Helper(iReq, iSkill, iDiff);
            else
            {
                if (InqInt((PropertyInt)0x10Eu, ref iReq) && InqInt((PropertyInt)0x10Fu, ref iSkill) && InqInt((PropertyInt)0x110u, ref iDiff))
                    Appraisal_ShowWieldRequirements_Helper(iReq, iSkill, iDiff);

                if (InqInt((PropertyInt)0x111u, ref iReq) && InqInt((PropertyInt)0x112u, ref iSkill) && InqInt((PropertyInt)0x113u, ref iDiff))
                    Appraisal_ShowWieldRequirements_Helper(iReq, iSkill, iDiff);

                if (InqInt((PropertyInt)0x114u, ref iReq) && InqInt((PropertyInt)0x115u, ref iSkill) && InqInt((PropertyInt)0x116u, ref iDiff))
                    Appraisal_ShowWieldRequirements_Helper(iReq, iSkill, iDiff);
            }
        }

        /// <summary>
        /// Not directly in the source, but makes the above much cleaner!
        /// </summary>
        /// <param name="iReq"></param>
        /// <param name="iSkill"></param>
        /// <param name="iDiff"></param>
        private void Appraisal_ShowWieldRequirements_Helper(int iReq, int iSkill, int iDiff)
        {
            string strSkill = GetAppraisalStringFromRequirements(iReq, iSkill, iDiff);
            string numtxt = "";
            switch (iReq)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 9:
                case 0xA:
                    numtxt = $"Wield requires {strSkill} {iDiff}";
                    break;
                case 8:
                    if (iDiff != 3)
                        numtxt = $"Wield requires trained {strSkill}";
                    else
                        numtxt = $"Wield requires specialized {strSkill}";
                    break;
                case 0xB:
                    numtxt = $"Wield requires {strSkill} type";
                    break;
                case 0xC:
                    numtxt = $"Wield requires {strSkill} race";
                    break;
            }
            if (numtxt != "")
                AddItemInfo(numtxt);
        }

        private void Appraisal_ShowUsageLimitInfo()
        {
            int level_requirement = 0;
            if (InqInt((PropertyInt)0x171u, ref level_requirement) && level_requirement > 0)
            {
                AddItemInfo("");
                AddItemInfo($"Use requires level {level_requirement}.");
            }

            int skill = 0;
            int iskill_level = 0;
            bool skill_str_added = false;
            if (InqInt((PropertyInt)0x16Eu, ref skill) && skill > 0 && InqInt((PropertyInt)0x16Fu, ref iskill_level) && iskill_level > 0)
            {
                string skill_str = InqSkillName(skill);
                if (skill_str == "") skill_str = "Unknown Skill";
                AddItemInfo("");
                AddItemInfo($"Use requires {skill_str} of at least {iskill_level}.");
                skill_str_added = true;
            }

            skill = 0;
            if (InqInt((PropertyInt)0x170u, ref skill) && skill > 0)
            {
                string skill_str = InqSkillName(skill);
                if (skill_str == "") skill_str = "Unknown Skill";
                if(!skill_str_added) AddItemInfo("");
                AddItemInfo($"Use requires specialized {skill_str}.");
            }
        }

        private void Appraisal_ShowItemLevelInfo()
        {
            long item_base_xp = 0;
            long item_xp = 0;
            int item_max_level = 0;
            int item_xp_style = 0;

            if (InqInt64((PropertyInt64)5u, ref item_base_xp) && item_base_xp > 0
                && InqInt((PropertyInt)0x13Fu, ref item_max_level) && item_max_level > 0
                && InqInt((PropertyInt)0x140u, ref item_xp_style) && item_xp_style > 0)
            {
                InqInt64((PropertyInt64)4u, ref item_xp);

                int level = ItemTotalXPToLevel(item_xp, item_base_xp, item_max_level, item_xp_style);

                int next_level = level + 1;
                if (next_level > item_max_level) next_level = item_max_level;
                long next_level_xp = ItemLevelToTotalXP(next_level, item_base_xp, item_max_level, item_xp_style);

                string formatted_item_xp = item_xp.ToString("N0");
                string formatted_next_xp = next_level_xp.ToString("N0");
                AddItemInfo($"Item Level: {level} / {item_max_level}");
                AddItemInfo($"Item XP: {formatted_item_xp} / {formatted_next_xp}");
                AddItemInfo("");

            }

            int cloak_proc = 0;
            if(InqInt((PropertyInt)0x160u, ref cloak_proc) && cloak_proc == 2)
                AddItemInfo("This cloak has a chance to reduce an incoming attack by 200 damage.", true);
        }

        private void Appraisal_ShowActivationRequirements()
        {
            string activationReqsString = "";

            int iDifficulty = 0;
            if (InqInt((PropertyInt)0x6D, ref iDifficulty) && iDifficulty > 0)
                activationReqsString += $"Arcane Lore: {iDifficulty}, ";

            int iRank = 0;
            if (InqInt((PropertyInt)0x6E, ref iRank) && iRank >= 1)
                activationReqsString += $"Allegiance Rank: {iRank}, ";

            int heritage_req = 0;
            if(InqInt((PropertyInt)0xBC, ref heritage_req))
            {
                string activator_name = "";
                if (InqHeritageGroupDisplayName(heritage_req, ref activator_name))
                    activationReqsString += activator_name + ", ";
            }

            int iSkillLimit = 0;
            int attribute2nd = 0;
            if (InqInt((PropertyInt)0x73u, ref iSkillLimit) && iSkillLimit > 0 && InqInt((PropertyInt)0xB0u, ref attribute2nd))
            {
                string activator_name = InqSkillName(attribute2nd);
                if (activator_name.Length > 0)
                    activationReqsString += $"{activator_name}: {iSkillLimit}, ";
            }

            int iAttributeLimit = 0;
            attribute2nd = 0;
            if (InqInt((PropertyInt)0x102u, ref iAttributeLimit) && iAttributeLimit > 0 && InqInt((PropertyInt)0x101u, ref attribute2nd))
            {
                string activator_name = InqAttributeName(attribute2nd);
                if (activator_name.Length > 0)
                    activationReqsString += $"{activator_name}: {iAttributeLimit}, ";
            }

            int iAttribute2ndLimit = 0;
            attribute2nd = 0;
            if (InqInt((PropertyInt)0x104u, ref iAttribute2ndLimit) && iAttributeLimit > 0 && InqInt((PropertyInt)0x103u, ref attribute2nd))
            {
                string activator_name = InqAttribute2ndName(attribute2nd);
                if (activator_name.Length > 0)
                    activationReqsString += $"{activator_name}: {iAttributeLimit}, ";
            }

            if (activationReqsString.Length > 0)
                AddItemInfo("Activation requires " + activationReqsString.TrimEnd(new Char[] { ' ', ',' }));

            bool has_allowed_activator = false;
            if (InqBool((PropertyBool)0x5Eu, ref has_allowed_activator) && has_allowed_activator == true)
            {
                string activator_name = "the original owner";
                InqString(PropertyString.CRAFTSMAN_NAME_STRING, ref activator_name);
                AddItemInfo("This item can only be activated by " + activator_name);
            }
        }

        private void Appraisal_ShowCasterData()
        {
            float rManaCModifier = 0;
            if(InqFloat((PropertyFloat)0x90u, ref rManaCModifier))
            {
                rManaCModifier += 1;
                string manaCModifier = ModifierToString(rManaCModifier);
                AddItemInfo($"Bonus to Mana Conversion: {manaCModifier}.", false);
            }

            float eleDamageModPvM = 1;
            if (InqFloat((PropertyFloat)0x98u, ref eleDamageModPvM))
            {
                int damageType = 0;
                if (InqInt((PropertyInt)0x2Du, ref damageType))
                {
                    string tmptxt = DamageTypeExtensions.GetDamageTypes((DamageType)damageType);
                    string eleDamageModInfo = $"Damage bonus for {tmptxt} spells:";
                    float eleDamageModPvP = GetElementalModPKModifier(eleDamageModPvM);
                    tmptxt = SmallModifierToString(eleDamageModPvM);
                    string eleDamageModTextPvM = $" vs. Monsters: {tmptxt}.";
                    tmptxt = SmallModifierToString(eleDamageModPvP);
                    string eleDamageModTextPvP = $" vs. Players: {tmptxt}.";
                    AddItemInfo(eleDamageModInfo);
                    AddItemInfo(eleDamageModTextPvM);
                    AddItemInfo(eleDamageModTextPvP);
                }
            }
        }

        private void Appraisal_ShowBoostValue()
        {
            if (Weenie.WeenieType != 28) // Healer_WeenieType 
            { 
                int iBoostAmount = 0;
                int iAttribEffected = 0;
                if (InqInt((PropertyInt)0x5Au, ref iBoostAmount) && InqInt((PropertyInt)0x59u, ref iAttribEffected) && iBoostAmount != 0)
                {
                    switch (iAttribEffected)
                    {
                        case 2:
                            if (iBoostAmount < 0)
                                AddItemInfo($"Depletes {iBoostAmount} Health when used.", false);
                            else
                                AddItemInfo($"Restores {iBoostAmount} Health when used.", false);
                            break;
                        case 4:
                            if (iBoostAmount < 0)
                                AddItemInfo($"Depletes {iBoostAmount} Stamina when used.", false);
                            else
                                AddItemInfo($"Restores {iBoostAmount} Stamina when used.", false);
                            break;
                        case 6:
                            if (iBoostAmount < 0)
                                AddItemInfo($"Depletes {iBoostAmount} Mana when used.", false);
                            else
                                AddItemInfo($"Restores {iBoostAmount} Mana when used.", false);
                            break;
                    }
                }
            }
        }

        private void Appraisal_ShowHealKitValues()
        {
            if(Weenie.WeenieType == 28) // Healer_WeenieType 
            {
                int iBoostAmount = 0;
                if(InqInt((PropertyInt)0x5Au, ref iBoostAmount) && iBoostAmount != 0)
                    AddItemInfo($"Bonus to Healing Skill: {iBoostAmount}");
                float rHealKitMod = 1.0F;
                if(InqFloat((PropertyFloat)0x64u, ref rHealKitMod))
                    AddItemInfo($"Restoration Bonus: {rHealKitMod * 100}%");
            }
        }

        private void Appraisal_ShowCapacity()
        {
            int iItemsCapacity = 0;
            
            int iContainersCapacity = 0;
            InqInt(PropertyInt.CONTAINERS_CAPACITY_INT, ref iContainersCapacity);
            if(iItemsCapacity > 0 || iContainersCapacity > 0)
            {
                if (iItemsCapacity == 0)
                    AddItemInfo($"Can hold up to {iContainersCapacity} containers.", false);
                else if (iContainersCapacity == 0)
                    AddItemInfo($"Can hold up to {iItemsCapacity} items.", false);
                else
                    AddItemInfo($"Can hold up to {iItemsCapacity} items and {iContainersCapacity} containers.", false);
            }
            int iMaxPages = Weenie.Book.BookMaxPages;
            int iNumPages = Weenie.BookData.Count;
            if (iMaxPages > 0)
                AddItemInfo($"{iNumPages} of {iMaxPages} pages full.");
        }

        private void Appraisal_ShowLockAppraiseInfo()
        {
            bool locked = false;
            int iStat = 0;
            if (InqBool(PropertyBool.LOCKED_BOOL, ref locked))
            {
                if (locked)
                {
                    AddItemInfo("Locked", false);

                    iStat = 0;
                    if (InqInt(PropertyInt.RESIST_LOCKPICK_INT, ref iStat))
                    {
                        string numtxt = pseudo_LockpickSuccessPercentToString(iStat);
                        AddItemInfo($"The lock looks {numtxt} to pick (Resistance {iStat}).");
                    }
                }
                else
                    AddItemInfo("Unlocked", true);
            }
            else if(InqInt(PropertyInt.RESIST_LOCKPICK_INT, ref iStat) && iStat != 0)
            {
                if (iStat > 0)
                    AddItemInfo($"Bonus to Lockpick Skill: +{iStat}");
                else
                    AddItemInfo($"Bonus to Lockpick Skill: {iStat}");
            }
        }

        private void Appraisal_ShowManaStoneInfo()
        {
            if (Weenie.SpellBook.Count == 0)
            {
                int iCurMana = 0;
                if (InqInt(PropertyInt.ITEM_CUR_MANA_INT, ref iCurMana))
                    AddItemInfo($"Stored Mana: {iCurMana}");

                float rEfficiency = 0f;
                if (InqFloat(PropertyFloat.ITEM_EFFICIENCY_FLOAT, ref rEfficiency))
                {
                    string numtxt = (rEfficiency * 100).ToString("N0");
                    AddItemInfo($"Efficiency: {numtxt}%");
                }

                float rChanceOfDestruction = 0f;
                if (InqFloat(PropertyFloat.MANA_STONE_DESTROY_CHANCE_FLOAT, ref rChanceOfDestruction))
                {
                    string numtxt = (rChanceOfDestruction * 100).ToString("N0");
                    AddItemInfo($"Chance of Destruction: {numtxt}%");
                }

            }

        }

        private void Appraisal_ShowRemainingUses()
        {
            int iKeys = 0;
            if (InqInt(PropertyInt.NUM_KEYS_INT, ref iKeys))
            {
                if (iKeys == 1)
                    AddItemInfo("Contains 1 key.");
                else
                    AddItemInfo($"Contains {iKeys} keys.");
            }

            bool unlimited_use = false;
            int iUses = 0;
            InqBool(PropertyBool.UNLIMITED_USE_BOOL, ref unlimited_use);
            if (unlimited_use == true)
                AddItemInfo("Number of uses remaining:  Unlimited");
            else if (InqInt(PropertyInt.STRUCTURE_INT, ref iUses))
                AddItemInfo($"Number of uses remaining: {iUses}");
        }

        private void Appraisal_ShowCraftsman()
        {
            bool has_allowed_iid = false;
            if( (!InqBool(PropertyBool.APPRAISAL_HAS_ALLOWED_WIELDER_BOOL, ref has_allowed_iid) || !has_allowed_iid) 
                && (!InqBool(PropertyBool.APPRAISAL_HAS_ALLOWED_ACTIVATOR_BOOL, ref has_allowed_iid) || !has_allowed_iid) )
            {
                string strCraftsman = "";
                if (InqString(PropertyString.CRAFTSMAN_NAME_STRING, ref strCraftsman))
                    AddItemInfo($"Created by {strCraftsman}.");
            }
        }

        private void Appraisal_ShowRareInfo()
        {
            bool rareUsesTimer = false;
            if (InqBool(PropertyBool.RARE_USES_TIMER_BOOL, ref rareUsesTimer) && rareUsesTimer)
                AddItemInfo("\"This rare item has a timer restriction of 3 minutes. You will not be able to use another rare item with a timer within 3 minutes of using this one.", false);

            int iRareID = 0;
            if (InqInt(PropertyInt.RARE_ID_INT, ref iRareID))
                AddItemInfo($"Rare #{iRareID}", false);
        }

        private void Appraisal_ShowMagicInfo()
        {
            if(Weenie.SpellBook.Count > 0)
            {
                // "Spell Descriptions:"

                int iSpellcraft = 0;
                if (InqInt(PropertyInt.ITEM_SPELLCRAFT_INT, ref iSpellcraft))
                    AddItemInfo($"Spellcraft: {iSpellcraft}.");

                int iCurMana = 0;
                int iManaCost = 0;
                if (InqInt(PropertyInt.ITEM_CUR_MANA_INT, ref iCurMana) && InqInt(PropertyInt.ITEM_MAX_MANA_INT, ref iManaCost))
                    AddItemInfo($"Mana: {iCurMana} / {iManaCost}.");

                float rManaRate = 0f;
                iManaCost = 0;
                if (InqFloat(PropertyFloat.MANA_RATE_FLOAT, ref rManaRate))
                {
                    var v30 = 1.0 / rManaRate;
                    if (v30 < 0) v30 = v30 * -1;
                    AddItemInfo($"Mana Cost: 1 point per {v30:N0} seconds.");
                }
                else if(InqInt(PropertyInt.ITEM_MANA_COST_INT, ref iManaCost))
                {
                    if (iManaCost <= 0)
                        AddItemInfo($"Mana Cost: {iManaCost}.");
                    else
                        AddItemInfo($"Mana Cost: {iManaCost}.\n(Can be reduced by the Mana Conversion skill)");
                }
                AddItemInfo("");

            }
        }

        private void Appraisal_ShowDescription()
        {
            int lifespan = 0;
            if(InqInt(PropertyInt.LIFESPAN_INT, ref lifespan))
            {
                string remaining = DeltaTimeToString((float)lifespan);
                AddItemInfo("This item expires in " + remaining);
            }

            string strDesc = "";
            if (InqString(PropertyString.LONG_DESC_STRING, ref strDesc))
            {
                // TODO
                string gearPlatingName = "";
                if (InqString(PropertyString.GEAR_PLATING_NAME_STRING, ref gearPlatingName))
                    strDesc = gearPlatingName;

                int iDecoration = 0;
                if (InqInt(PropertyInt.APPRAISAL_LONG_DESC_DECORATION_INT, ref iDecoration))
                {
                    int iGemCount = 0;
                    if ((iDecoration & 1) != 0 && InqInt(PropertyInt.ITEM_WORKMANSHIP_INT, ref iGemCount))
                    {
                        // More here. Is any of this even applicable to the stock DB?
                    }
                }

            }
            else 
                InqString(PropertyString.SHORT_DESC_STRING, ref strDesc);

            if(strDesc != "")
            {
                AddItemInfo("");
                AddItemInfo(strDesc);
            }

            int bitfield = 0;
            if(InqInt(PropertyInt.PORTAL_BITMASK_INT, ref bitfield))
            {
                string portalDesc = "";
                if ((bitfield & 2) != 0)
                    portalDesc += "Player Killers may not use this portal.\n";
                if ((bitfield & 4) != 0)
                    portalDesc += "Lite Player Killers may not use this portal.\n";
                if ((bitfield & 8) != 0)
                    portalDesc += "Non-Player Killers may not use this portal.\n";
                if ((bitfield & 0x20) != 0)
                    portalDesc += "This portal cannot be recalled nor linked to.\n";
                if ((bitfield & 0x10) != 0)
                    portalDesc += "This portal cannot be summoned.\n";

                if(portalDesc.Length > 0)
                {
                    AddItemInfo("");
                    AddItemInfo(portalDesc);
                }
            }

            long cost = 0;
            if(InqInt64(PropertyInt64.AUGMENTATION_COST_INT64, ref cost))
            {
                AddItemInfo($"Using this gem will drain {cost:N0} points of your available experience.");
            }
        }
    }
}
