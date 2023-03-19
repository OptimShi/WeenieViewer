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
using WeenieViewer.Controls;
using WeenieViewer.Db;

namespace WeenieViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public DbManager db;

        public MainWindow()
        {
            InitializeComponent();
            lblResultsCount.Text = "";
            lblVersion.Text = "";
            btnCloseTab.Visibility = Visibility.Hidden;

            // Init our SQLite Database
            db = new DbManager();
            db.Connect();
            lblVersion.Text = db.Version;

            txtSearch.TextChanged += new TextChangedEventHandler(txtSearch_TextChanged);
            txtSearch.Focus();

            SetupHotKeys();
            // txtSearch.Text = "Asheron"; 
        }

        private void miExit_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        public void DoDBSearch(string criteria)
        {
            if (criteria != "")
            {
                tabGroup.SelectedItem = tabSearch;
                lstSearchResults.Items.Clear();

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

                lblResultsCount.Text = searchResults.Count.ToString() + " Results";
                //MessageBox.Show(searchResults.Count + " results found!");
            }

        }

        private void txtSearch_KeyDown(object sender, KeyEventArgs e)
        {
            DoDBSearch(txtSearch.Text.Trim());
        }

        private void lstSearchResults_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if(lstSearchResults.HasItems && lstSearchResults.SelectedItem != null)
            {
                string selectedItem = lstSearchResults.SelectedValue.ToString();

                int wcidLength = selectedItem.LastIndexOf(')') - selectedItem.LastIndexOf('(') - 1;
                var selectedWCID = selectedItem.Substring(selectedItem.LastIndexOf('(')+1, wcidLength);

                // Does this tab already exist?
                var tabExists = tabGroup.Items.OfType<TabItem>().SingleOrDefault(n => n.Header.ToString() == selectedItem);
                if (tabExists != null)
                {
                    // Bring the tab forward
                    tabGroup.SelectedItem = tabExists;
                }
                else
                {
                    // Create our new tab.
                    //var newTab = new TabWeenie() {};
                    TabItem newWeenieTabItem = new TabItem
                    {
                        Header = selectedItem,
                        Name = "tab_" + selectedWCID.ToString()
                    };
                    TabWeenie weenieTabContent = new TabWeenie();
                    newWeenieTabItem.Content = weenieTabContent;
                    var weenie = db.GetWeenie(Int32.Parse(selectedWCID));
                    weenieTabContent.DisplayWeenie(weenie);

                    tabGroup.Items.Add(newWeenieTabItem);
                    tabGroup.SelectedItem = newWeenieTabItem;
                }

            }
        }

        private void txtSearch_TextChanged(object sender, TextChangedEventArgs e)
        {
            DoDBSearch(txtSearch.Text.Trim());
        }

        private void tabGroup_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // Check if the current selected tab is the "Search Results" tab -- if so, hide the Close button
            TabItem ti = tabGroup.SelectedItem as TabItem;
            if(ti == null || ti.Name == "tabSearch")
            {
                btnCloseTab.Visibility = Visibility.Collapsed;
                lblResultsCount.Visibility = Visibility.Visible;
            }
            else
            {
                btnCloseTab.Visibility = Visibility.Visible;
                lblResultsCount.Visibility = Visibility.Collapsed;
            }
        }

        private void btnCloseTab_Click(object sender, RoutedEventArgs e)
        {
            TabItem ti = tabGroup.SelectedItem as TabItem;
            tabGroup.Items.Remove(ti);
            e.Handled = true;
        }

        private void miSearchWeenies_Click(object sender, RoutedEventArgs e)
        {
            tabGroup.SelectedItem = tabSearch;
        }

        private void SetupHotKeys()
        {
            try
            {
                RoutedCommand firstSettings = new RoutedCommand();
                firstSettings.InputGestures.Add(new KeyGesture(Key.W, ModifierKeys.Control));
                CommandBindings.Add(new CommandBinding(firstSettings, CloseTab));

                var spellSearch = new RoutedCommand();
                spellSearch.InputGestures.Add(new KeyGesture(Key.S, ModifierKeys.Control));
                CommandBindings.Add(new CommandBinding(spellSearch, miSearchSpells_Click));
            }
            catch (Exception Err) { }
        }

        private void CloseTab(object sender, ExecutedRoutedEventArgs e)
        {
            //handler code goes here.
            TabItem ti = tabGroup.SelectedItem as TabItem;
            if (ti != null && ti.Name != "tabSearch")
            {
                tabGroup.Items.Remove(ti);
            }
        }

        private void miSearchSpells_Click(object sender, RoutedEventArgs e)
        {
            var spellSearch = new DialogSpells();
            spellSearch.Owner = this;
            spellSearch.ShowDialog();
        }
    }
}
