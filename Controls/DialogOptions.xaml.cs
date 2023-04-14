using MySqlConnector;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml.Linq;
using WeenieViewer.Properties;

namespace WeenieViewer.Controls
{
    /// <summary>
    /// Interaction logic for DialogOptions.xaml
    /// </summary>
    public partial class DialogOptions : Window
    {
        public DialogOptions()
        {
            InitializeComponent();

            foreach (ComboBoxItem c in cbxDBType.Items)
            {
                if (c.Content.ToString() == WeenieViewerSettings.Default.DBType)
                {
                    c.IsSelected = true;
                    break;
                }
            }

            var useWiki = WeenieViewerSettings.Default.useWikia;
            if (useWiki)
                cbxWiki.SelectedIndex = 0;
            else
                cbxWiki.SelectedIndex = 1;

            txtMysqlDB.Text = WeenieViewerSettings.Default.mysql_dbname;
            txtMysqlHost.Text = WeenieViewerSettings.Default.mysql_host;
            txtMysqlPass.Text = WeenieViewerSettings.Default.mysql_pass;
            txtMysqlPort.Text = WeenieViewerSettings.Default.mysql_port;
            txtMysqlUser.Text = WeenieViewerSettings.Default.mysql_user;

            txtSQLiteDB.Text = WeenieViewerSettings.Default.sqlite_dbname;

            if (WeenieViewerSettings.Default.enableServerMenu == true)
                chkServerDebug.IsChecked = true;
            else
                chkServerDebug.IsChecked = false;
        }

        private void btnOK_Click(object sender, RoutedEventArgs e)
        {
            var wikiOption = cbxWiki.SelectedIndex;
            WeenieViewerSettings.Default.useWikia = (wikiOption == 0);
            WeenieViewerSettings.Default.DBType = ((ComboBoxItem)cbxDBType.SelectedItem).Content.ToString();

            WeenieViewerSettings.Default.mysql_dbname = txtMysqlDB.Text;
            WeenieViewerSettings.Default.mysql_host = txtMysqlHost.Text;
            WeenieViewerSettings.Default.mysql_pass = txtMysqlPass.Text;
            WeenieViewerSettings.Default.mysql_port = txtMysqlPort.Text;
            WeenieViewerSettings.Default.mysql_user = txtMysqlUser.Text;

            WeenieViewerSettings.Default.sqlite_dbname = txtSQLiteDB.Text;

            if (chkServerDebug.IsChecked == true)
                WeenieViewerSettings.Default.enableServerMenu = true;
            else
                WeenieViewerSettings.Default.enableServerMenu = false;

            WeenieViewerSettings.Default.Save();

            this.DialogResult = true;
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;
        }

        private void TestConnectionButton_Click(object sender, RoutedEventArgs e)
        {
            Mouse.OverrideCursor = Cursors.Wait;
            var dbType = ((ComboBoxItem)cbxDBType.SelectedItem).Content.ToString();
            switch (dbType)
            {
                case "SQLite":
                    // Do nothing, I guess...
                    break;
                case "MySQL":
                    string host = txtMysqlHost.Text.Trim();
                    string user = txtMysqlUser.Text.Trim();
                    string pass = txtMysqlPass.Text.Trim();
                    string dbname = txtMysqlDB.Text.Trim();
                    string port = txtMysqlPort.Text.Trim();

                    string connect = $"server={host};port={port};database={dbname};uid={user};pwd={pass}";
                    MySqlConnection mysql;
                    try
                    {
                        mysql = new MySqlConnection(connect);
                        mysql.Open();
                        var command = mysql.CreateCommand();
                        command.CommandText = "select * from weenie limit 1";
                        using (var reader = command.ExecuteReader())
                        {
                            while(reader.Read()) {
                                var classId = reader.GetInt32(reader.GetOrdinal("class_Id"));
                                string className = reader.GetString(reader.GetOrdinal("class_Name"));
                            }
                        }
                        mysql.Close();
                        mysql.Dispose();
                    }
                    catch (Exception ex)
                    {
                        string errorMsg = "Could not connect to MySQL Database.\n\n" + ex.Message;
                        Mouse.OverrideCursor = Cursors.Arrow;
                        MessageBox.Show(errorMsg, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                        return;
                    }
                    Mouse.OverrideCursor = Cursors.Arrow;
                    MessageBox.Show("Connection Successful!", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                    break;
            }
        }

        private void cbxDBType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var dbType = ((ComboBoxItem)cbxDBType.SelectedItem).Content.ToString();
            switch (dbType)
            {
                case "SQLite":
                    MySQL_Options.Visibility = Visibility.Collapsed;
                    SQLite_Options.Visibility = Visibility.Visible;
                    break;
                case "MySQL":
                    MySQL_Options.Visibility = Visibility.Visible;
                    SQLite_Options.Visibility = Visibility.Collapsed;
                    break;
            }
        }

        private void btnSQLiteBrowse_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.DefaultExt = ".txt"; // Default file extension
            dialog.Filter = "SQLite Database (.db)|*.db|All Files (*.*)|*.*"; // Filter files by extension
            dialog.FileName = System.IO.Path.GetFileName(txtSQLiteDB.Text); ; // Default file name

            dialog.InitialDirectory = System.IO.Path.GetDirectoryName(txtSQLiteDB.Text);

            // Show open file dialog box
            bool? result = dialog.ShowDialog();

            if (result == true)
            {
                txtSQLiteDB.Text = dialog.FileName;
            }
        }
    }
}
