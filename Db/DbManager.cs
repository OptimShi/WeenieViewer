using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Data.SQLite;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Markup;
using System.Xml.Linq;
using WeenieViewer.Db.weenie;
using WeenieViewer.Enums;

namespace WeenieViewer.Db
{
    internal class DbManager
    {
        SQLiteConnection sqlite;
        public string Version = "";

        public void Connect()
        {
            string dbName = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "ace_world.db");
            //dbName = "D:\\Web Development\\sqlite\\ace_world.db"; // For Testing Purposes
            if (!File.Exists(dbName))
            {
                //throw new FileNotFoundException("Could Not Find 'ace_world.db'");
                MessageBox.Show("Fatal Error:\nCould not locate database.\nThis application will now close.", "WeenieViewer", MessageBoxButton.OK, MessageBoxImage.Error);
                Application.Current.Shutdown();
                return;
            }
            sqlite = new SQLiteConnection("Data Source=" + dbName);
            // SQLitePCL.raw.SetProvider(new SQLitePCL.SQLite3Provider_e_sqlite3());
            sqlite.Open();

            GetVersion();
        }

        public void Disconnect()
        {
            sqlite.Close();
        }

        public void Dispose()
        {
            this.Disconnect();
        }

        private void GetVersion()
        {
            var command = sqlite.CreateCommand();
            command.CommandText = "SELECT * FROM `version`";
            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    string version_base = reader.GetString(reader.GetOrdinal("base_Version"));
                    string version_patch = reader.GetString(reader.GetOrdinal("patch_Version"));
                    var mod = reader.GetDateTime(reader.GetOrdinal("last_Modified"));

                    Version = $"ace_world Base: {version_base}, Patch: {version_patch}, Date: {mod.ToString()}";
                    //var object_Id = reader.Get(0);
                    //var WeenieName = reader.GetString(1);

                }
            }
        }

        public Dictionary<int, string> SearchForWeenie(string name)
        {
            Dictionary<int, string> results = new Dictionary<int, string>();
            var command = sqlite.CreateCommand();
            command.CommandText =
                $"SELECT `object_Id`, `value` FROM `weenie_properties_string` WHERE `type` = 1 and `value` like '%{name}%' order by `object_Id` asc";
            //command.Parameters.AddWithValue("$name", name);

            using (var reader = command.ExecuteReader())
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
            var command = sqlite.CreateCommand();
            command.CommandText =
                $"SELECT `object_Id`, `value` FROM `weenie_properties_string` WHERE `type` = 1 and `object_Id` = @wcid limit 1";
            command.Parameters.AddWithValue("@wcid", WCID);

            using (var reader = command.ExecuteReader())
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

        public dbWeenie GetWeenie(int wcid)
        {

            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT * FROM sqlite_master where type='table';";
            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    string value = reader.GetString(reader.GetOrdinal("tbl_name"));
                }
            }

            dbWeenie weenie = new dbWeenie();

            command.Reset();
            command = sqlite.CreateCommand();
            command.CommandText = $"SELECT * FROM `weenie` where `class_Id` = @wcid limit 1;";
            command.Parameters.AddWithValue("@wcid", wcid);
            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    weenie.WeenieClass = reader.GetString(reader.GetOrdinal("class_Name"));
                    weenie.WeenieType = reader.GetInt32(reader.GetOrdinal("type"));
                }
            }

            command.Reset();
            command = sqlite.CreateCommand();
            command.CommandText = $"SELECT count(*) as myCount FROM `weenie_properties_book_page_data`;";
            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    var counter = reader.GetInt32(reader.GetOrdinal("myCount"));
                }
            }

            weenie.Bools = _GetBools(wcid);
            weenie.DIDs = _GetDIDs(wcid);
            weenie.Floats = _GetFloats(wcid);
            weenie.Ints = _GetInts(wcid);
            weenie.Int64s = _GetInt64s(wcid);
            weenie.IIDs = _GetIIDs(wcid);
            weenie.Strings = _GetStrings(wcid);
            weenie.BookData = _GetBookPageData(wcid);
            
            return weenie;
        }

        private Dictionary<PropertyBool, bool> _GetBools(int wcid)
        {
            Dictionary<PropertyBool, bool> results = new Dictionary<PropertyBool, bool>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_bool` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    int value = reader.GetInt32(reader.GetOrdinal("type"));
                    results.Add((PropertyBool)key, value == 1);
                }
            }

            return results;
        }

        private Dictionary<PropertyFloat, float> _GetFloats(int wcid)
        {
            Dictionary<PropertyFloat, float> results = new Dictionary<PropertyFloat, float>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_float` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);

            using (var reader = command.ExecuteReader())
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
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_int` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);
            command.CommandType = CommandType.Text;

            using (var reader = command.ExecuteReader())
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
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_i_i_d` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);
            command.CommandType = CommandType.Text;

            using (var reader = command.ExecuteReader())
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
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_d_i_d` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);
            command.CommandType = CommandType.Text;

            using (var reader = command.ExecuteReader())
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
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_int64` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);

            using (var reader = command.ExecuteReader())
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
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_string` WHERE `object_Id` = @wcid";
            command.Parameters.Add(new SQLiteParameter("@wcid", wcid));

            using (var reader = command.ExecuteReader())
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

        private Dictionary<int, BookPageData> _GetBookPageData(int wcid)
        {
            Dictionary<int, BookPageData> results = new Dictionary<int, BookPageData>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT * FROM `weenie_properties_book_page_data` WHERE `object_Id` = @wcid";
            command.Parameters.Add(new SQLiteParameter("@wcid", wcid));

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    BookPageData page = new BookPageData();
                    page.PageId = reader.GetInt32(reader.GetOrdinal("page_Id"));
                    page.AuthorId= reader.GetInt32(reader.GetOrdinal("author_Id"));
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
    }
}
