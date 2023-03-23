using EmoteScriptLib.Entity.Enum;
using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;
using PropertyInt = EmoteScriptLib.Entity.Enum.PropertyInt;

namespace WeenieViewer.SQLWriter
{
    public class WeenieSQLWriter
    {
        public IDictionary<int, string> WeenieNames;
        public IDictionary<int, string> SpellNames;

        /// <summary>
        /// If input is null, NULL will be returned.<para />
        /// If input is not null, a string surrounded in ' will be returnedf, and any ' found within the string will be replaced wtih ''
        /// </summary>
        protected static string GetSQLString(string input)
        {
            if (input == null)
                return null;

            return "'" + input.Replace("'", "''") + "'";
        }

        /// <summary>
        /// This will find values that were not output to a values line, for example, if a property is a (int?), and it has no value, you might see ", ," in the sql.<para />
        /// This function will replace that ", ," with ", NULL,".<para />
        /// It also removes empty comments like the folliwng: " /*  */"
        /// </summary>
        protected static string FixNullFields(string input)
        {
            input = input.Replace(", ,", ", NULL,");
            input = input.Replace(", ,", ", NULL,");

            // Fix cases where the last field might be null
            input = input.Replace(", )", ", NULL)");

            // Remove empty comments
            input = input.Replace(" /*  */", "");

            return input;
        }

        /// <summary>
        /// lineGenerator should generate the entire line after the first (. It should include the trailing ) and any comments after.<para />
        /// It should consist of only a single line.<para />
        /// This will automatically call FixNullFields on the output created by lineGenerator()
        /// </summary>
        protected static void ValuesWriter(int count, Func<int, string> lineGenerator, StreamWriter writer)
        {
            for (int i = 0; i < count; i++)
            {
                string output;

                if (i == 0)
                    output = "VALUES (";
                else
                    output = "     , (";

                output += lineGenerator(i);

                if (i == count - 1)
                    output += ";";

                output = FixNullFields(output);

                writer.WriteLine(output);
            }
        }

        protected static float? TrimNegativeZero(float? input, int places = 6)
        {
            if (input == null)
                return null;

            var str = input.Value.ToString($"0.{new string('#', places)}");

            if (str == $"-0.{new string('#', places)}" || str == "-0")
                str = str.Substring(1, str.Length - 1);

            var ret = float.Parse(str);

            return ret;
        }

        public void CreateSQLINSERTStatement(IList<Emote> input, StreamWriter writer)
        {
            uint weenieClassID = 1;

            foreach (var value in input)
            {
                writer.WriteLine();
                writer.WriteLine("INSERT INTO `weenie_properties_emote` (`object_Id`, `category`, `probability`, `weenie_Class_Id`, `style`, `substyle`, `quest`, `vendor_Type`, `min_Health`, `max_Health`)");

                //var categoryLabel = Enum.GetName(typeof(EmoteCategory), value.Category);
                //if (categoryLabel != null)
                //    categoryLabel = $" /* {categoryLabel} */";

                string weenieClassIdLabel = null;
                if (WeenieNames != null && value.WeenieClassId.HasValue)
                {
                    WeenieNames.TryGetValue(value.WeenieClassId.Value, out weenieClassIdLabel);
                    if (weenieClassIdLabel != null)
                        weenieClassIdLabel = $" /* {weenieClassIdLabel} */";
                }

                string styleLabel = null;

                string substyleLabel = null;

                string vendorTypeLabel = null;

                var output = "VALUES (" +
                             $"{weenieClassID}, " +
                             $"{value.Category.ToString().PadLeft(2)}, " +
                             $"{value.Probability.ToString("0.######", CultureInfo.InvariantCulture).PadLeft(6)}, " +
                             $"{value.WeenieClassId}{weenieClassIdLabel}, " +
                             $"{(value.Style.HasValue ? "0x" : "")}{value.Style:X8}{styleLabel}, " +
                             $"{(value.Substyle.HasValue ? "0x" : "")}{value.Substyle:X8}{substyleLabel}, " +
                             $"{GetSQLString(value.Quest)}, " +
                             $"{value.VendorType}{vendorTypeLabel}, " +
                             $"{value.MinHealth:0.######}, " +
                             $"{value.MaxHealth:0.######}" +
                             ");";

                output = FixNullFields(output);

                writer.WriteLine(output);

                if (value.EmoteAction != null && value.EmoteAction.Count > 0)
                {
                    writer.WriteLine();
                    writer.WriteLine("SET @parent_id = LAST_INSERT_ID();");

                    writer.WriteLine();
                    CreateSQLINSERTStatement(value.EmoteAction.OrderBy(r => r.Order).ToList(), writer);
                }
            }
        }

