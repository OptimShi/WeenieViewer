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

            WeenieViewerSettings.Default.Save();

            this.DialogResult = true;
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;
        }

        private void TestConnectionButton_Click(object sender, RoutedEventArgs e)
        {
            var dbType = ((ComboBoxItem)cbxDBType.SelectedItem).Content.ToString();
            switch (dbType)
            {
                case "SQLite":
                    break;
                case "MySQL":
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
                    break;
                case "MySQL":
                    MySQL_Options.Visibility = Visibility.Visible;
                    break;
            }
        }

        private void cbxWiki_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
