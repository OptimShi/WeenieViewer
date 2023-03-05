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

namespace WeenieViewer.Db
{
    internal class DbManager
    {
        SQLiteConnection sqlite;
        public string Version = "";

        public void Connect()
        {
            string dbName = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "ace_world.db");
            dbName = "D:\\Web Development\\sqlite\\ace_world.db";
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
            weenie.Bools = _GetBools(wcid);
            weenie.DIDs = _GetInts(wcid, "weenie_properties_d_i_d");
            weenie.Floats = _GetFloats(wcid);
            weenie.Ints = _GetInts(wcid);
            weenie.Int64s = _GetInt64s(wcid);
            weenie.IIDs = _GetInts(wcid, "weenie_properties_i_i_d");
            weenie.Strings = _GetStrings(wcid);
            return weenie;
        }

        private Dictionary<int, bool> _GetBools(int wcid)
        {
            Dictionary<int, bool> results = new Dictionary<int, bool>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_bool` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    string value = reader.GetString(reader.GetOrdinal("value"));
                    results.Add(key, key == 1);
                }
            }

            return results;
        }
        private Dictionary<int, float> _GetFloats(int wcid)
        {
            Dictionary<int, float> results = new Dictionary<int, float>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_float` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    float value = reader.GetFloat(reader.GetOrdinal("value"));
                    results.Add(key, value);
                }
            }

            return results;
        }

        private Dictionary<int, int> _GetInts(int wcid, string table = "weenie_properties_int")
        {
            Dictionary<int, int> results = new Dictionary<int, int>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `{table}` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);
            command.CommandType = CommandType.Text;

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    int value = reader.GetInt32(reader.GetOrdinal("value"));
                    results.Add(key, value);
                }
            }

            return results;
        }

        private Dictionary<int, long> _GetInt64s(int wcid)
        {
            Dictionary<int, long> results = new Dictionary<int, long>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_int64` WHERE `object_Id` = @wcid";
            command.Parameters.AddWithValue("@wcid", wcid);

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    long value = reader.GetInt64(reader.GetOrdinal("value"));
                    results.Add(key, value);
                }
            }

            return results;
        }


        private Dictionary<int, string> _GetStrings(int wcid)
        {
            Dictionary<int, string> results = new Dictionary<int, string>();
            var command = sqlite.CreateCommand();
            command.CommandText = $"SELECT `type`, `value` FROM `weenie_properties_string` WHERE `object_Id` = @wcid";
            command.Parameters.Add(new SQLiteParameter("@wcid", wcid));

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    int key = reader.GetInt32(reader.GetOrdinal("type"));
                    string value = reader.GetString(reader.GetOrdinal("value"));
                    results.Add(key, value);
                }
            }

            return results;
        }
    }
}
