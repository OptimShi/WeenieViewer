using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Data.SQLite;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
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
            if(!File.Exists(dbName))
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
    }
}
