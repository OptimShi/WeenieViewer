using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SQLite;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Markup;
using MySqlConnector;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;

namespace WeenieViewer.Db
{
    public class DbManager
    {
        //private SQLiteConnection sqlite;
        public DbContext db;
        public string Version = "";
        public Dictionary<int, string> SpellNames;
        public Dictionary<string, Position> PointsOfInterest;
        public Dictionary<int, string> WeenieNames;


        public bool Connect()
        {
            db = new DbContext();
            if(db.Connected)
            {
                GetVersion();
                LoadWeenieNames();
                LoadSpells();
                LoadPointsOfInterest();
                return true;
            }

            return false;
        }

        public void Disconnect()
        {
            db.Close();
        }

        public void Dispose()
        {
            this.Disconnect();
        }

        private void GetVersion()
        {
            using (var reader = db.GetReader("SELECT * FROM `version`"))
            {
                while (reader.Read())
                {
                    string version_base = reader.GetString(reader.GetOrdinal("base_Version"));
                    string version_patch = reader.GetString(reader.GetOrdinal("patch_Version"));
                    var mod = reader.GetDateTime(reader.GetOrdinal("last_Modified"));

                    string dbType;
                    if (db.usingSQLite)
                        dbType = "SQLite";
                    else
                        dbType = "MySQL";
                    Version = $"{dbType} - ace_world Base: {version_base}, Patch: {version_patch}, Date: {mod.ToString()}";
                    //var object_Id = reader.Get(0);
                    //var WeenieName = reader.GetString(1);

                }
            }
        }