        private void CreateSQLINSERTStatement(IList<EmoteAction> input, StreamWriter writer)
        {
            writer.WriteLine("INSERT INTO `weenie_properties_emote_action` (`emote_Id`, `order`, `type`, `delay`, `extent`, `motion`, `message`, `test_String`, `min`, `max`, `min_64`, `max_64`, `min_Dbl`, `max_Dbl`, " +
                             "`stat`, `display`, `amount`, `amount_64`, `hero_X_P_64`, `percent`, `spell_Id`, `wealth_Rating`, `treasure_Class`, `treasure_Type`, `p_Script`, `sound`, `destination_Type`, `weenie_Class_Id`, `stack_Size`, `palette`, `shade`, `try_To_Bond`, " +
                             "`obj_Cell_Id`, `origin_X`, `origin_Y`, `origin_Z`, `angles_W`, `angles_X`, `angles_Y`, `angles_Z`)");

            var lineGenerator = new Func<int, string>(i =>
            {
                string typeLabel = Enum.GetName(typeof(EmoteType), input[i].Type);
                if (typeLabel != null)
                    typeLabel = $" /* {typeLabel} */";

                string motionLabel = null;
                if (input[i].Motion.HasValue)
                {
                    motionLabel = Enum.GetName(typeof(MotionCommand), input[i].Motion.Value);
                    if (motionLabel != null)
                        motionLabel = $" /* {motionLabel} */";
                }

                string spellIdLabel = null;
                if (SpellNames != null && input[i].SpellId.HasValue)
                {
                    SpellNames.TryGetValue(input[i].SpellId.Value, out spellIdLabel);
                    if (spellIdLabel != null)
                        spellIdLabel = $" /* {spellIdLabel} */";
                }

                string pScriptLabel = null;
                if (input[i].PScript.HasValue)
                {
                    pScriptLabel = Enum.GetName(typeof(PlayScript), input[i].PScript.Value);
                    if (pScriptLabel != null)
                        pScriptLabel = $" /* {pScriptLabel} */";
                }

                string soundLabel = null;
                if (input[i].Sound.HasValue)
                {
                    soundLabel = Enum.GetName(typeof(Sound), input[i].Sound.Value);
                    if (soundLabel != null)
                        soundLabel = $" /* {soundLabel} */";
                }

                string weenieClassIdLabel = null;
                if (input[i].WeenieClassId.HasValue && WeenieNames != null)
                {
                    WeenieNames.TryGetValue((int)input[i].WeenieClassId.Value, out weenieClassIdLabel);
                    if (weenieClassIdLabel != null)
                        weenieClassIdLabel = $" /* {weenieClassIdLabel} */";
                }

                string destinationTypeLabel = null;
                if (input[i].DestinationType.HasValue)
                {
                    destinationTypeLabel = Enum.GetName(typeof(DestinationType), input[i].DestinationType.Value);
                    if (destinationTypeLabel != null)
                        destinationTypeLabel = $" /* {destinationTypeLabel} */";
                }

                string telelocLabel = null;
                if (input[i].ObjCellId.HasValue && input[i].ObjCellId.Value > 0)
                {
                    telelocLabel = $" /* @teleloc 0x{input[i].ObjCellId.Value:X8} [{TrimNegativeZero(input[i].OriginX.Value):F6} {TrimNegativeZero(input[i].OriginY.Value):F6} {TrimNegativeZero(input[i].OriginZ.Value):F6}] {TrimNegativeZero(input[i].AnglesW.Value):F6} {TrimNegativeZero(input[i].AnglesX.Value):F6} {TrimNegativeZero(input[i].AnglesY.Value):F6} {TrimNegativeZero(input[i].AnglesZ.Value):F6} */";
                }

                string statLabel = null;
                if (input[i].Stat.HasValue)
                {
                    switch ((EmoteType)input[i].Type)
                    {
                        case EmoteType.AwardLevelProportionalSkillXP:
                        case EmoteType.AwardSkillPoints:
                        case EmoteType.AwardSkillXP:

                        case EmoteType.InqSkillStat:
                        case EmoteType.InqRawSkillStat:
                        case EmoteType.InqSkillTrained:
                        case EmoteType.InqSkillSpecialized:
                        case EmoteType.UntrainSkill:
                            statLabel = $" /* Skill.{(EmoteScriptLib.Entity.Enum.Skill)input[i].Stat.Value} */";
                            break;

                        case EmoteType.DecrementIntStat:
                        case EmoteType.IncrementIntStat:
                        case EmoteType.InqIntStat:
                        case EmoteType.SetIntStat:
                            statLabel = $" /* PropertyInt.{(PropertyInt)input[i].Stat.Value} */";
                            break;

                        case EmoteType.InqAttributeStat:
                        case EmoteType.InqRawAttributeStat:
                            statLabel = $" /* PropertyAttribute.{(PropertyAttribute)input[i].Stat.Value} */";
                            break;

                        case EmoteType.InqBoolStat:
                        case EmoteType.SetBoolStat:
                            statLabel = $" /* PropertyBool.{(EmoteScriptLib.Entity.Enum.PropertyBool)input[i].Stat.Value} */";
                            break;

                        case EmoteType.InqFloatStat:
                        case EmoteType.SetFloatStat:
                            statLabel = $" /* PropertyFloat.{(EmoteScriptLib.Entity.Enum.PropertyFloat)input[i].Stat.Value} */";
                            break;

                        case EmoteType.InqInt64Stat:
                        case EmoteType.SetInt64Stat:
                            statLabel = $" /* PropertyInt64.{(EmoteScriptLib.Entity.Enum.PropertyInt64)input[i].Stat.Value} */";
                            break;

                        case EmoteType.InqSecondaryAttributeStat:
                        case EmoteType.InqRawSecondaryAttributeStat:
                            statLabel = $" /* PropertyAttribute2nd.{(PropertyAttribute2nd)input[i].Stat.Value} */";
                            break;

                        case EmoteType.InqStringStat:
                            statLabel = $" /* PropertyString.{(EmoteScriptLib.Entity.Enum.PropertyString)input[i].Stat.Value} */";
                            break;

                        default:
                            break;
                    }
                }

                string amountLabel = null;
                if (input[i].Amount.HasValue)
                {
                    switch ((EmoteType)input[i].Type)
                    {
                        case EmoteType.AddCharacterTitle:
                            amountLabel = $" /* {(CharacterTitle)input[i].Amount.Value} */";
                            break;

                        case EmoteType.AddContract:
                        case EmoteType.RemoveContract:
                            amountLabel = $" /* {(ContractId)input[i].Amount.Value} */";
                            break;

                        default:
                            break;
                    }
                }

                string treasureClassLabel = null;
               

                string treasureTypeLabel = null;


                string paletteLabel = null;
                if (input[i].Palette.HasValue)
                {
                    paletteLabel = Enum.GetName(typeof(PaletteTemplate), input[i].Palette.Value);
                    if (paletteLabel != null)
                        paletteLabel = $" /* {paletteLabel} */";
                }

                return
                    "@parent_id, " +
                    $"{input[i].Order.ToString().PadLeft(2)}, " +
                    $"{input[i].Type.ToString().PadLeft(3)}{typeLabel}, " +
                    $"{input[i].Delay:0.######}, " +
                    $"{input[i].Extent:0.######}, " +
                    $"{(input[i].Motion.HasValue ? "0x" : "")}{input[i].Motion:X8}{motionLabel}, " +
                    $"{GetSQLString(input[i].Message)}, " +
                    $"{GetSQLString(input[i].TestString)}, " +
                    $"{input[i].Min}, " +
                    $"{input[i].Max}, " +
                    $"{input[i].Min64}, " +
                    $"{input[i].Max64}, " +
                    $"{input[i].MinDbl}, " +
                    $"{input[i].MaxDbl}, " +
                    $"{input[i].Stat}{statLabel}, " +
                    $"{input[i].Display}, " +
                    $"{input[i].Amount}{amountLabel}, " +
                    $"{input[i].Amount64}, " +
                    $"{input[i].HeroXP64}, " +
                    $"{input[i].Percent}, " +
                    $"{input[i].SpellId}{spellIdLabel}, " +
                    $"{input[i].WealthRating}, " +
                    $"{input[i].TreasureClass}{treasureClassLabel}, " +
                    $"{input[i].TreasureType}{treasureTypeLabel}, " +
                    $"{input[i].PScript}{pScriptLabel}, " +
                    $"{input[i].Sound}{soundLabel}, " +
                    $"{input[i].DestinationType}{destinationTypeLabel}, " +
                    $"{input[i].WeenieClassId}{weenieClassIdLabel}, " +
                    $"{input[i].StackSize}, " +
                    $"{input[i].Palette}{paletteLabel}, " +
                    $"{input[i].Shade:0.######}, " +
                    $"{input[i].TryToBond}, " +
                    $"{(input[i].ObjCellId.HasValue ? "0x" : "")}{input[i].ObjCellId:X8}{telelocLabel}, " +
                    $"{TrimNegativeZero(input[i].OriginX):0.######}, " +
                    $"{TrimNegativeZero(input[i].OriginY):0.######}, " +
                    $"{TrimNegativeZero(input[i].OriginZ):0.######}, " +
                    $"{TrimNegativeZero(input[i].AnglesW):0.######}, " +
                    $"{TrimNegativeZero(input[i].AnglesX):0.######}, " +
                    $"{TrimNegativeZero(input[i].AnglesY):0.######}, " +
                    $"{TrimNegativeZero(input[i].AnglesZ):0.######})";
            });

            ValuesWriter(input.Count, lineGenerator, writer);
        }
    }
}
