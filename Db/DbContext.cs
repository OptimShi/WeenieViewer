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

namespace WeenieViewer.Db
{
    public class DbContext
    {
        private SQLiteConnection sqlite;
        private MySqlConnection mysql;
        public bool usingSQLite { get; private set; }

        public DbContext() {
            usingSQLite = false;
            if (usingSQLite)
                InitSQLite();
            else
                InitMySQL();
        }

        public void Close()
        {
            sqlite.Close();
            mysql.Close();  
        }

        private bool InitSQLite()
        {
            string dbName = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "ace_world.db");
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
            string host = "localhost";
            string user = "root";
            string pass = "";
            string dbname = "ace_world";

            string connect = $"server={host};database={dbname};uid={user};pwd={pass}";
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
