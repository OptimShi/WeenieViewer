using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
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
using WeenieViewer.Db;

namespace WeenieViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DbManager db;

        public MainWindow()
        {
            InitializeComponent();

            // Init our SQLite Database
            db = new DbManager();
            db.Connect();
            lblVersion.Text = db.Version;
        }

        private void miExit_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        private void miSearchWeenies_Click(object sender, RoutedEventArgs e)
        {
           
        }

        public void DoDBSearch(string criteria)
        {
            tabGroup.SelectedItem = tabSearch;
            lstSearchResults.Items.Clear();
            if (criteria != "")
            {
                Dictionary<int, string> searchResults;
                var isNumeric = int.TryParse(criteria, out _);
                if (isNumeric)
                {
                    searchResults = db.SearchForWCID(criteria);
                }
                else
                {
                    searchResults = db.SearchForWeenie(criteria);
                }
                
                foreach(var w in searchResults)
                {
                    lstSearchResults.Items.Add(w.Value + " (" + w.Key +")");
                }
                //MessageBox.Show(searchResults.Count + " results found!");
            }

        }

        private void txtSearch_KeyDown(object sender, KeyEventArgs e)
        {
            DoDBSearch(txtSearch.Text.Trim());
        }
    }
}