        public Dictionary<int, string> SearchForWeenie(string name)
        {
            Dictionary<string, object> dbParams = new Dictionary<string, object>();
            dbParams.Add("@name", "%" + name + "%");
            string sql = "SELECT `object_Id`, `value` FROM `weenie_properties_string` WHERE `type` = 1 and `value` like @name order by `object_Id` asc";

            Dictionary<int, string> results = new Dictionary<int, string>();

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    var object_Id = reader.GetInt32(0);
                    var WeenieName = reader.GetString(1);
                    results.Add(object_Id, WeenieName);
                }
            }
            return results;
        }

        public Dictionary<int, string> SearchForWCID(string WCID)
        {
            Dictionary<int, string> results = new Dictionary<int, string>();
            string sql =
                $"SELECT `object_Id`, `value` FROM `weenie_properties_string` WHERE `type` = 1 and `object_Id` = @wcid limit 1";

            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", WCID } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    var object_Id = reader.GetInt32(0);
                    var WeenieName = reader.GetString(1);
                    results.Add(object_Id, WeenieName);
                }
            }
            return results;
        }

        public void LoadWeenieNames()
        {
            if (WeenieNames == null)
            {
                WeenieNames = new Dictionary<int, string>();

                using (var reader = db.GetReader("SELECT object_Id, value FROM `weenie_properties_string` where `type` = 1 order by object_Id;"))
                {
                    while (reader.Read())
                    {
                        int wcid = reader.GetInt32(reader.GetOrdinal("object_Id"));
                        string name = reader.GetString(reader.GetOrdinal("value"));
                        WeenieNames.Add(wcid, name);
                    }
                }
            }
        }

        public void LoadSpells()
        {
            if (SpellNames == null)
            {
                SpellNames = new Dictionary<int, string>();

                using (var reader = db.GetReader("SELECT id, name FROM `spell`;"))
                {
                    while (reader.Read())
                    {
                        int id = reader.GetInt32(reader.GetOrdinal("id"));
                        string name = reader.GetString(reader.GetOrdinal("name"));
                        SpellNames.Add(id, name);
                    }
                }
            }
        }

        public void LoadPointsOfInterest()
        {
            if (PointsOfInterest == null)
            {
                PointsOfInterest = new Dictionary<string, Position>();

                string sql;
                if (db.usingSQLite)
                    sql = "SELECT poi.name, (p.obj_Cell_Id), p.origin_X, p.origin_Y, p.origin_Z FROM `points_of_interest` as poi, `weenie_properties_position` as p where p.object_Id = poi.weenie_Class_Id and p.position_Type = 2 group by poi.weenie_Class_Id;";
                else
                    sql = "SELECT poi.name, (p.obj_Cell_Id), p.origin_X, p.origin_Y, p.origin_Z FROM `points_of_interest` as poi, `weenie_properties_position` as p where p.object_Id = poi.weenie_Class_Id and p.position_Type = 2 group by poi.weenie_Class_Id;";
                using (var reader = db.GetReader(sql))
                {
                    while (reader.Read())
                    {
                        string name = reader.GetString(reader.GetOrdinal("name"));
                        var pos = new Position();
                        try {
                            pos.objCellId = Convert.ToUInt32(reader.GetValue(reader.GetOrdinal("obj_Cell_Id")));
                            pos.x = reader.GetFloat(reader.GetOrdinal("origin_X"));
                            pos.y = reader.GetFloat(reader.GetOrdinal("origin_Y"));
                            pos.z = reader.GetFloat(reader.GetOrdinal("origin_Z"));
                            PointsOfInterest.Add(name, pos);
                        }
                        catch
                        {

                        }
                    }
                }
            }
        }

        public dbWeenie GetWeenie(int wcid)
        {
            dbWeenie weenie = new dbWeenie();

            string sql = "SELECT * FROM `weenie` where `class_Id` = @wcid limit 1;";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    weenie.WeenieClass = reader.GetString(reader.GetOrdinal("class_Name"));
                    weenie.WeenieType = reader.GetInt32(reader.GetOrdinal("type"));
                }
            }

            weenie.Bools = _GetBools(wcid);
            weenie.DIDs = _GetDIDs(wcid);
            weenie.Floats = _GetFloats(wcid);
            weenie.Ints = _GetInts(wcid);
            weenie.Int64s = _GetInt64s(wcid);
            weenie.IIDs = _GetIIDs(wcid);
            weenie.Strings = _GetStrings(wcid);
            weenie.SpellBook = _GetSpellBook(wcid);

            weenie.Book = _GetBook(wcid);
            weenie.BookData = _GetBookPageData(wcid);

            weenie.Attributes = _GetAttributes(wcid);
            weenie.Attributes2nd = _GetAttributes2nd(wcid);
            weenie.Skills = _GetSkills(wcid);
            foreach(var s in weenie.Skills)
            {
                s.Value.CurrentValue = weenie.GetSkillLevel(s.Key);
                //weenie.Skills[s.Key] = s.Value;
            }

            weenie.CreateList = _GetCreateList(wcid);
            weenie.SoldBy = _GetItemInCreateList(wcid);
            weenie.Positions = _GetPositions(wcid);

            //weenie.Emotes = new List<Emote>();
            weenie.Emotes = _GetEmotes(wcid);

            return weenie;
        }

        private Dictionary<PropertyBool, bool> _GetBools(int wcid)
        {
            Dictionary<PropertyBool, bool> results = new Dictionary<PropertyBool, bool>();

            string sql = "SELECT `type`, `value` FROM `weenie_properties_bool` WHERE `object_Id` = @wcid order by `type`";
            Dictionary<string, object> dbParams = new Dictionary<string, object>();
            dbParams.Add("@wcid", wcid);
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    int value = reader.GetInt32(reader.GetOrdinal("value"));
                    results.Add((PropertyBool)key, value == 1);
                }
            }

            return results;
        }

        private Dictionary<PropertyFloat, float> _GetFloats(int wcid)
        {
            Dictionary<PropertyFloat, float> results = new Dictionary<PropertyFloat, float>();
            var sql = $"SELECT `type`, `value` FROM `weenie_properties_float` WHERE `object_Id` = @wcid order by `type`";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    float value = reader.GetFloat(reader.GetOrdinal("value"));
                    results.Add((PropertyFloat)key, value);
                }
            }

            return results;
        }

        private Dictionary<PropertyInt, int> _GetInts(int wcid)
        {
            Dictionary<PropertyInt, int> results = new Dictionary<PropertyInt, int>();
            var sql = $"SELECT `type`, `value` FROM `weenie_properties_int` WHERE `object_Id` = @wcid order by `type`";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    int value = reader.GetInt32(reader.GetOrdinal("value"));
                    results.Add((PropertyInt)key, value);
                }
            }

            return results;
        }

        private Dictionary<PropertyIID, int> _GetIIDs(int wcid)
        {
            Dictionary<PropertyIID, int> results = new Dictionary<PropertyIID, int>();
            var sql = $"SELECT `type`, `value` FROM `weenie_properties_i_i_d` WHERE `object_Id` = @wcid order by `type`";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    int value = reader.GetInt32(reader.GetOrdinal("value"));
                    results.Add((PropertyIID)key, value);
                }
            }

            return results;
        }

        private Dictionary<PropertyDID, int> _GetDIDs(int wcid)
        {
            Dictionary<PropertyDID, int> results = new Dictionary<PropertyDID, int>();
            var sql = $"SELECT `type`, `value` FROM `weenie_properties_d_i_d` WHERE `object_Id` = @wcid order by `type`";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    int value = reader.GetInt32(reader.GetOrdinal("value"));
                    results.Add((PropertyDID)key, value);
                }
            }

            return results;
        }

        private Dictionary<PropertyInt64, long> _GetInt64s(int wcid)
        {
            Dictionary<PropertyInt64, long> results = new Dictionary<PropertyInt64, long>();
            var sql = $"SELECT `type`, `value` FROM `weenie_properties_int64` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    long value = reader.GetInt64(reader.GetOrdinal("value"));
                    results.Add((PropertyInt64)key, value);
                }
            }

            return results;
        }


        private Dictionary<PropertyString, string> _GetStrings(int wcid)
        {
            Dictionary<PropertyString, string> results = new Dictionary<PropertyString, string>();
            var sql = $"SELECT `type`, `value` FROM `weenie_properties_string` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    string value = reader.GetString(reader.GetOrdinal("value"));
                    results.Add((PropertyString)key, value);
                }
            }

            return results;
        }

        private List<SpellBook> _GetSpellBook(int wcid)
        {
            LoadSpells();

            List<SpellBook> results = new List<SpellBook>();
            var sql = $"SELECT `spell`, `probability` FROM `weenie_properties_spell_book` WHERE `object_Id` = @wcid order by `id`";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    SpellBook spellBook = new SpellBook();
                    spellBook.SpellId = reader.GetInt32(reader.GetOrdinal("spell"));
                    spellBook.Probability = reader.GetFloat(reader.GetOrdinal("probability"));
                    spellBook.Name = GetSpellName(spellBook.SpellId);
                    results.Add(spellBook);
                }
            }

            return results;
        }

        private Book _GetBook(int wcid)
        {
            Book results = new Book();
            var sql = $"SELECT * FROM `weenie_properties_book` WHERE `object_Id` = @wcid limit 1";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    BookPageData page = new BookPageData();
                    results.BookMaxPages = reader.GetInt32(reader.GetOrdinal("max_Num_Pages"));
                    results.BookMaxCharsPerPage = reader.GetInt32(reader.GetOrdinal("max_Num_Chars_Per_Page"));
                }
            }

            return results;
        }

        private Dictionary<int, BookPageData> _GetBookPageData(int wcid)
        {
            Dictionary<int, BookPageData> results = new Dictionary<int, BookPageData>();
            var sql = $"SELECT * FROM `weenie_properties_book_page_data` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    BookPageData page = new BookPageData();
                    page.PageId = reader.GetInt32(reader.GetOrdinal("page_Id"));
                    page.AuthorId= reader.GetInt64(reader.GetOrdinal("author_Id"));
                    page.AuthorName = reader.GetString(reader.GetOrdinal("author_Name"));
                    page.AuthorAccount = reader.GetString(reader.GetOrdinal("author_Account"));

                    var ignore = reader.GetInt32(reader.GetOrdinal("ignore_Author"));
                    page.IgnoreAuthor = ignore == 1;

                    page.PageText = reader.GetString(reader.GetOrdinal("page_Text"));

                    results.Add(page.PageId, page);
                }
            }

            return results;
        }

        public string GetSpellName(int spell_id)
        {
            if (SpellNames.ContainsKey(spell_id))
                return SpellNames[spell_id];

            return null;
        }

        private Dictionary<int, weenie.Skill> _GetSkills(int wcid)
        {
            var results = new Dictionary<int, weenie.Skill>();
            var sql = $"SELECT * FROM `weenie_properties_skill` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    weenie.Skill skill = new weenie.Skill();
                    skill.type = reader.GetInt32(reader.GetOrdinal("type"));
                    skill.level_from_pp = reader.GetInt32(reader.GetOrdinal("level_From_P_P"));
                    skill.sac = reader.GetInt32(reader.GetOrdinal("s_a_c"));
                    skill.pp = reader.GetInt32(reader.GetOrdinal("p_p"));
                    skill.init_level = reader.GetInt32(reader.GetOrdinal("init_Level"));
                    skill.resistant_at_last_check = reader.GetInt32(reader.GetOrdinal("resistance_At_Last_Check"));
                    skill.last_used_time = reader.GetDouble(reader.GetOrdinal("last_Used_Time"));
                    results.Add(skill.type, skill);
                }
            }

            return results;
        }

        private List<Position> _GetPositions(int wcid)
        {
            var results = new List<Position>();

            // Lookup fixed positions
            var sql = $"SELECT * FROM `weenie_properties_position` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    weenie.Position pos = new weenie.Position();
                    pos.positionType = reader.GetInt32(reader.GetOrdinal("position_Type"));
                    pos.objCellId = (uint)reader.GetInt64(reader.GetOrdinal("obj_Cell_Id"));

                    pos.x = reader.GetFloat(reader.GetOrdinal("origin_X"));
                    pos.y = reader.GetFloat(reader.GetOrdinal("origin_Y"));
                    pos.z = reader.GetFloat(reader.GetOrdinal("origin_Z"));

                    pos.qw = reader.GetFloat(reader.GetOrdinal("angles_W"));
                    pos.qx = reader.GetFloat(reader.GetOrdinal("angles_X"));
                    pos.qy = reader.GetFloat(reader.GetOrdinal("angles_Y"));
                    pos.qz = reader.GetFloat(reader.GetOrdinal("angles_Z"));

                    results.Add(pos);
                }
            }
            sql = $"SELECT * FROM `landblock_instance` WHERE `weenie_Class_Id` = @wcid";
            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    weenie.Position pos = new weenie.Position();
                    pos.positionType = -1;
                    pos.objCellId = (uint)reader.GetInt64(reader.GetOrdinal("obj_Cell_Id"));

                    pos.x = reader.GetFloat(reader.GetOrdinal("origin_X"));
                    pos.y = reader.GetFloat(reader.GetOrdinal("origin_Y"));
                    pos.z = reader.GetFloat(reader.GetOrdinal("origin_Z"));

                    pos.qw = reader.GetFloat(reader.GetOrdinal("angles_W"));
                    pos.qx = reader.GetFloat(reader.GetOrdinal("angles_X"));
                    pos.qy = reader.GetFloat(reader.GetOrdinal("angles_Y"));
                    pos.qz = reader.GetFloat(reader.GetOrdinal("angles_Z"));

                    results.Add(pos);
                }
            }

            return results;
        }

        private Dictionary<int, Attributes2nd> _GetAttributes2nd(int wcid)
        {
            var results = new Dictionary<int, Attributes2nd>();
            var sql = $"SELECT * FROM `weenie_properties_attribute_2nd` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    Attributes2nd att = new Attributes2nd();
                    att.type = reader.GetInt32(reader.GetOrdinal("type"));
                    att.level_from_cp = reader.GetInt32(reader.GetOrdinal("level_From_C_P"));
                    att.cp_spent = reader.GetInt32(reader.GetOrdinal("c_P_Spent"));
                    att.init_level = reader.GetInt32(reader.GetOrdinal("init_Level"));
                    att.current_level = reader.GetInt32(reader.GetOrdinal("current_Level"));
                    results.Add(att.type, att);
                }
            }

            return results;
        }

        private Dictionary<int, Attributes> _GetAttributes(int wcid)
        {
            var results = new Dictionary<int, Attributes>();
            var sql = $"SELECT * FROM `weenie_properties_attribute` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    Attributes att = new Attributes();
                    att.type = reader.GetInt32(reader.GetOrdinal("type"));
                    att.level_from_cp = reader.GetInt32(reader.GetOrdinal("level_From_C_P"));
                    att.cp_spent = reader.GetInt32(reader.GetOrdinal("c_P_Spent"));
                    att.init_level = reader.GetInt32(reader.GetOrdinal("init_Level"));
                    results.Add(att.type, att);
                }
            }

            return results;
        }

        private List<CreateListItem> _GetCreateList(int wcid)
        {
            var results = new List<CreateListItem>();
            //command.CommandText = $"SELECT * FROM `weenie_properties_create_list` WHERE `object_Id` = @wcid";
            var sql = "SELECT cl.weenie_Class_Id as wcid, s.value as name, i.value as value, cl.* FROM `weenie_properties_create_list` as cl " +
                "left join `weenie_properties_string` as s on s.object_Id = cl.weenie_Class_Id and s.type = 1 " + 
                "left join `weenie_properties_int` as i on i.object_Id = cl.weenie_Class_Id and i.type = 19 " + 
                "WHERE cl.`object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    CreateListItem cl = new CreateListItem();
                    cl.objectId = reader.GetInt32(reader.GetOrdinal("object_Id"));
                    cl.destinationType = reader.GetInt32(reader.GetOrdinal("destination_Type"));
                    cl.wcid = reader.GetInt32(reader.GetOrdinal("weenie_Class_Id"));
                    cl.stackSize = reader.GetInt32(reader.GetOrdinal("stack_Size"));
                    cl.palette = reader.GetInt32(reader.GetOrdinal("palette"));
                    cl.shade = reader.GetFloat(reader.GetOrdinal("shade"));
                    
                    var tempBond = reader.GetInt32(reader.GetOrdinal("try_To_Bond"));
                    cl.tryToBond = tempBond == 1;

                    if (!reader.IsDBNull(reader.GetOrdinal("name")))
                        cl.name = reader.GetString(reader.GetOrdinal("name"));
                    else
                        cl.name = "(Missing Item)";

                    if (!reader.IsDBNull(reader.GetOrdinal("value")))
                        cl.value = reader.GetInt32(reader.GetOrdinal("value"));
                    else
                        cl.value = 0;
                    
                    results.Add(cl);
                }
            }
            return results;
        }

        /// <summary>
        /// Returns a list of objects that have the specificied item in their create list
        /// </summary>
        /// <param name="wcid"></param>
        /// <returns></returns>
        private List<CreateListItem> _GetItemInCreateList(int wcid)
        {
            var results = new List<CreateListItem>();
            var sql = "SELECT cl.weenie_Class_Id as wcid, s.value as name, cl.* " +
                                "FROM `weenie_properties_string` as s, `weenie_properties_create_list` as cl " +
                                "WHERE cl.`weenie_Class_Id` = @wcid and s.type = 1 and s.object_Id = cl.object_Id";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    CreateListItem cl = new CreateListItem();
                    cl.objectId = reader.GetInt32(reader.GetOrdinal("object_Id"));
                    cl.destinationType = reader.GetInt32(reader.GetOrdinal("destination_Type"));
                    cl.wcid = reader.GetInt32(reader.GetOrdinal("weenie_Class_Id"));
                    cl.stackSize = reader.GetInt32(reader.GetOrdinal("stack_Size"));
                    cl.palette = reader.GetInt32(reader.GetOrdinal("palette"));
                    cl.shade = reader.GetFloat(reader.GetOrdinal("shade"));

                    var tempBond = reader.GetInt32(reader.GetOrdinal("try_To_Bond"));
                    cl.tryToBond = tempBond == 1;

                    cl.ownerWcid = cl.objectId;
                    if (!reader.IsDBNull(reader.GetOrdinal("name")))
                        cl.ownerName = reader.GetString(reader.GetOrdinal("name"));
                    else
                        cl.ownerName = "(Missing Item)";

                    results.Add(cl);
                }
            }
            return results;
        }

        private List<Emote> _GetEmotes(int wcid)
        {
            var results = new Dictionary<int, Emote>();
            List<int> emoteIds = new List<int>();

            string sql = $"SELECT * FROM `weenie_properties_emote` WHERE `object_Id` = @wcid";
            Dictionary<string, object> dbParams = new Dictionary<string, object> { { "@wcid", wcid } };

            using (var reader = db.GetReader(sql, dbParams))
            {
                while (reader.Read())
                {
                    int emoteId = reader.GetInt32(reader.GetOrdinal("id"));
                    weenie.Emote emote = new weenie.Emote();
                    emote.ObjectId = reader.GetInt32(reader.GetOrdinal("object_Id"));
                    emote.Category = reader.GetInt32(reader.GetOrdinal("category"));
                    emote.Probability = reader.GetFloat(reader.GetOrdinal("probability"));
                    if(!reader.IsDBNull(reader.GetOrdinal("weenie_Class_Id")))
                        emote.WeenieClassId = reader.GetInt32(reader.GetOrdinal("weenie_Class_Id"));
                    if (!reader.IsDBNull(reader.GetOrdinal("style")))
                        emote.Style = (uint)reader.GetInt64(reader.GetOrdinal("style"));
                    if (!reader.IsDBNull(reader.GetOrdinal("substyle")))
                        emote.Substyle = (uint)reader.GetInt64(reader.GetOrdinal("substyle"));
                    if (!reader.IsDBNull(reader.GetOrdinal("quest")))
                        emote.Quest = reader.GetString(reader.GetOrdinal("quest"));
                    if (!reader.IsDBNull(reader.GetOrdinal("vendor_Type")))
                        emote.VendorType = reader.GetInt32(reader.GetOrdinal("vendor_Type"));
                    if (!reader.IsDBNull(reader.GetOrdinal("min_Health")))
                        emote.MinHealth = reader.GetFloat(reader.GetOrdinal("min_Health"));
                    if (!reader.IsDBNull(reader.GetOrdinal("max_Health")))
                        emote.MaxHealth = reader.GetFloat(reader.GetOrdinal("max_Health"));

                    emoteIds.Add(emoteId);
                   // emote.EmoteAction = _GetEmoteActions(emoteId);

                    results.Add(emoteId, emote);
                }
            }

            var EmoteActions = _GetEmoteActions(emoteIds);
            foreach(var emoteAction in EmoteActions)
            {
                results[emoteAction.Key].EmoteAction = emoteAction.Value;
            }
            return results.Values.ToList();
        }

        /// <summary>
        /// Much faster to do one in "IN" query for all emotes for this Weenie, then one query for each emoteId on its own...
        /// </summary>
        /// <param name="EmoteIds"></param>
        /// <returns></returns>
        private Dictionary<int, List<EmoteAction>> _GetEmoteActions(List<int> EmoteIds)
        {
            var results = new Dictionary<int, List<EmoteAction>>();

            string inClause = "";
            for(var i = 0; i< EmoteIds.Count; i++)
            {
                inClause += EmoteIds[i].ToString() + ",";
            }
            inClause = inClause.TrimEnd(new Char[] { ',' });
            if(inClause.Length > 0 ) { 
                string sql = $"SELECT * FROM `weenie_properties_emote_action` WHERE `emote_Id` in ({inClause}) order by `order`";
                //command.Parameters.Add(new SQLiteParameter("@inClause", inClause));

                using (var reader = db.GetReader(sql))
                {
                    while (reader.Read())
                    {
                        EmoteAction action = new EmoteAction();
                        action.Id = reader.GetInt32(reader.GetOrdinal("id"));
                        action.EmoteId = reader.GetInt32(reader.GetOrdinal("emote_Id"));
                        action.Order = (uint)reader.GetInt32(reader.GetOrdinal("order"));
                        action.Type = (uint)reader.GetInt32(reader.GetOrdinal("type"));
                        action.Delay = reader.GetFloat(reader.GetOrdinal("delay"));
                        action.Extent = reader.GetFloat(reader.GetOrdinal("extent"));
                        if (!reader.IsDBNull(reader.GetOrdinal("motion")))
                            action.Motion = (uint)reader.GetInt32(reader.GetOrdinal("motion"));
                        if (!reader.IsDBNull(reader.GetOrdinal("message")))
                            action.Message = reader.GetString(reader.GetOrdinal("message"));
                        if (!reader.IsDBNull(reader.GetOrdinal("test_String")))
                            action.TestString = reader.GetString(reader.GetOrdinal("test_String"));
                        if (!reader.IsDBNull(reader.GetOrdinal("min")))
                            action.Min = reader.GetInt32(reader.GetOrdinal("min"));
                        if (!reader.IsDBNull(reader.GetOrdinal("max")))
                            action.Max = reader.GetInt32(reader.GetOrdinal("max"));
                        if (!reader.IsDBNull(reader.GetOrdinal("min_64")))
                            action.Min64 = reader.GetInt64(reader.GetOrdinal("min_64"));
                        if (!reader.IsDBNull(reader.GetOrdinal("max_64")))
                            action.Max64 = reader.GetInt64(reader.GetOrdinal("max_64"));
                        if (!reader.IsDBNull(reader.GetOrdinal("min_Dbl")))
                            action.MinDbl = reader.GetDouble(reader.GetOrdinal("min_Dbl"));
                        if (!reader.IsDBNull(reader.GetOrdinal("max_Dbl")))
                            action.MaxDbl = reader.GetDouble(reader.GetOrdinal("max_Dbl"));
                        if (!reader.IsDBNull(reader.GetOrdinal("stat")))
                            action.Stat = reader.GetInt32(reader.GetOrdinal("stat"));
                        if (!reader.IsDBNull(reader.GetOrdinal("display")))
                            action.Display = reader.GetBoolean(reader.GetOrdinal("display"));
                        if (!reader.IsDBNull(reader.GetOrdinal("amount")))
                            action.Amount = reader.GetInt32(reader.GetOrdinal("amount"));
                        if (!reader.IsDBNull(reader.GetOrdinal("amount_64")))
                            action.Amount64 = reader.GetInt64(reader.GetOrdinal("amount_64"));
                        if (!reader.IsDBNull(reader.GetOrdinal("hero_X_P_64")))
                            action.HeroXP64 = reader.GetInt64(reader.GetOrdinal("hero_X_P_64"));
                        if (!reader.IsDBNull(reader.GetOrdinal("percent")))
                            action.Percent = reader.GetDouble(reader.GetOrdinal("percent"));
                        if (!reader.IsDBNull(reader.GetOrdinal("spell_Id")))
                            action.SpellId = reader.GetInt32(reader.GetOrdinal("spell_Id"));
                        if (!reader.IsDBNull(reader.GetOrdinal("wealth_Rating")))
                            action.WealthRating = reader.GetInt32(reader.GetOrdinal("wealth_Rating"));
                        if (!reader.IsDBNull(reader.GetOrdinal("treasure_Class")))
                            action.TreasureClass = reader.GetInt32(reader.GetOrdinal("treasure_Class"));
                        if (!reader.IsDBNull(reader.GetOrdinal("treasure_Type")))
                            action.TreasureType = reader.GetInt32(reader.GetOrdinal("treasure_Type"));
                        if (!reader.IsDBNull(reader.GetOrdinal("p_Script")))
                            action.PScript = reader.GetInt32(reader.GetOrdinal("p_Script"));
                        if (!reader.IsDBNull(reader.GetOrdinal("sound")))
                            action.Sound = reader.GetInt32(reader.GetOrdinal("sound"));
                        if (!reader.IsDBNull(reader.GetOrdinal("destination_Type")))
                            action.DestinationType = reader.GetInt32(reader.GetOrdinal("destination_Type"));
                        if (!reader.IsDBNull(reader.GetOrdinal("weenie_Class_Id")))
                            action.WeenieClassId = (uint)reader.GetInt32(reader.GetOrdinal("weenie_Class_Id"));
                        if (!reader.IsDBNull(reader.GetOrdinal("stack_Size")))
                            action.StackSize = reader.GetInt32(reader.GetOrdinal("stack_Size"));
                        if (!reader.IsDBNull(reader.GetOrdinal("palette")))
                            action.Palette = reader.GetInt32(reader.GetOrdinal("palette"));
                        if (!reader.IsDBNull(reader.GetOrdinal("shade")))
                            action.Shade = reader.GetFloat(reader.GetOrdinal("shade"));
                        if (!reader.IsDBNull(reader.GetOrdinal("try_To_Bond")))
                            action.TryToBond = reader.GetBoolean(reader.GetOrdinal("try_To_Bond"));
                        if (!reader.IsDBNull(reader.GetOrdinal("obj_Cell_Id")))
                            action.ObjCellId = (uint)reader.GetInt32(reader.GetOrdinal("obj_Cell_Id"));
                        if (!reader.IsDBNull(reader.GetOrdinal("origin_X")))
                            action.OriginX = reader.GetFloat(reader.GetOrdinal("origin_X"));
                        if (!reader.IsDBNull(reader.GetOrdinal("origin_Y")))
                            action.OriginY = reader.GetFloat(reader.GetOrdinal("origin_Y"));
                        if (!reader.IsDBNull(reader.GetOrdinal("origin_Z")))
                            action.OriginZ = reader.GetFloat(reader.GetOrdinal("origin_Z"));
                        if (!reader.IsDBNull(reader.GetOrdinal("angles_W")))
                            action.AnglesW = reader.GetFloat(reader.GetOrdinal("angles_W"));
                        if (!reader.IsDBNull(reader.GetOrdinal("angles_X")))
                            action.AnglesX = reader.GetFloat(reader.GetOrdinal("angles_X"));
                        if (!reader.IsDBNull(reader.GetOrdinal("angles_Y")))
                            action.AnglesY = reader.GetFloat(reader.GetOrdinal("angles_Y"));
                        if (!reader.IsDBNull(reader.GetOrdinal("angles_Z")))
                            action.AnglesZ = reader.GetFloat(reader.GetOrdinal("angles_Z"));

                        if (results.ContainsKey(action.EmoteId))
                            results[action.EmoteId].Add(action);
                        else
                        {
                            List<EmoteAction> actions = new List<EmoteAction> { action };
                            results.Add(action.EmoteId, actions);
                        }
                    }
                }
            }

            return results;
        }


    }
}
