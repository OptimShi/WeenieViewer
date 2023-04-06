using EmoteScriptLib.Emotes;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Data.SQLite;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using WeenieViewer.Properties;

namespace WeenieViewer.Db
{
    public class DbContext
    {
        private SQLiteConnection sqlite;
        private MySqlConnection mysql;
        public bool usingSQLite { get; private set; }

        // Wether or not we successfully opened a database connection
        public bool Connected { get; private set; }

        public DbContext() {
            usingSQLite = WeenieViewerSettings.Default.DBType == "SQLite";
            if (usingSQLite)
                Connected = InitSQLite();
            else
                Connected = InitMySQL();
        }

        public void Close()
        {
            sqlite.Close();
            mysql.Close();  
        }

        private bool InitSQLite()
        {
            string dbName;
            if (WeenieViewerSettings.Default.sqlite_dbname != "")
                dbName = WeenieViewerSettings.Default.sqlite_dbname;
            else
                dbName = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "ace_world.db");

#if DEBUG
            dbName = "D:\\Web Development\\sqlite\\ace_world.db"; // For Testing Purposes
#endif
            if (!File.Exists(dbName))
            {
                //throw new FileNotFoundException("Could Not Find 'ace_world.db'");
                string ErrorMsg = "Fatal Error: Could not locate database.\n\n" +
                    "Please ensure ace_world.db is in your application folder.\n\n" +
                    "This application will now close.";
                MessageBox.Show(ErrorMsg, "WeenieViewer", MessageBoxButton.OK, MessageBoxImage.Error);
                Application.Current.Shutdown();
                return false;
            }

            try
            {
                sqlite = new SQLiteConnection("Data Source=" + dbName);
                // SQLitePCL.raw.SetProvider(new SQLitePCL.SQLite3Provider_e_sqlite3());
                sqlite.Open();
            }
            catch
            {
                return false;
            }
            return true;
        }

        private bool InitMySQL()
        {
            string host = WeenieViewerSettings.Default.mysql_host;
            string user = WeenieViewerSettings.Default.mysql_user;
            string pass = WeenieViewerSettings.Default.mysql_pass;
            string dbname = WeenieViewerSettings.Default.mysql_dbname;
            string port = WeenieViewerSettings.Default.mysql_port;

            string connect = $"server={host};port={port};database={dbname};uid={user};pwd={pass}";
            try
            {
                mysql = new MySqlConnection(connect);
                mysql.Open();
            }
            catch (Exception ex)
            {
                mysql.Close();
                return false;
            }

            return true;
        }

        public DbDataReader GetReader(string query, Dictionary<string, object> parameters = null)
        {
            if (usingSQLite)
            {
                var command = sqlite.CreateCommand();
                command.CommandText = query;

                if (parameters != null)
                    foreach (var p in parameters)
                        command.Parameters.AddWithValue(p.Key, p.Value);

                var reader = command.ExecuteReader();

                return reader;
            }
            else
            {
                var command = mysql.CreateCommand();
                command.CommandText = query;

                if (parameters != null)
                    foreach (var p in parameters)
                        command.Parameters.AddWithValue(p.Key, p.Value);

                var reader = command.ExecuteReader();

                return reader;
            }
        }

    }
}
