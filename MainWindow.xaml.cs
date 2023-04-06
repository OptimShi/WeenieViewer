using System;
using System.Collections.Generic;
using System.Configuration;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml.Linq;
using WeenieViewer.Controls;
using WeenieViewer.Db;
using WeenieViewer.Db.weenie;
using WeenieViewer.Properties;

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
            btnWiki.Visibility = Visibility.Hidden;
            btnAcpedia.Visibility = Visibility.Hidden;

            // Init our SQLite Database
            db = new DbManager();
            var connected = db.Connect();
            if (connected)
            {
                lblVersion.Text = db.Version;

                txtSearch.TextChanged += new TextChangedEventHandler(txtSearch_TextChanged);
                txtSearch.Focus();

                SetupHotKeys();

#if DEBUG
                MenuItem newMenuItem = new MenuItem();
                newMenuItem.Header = "Debug";
                MainMenu.Items.Add(newMenuItem);

                //Add to a sub item
                MenuItem subMenuItem = new MenuItem();
                subMenuItem.Header = "Open All Weenies";
                subMenuItem.Click += new RoutedEventHandler(DEBUG_OpenAllTheWeenies);

                newMenuItem.Items.Add(subMenuItem);
#endif
            }
            else
            {
                PromptForDBConnection();
            }
        }

        private void PromptForDBConnection()
        {
            throw new NotImplementedException();
        }

        private void View_OnClick(object sender, RoutedEventArgs e)
        {
            if (lstSearchResults.HasItems && lstSearchResults.SelectedItem != null)
            {
                string selectedItem = lstSearchResults.SelectedValue.ToString();

                int wcidLength = selectedItem.LastIndexOf(')') - selectedItem.LastIndexOf('(') - 1;
                var selectedWCID = selectedItem.Substring(selectedItem.LastIndexOf('(') + 1, wcidLength);

                ViewWeenie(Int32.Parse(selectedWCID));
            }
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

                ViewWeenie(Int32.Parse(selectedWCID));
            }
        }

        public void ViewWeenie(int wcid)
        {
            // Does this tab already exist?
            var tabExists = tabGroup.Items.OfType<TabItem>().SingleOrDefault(n => n.Name.ToString() == "tab_" + wcid.ToString());
            if (tabExists != null)
            {
                // Bring the tab forward
                tabGroup.SelectedItem = tabExists;
            }
            else
            {
                Cursor = Cursors.Wait;
                try
                {
                    // Create our new tab.
                    //var newTab = new TabWeenie() {};
                    TabItem newWeenieTabItem = new TabItem
                    {
                        //Header = itemName,
                        Name = "tab_" + wcid.ToString()
                    };

                    TabWeenie weenieTabContent = new TabWeenie();
                    weenieTabContent.wcid = wcid;

                    var weenie = db.GetWeenie(wcid);
                    weenieTabContent.DisplayWeenie(weenie);

                    // You can get a "missing item" via a CreateList, possibly other ways
                    if (!weenie.Strings.ContainsKey(Enums.PropertyString.NAME_STRING))
                    {
                        newWeenieTabItem.Header = $"Missing Item ({wcid})";
                    }
                    else 
                    {
                        newWeenieTabItem.Header = weenie.Strings[Enums.PropertyString.NAME_STRING] + $" ({wcid})";
                        weenieTabContent.name = weenie.Strings[Enums.PropertyString.NAME_STRING];
                    }

                    newWeenieTabItem.Content = weenieTabContent;


                    tabGroup.Items.Add(newWeenieTabItem);
                    tabGroup.SelectedItem = newWeenieTabItem;
                }
                finally
                {
                    Cursor = Cursors.Arrow;
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
                btnWiki.Visibility = Visibility.Collapsed;
                btnAcpedia.Visibility = Visibility.Collapsed;
                lblResultsCount.Visibility = Visibility.Visible;
            }
            else
            {
                btnCloseTab.Visibility = Visibility.Visible;
                if (WeenieViewerSettings.Default.useWikia)
                {
                    btnWiki.Visibility = Visibility.Visible;
                    btnAcpedia.Visibility = Visibility.Collapsed;
                }
                else
                {
                    btnWiki.Visibility = Visibility.Collapsed;
                    btnAcpedia.Visibility = Visibility.Visible;
                }
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
            catch { }
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

        private void btnWiki_Click(object sender, RoutedEventArgs e)
        {
            TabItem ti = tabGroup.SelectedItem as TabItem;
            TabWeenie content = ti.Content as TabWeenie;

            string name = content.name;
            string url = "https://asheron.fandom.com/wiki/Special:Search?query=" + Uri.EscapeDataString(name);
            //string url = "http://www.acpedia.org/?search=" + Uri.EscapeDataString(name);
            Process.Start(new ProcessStartInfo("cmd", $"/c start {url}") { CreateNoWindow = true });
        }

        private void btnAcpedia_Click(object sender, RoutedEventArgs e)
        {
            TabItem ti = tabGroup.SelectedItem as TabItem;
            TabWeenie content = ti.Content as TabWeenie;

            string name = content.name;
            string url = "http://www.acpedia.org/?search=" + Uri.EscapeDataString(name);
            Process.Start(new ProcessStartInfo("cmd", $"/c start {url}") { CreateNoWindow = true });
        }

        private void miAbout_Click(object sender, RoutedEventArgs e)
        {
            var about = new DialogAbout();
            about.Owner = this;
            about.ShowDialog();
        }

        private void miOptions_Click(object sender, RoutedEventArgs e)
        {
            var options = new DialogOptions();
            options.Owner = this;
            var optionsResult = options.ShowDialog();
            if (optionsResult != null && (bool)optionsResult)
            {
                // Trigger the tab change to switch the Wiki button, if neccessary
                tabGroup_SelectionChanged(null, null);

                // Check if we need to swap database
                bool isSQLite = WeenieViewerSettings.Default.DBType == "SQLite";
                if (isSQLite != db.db.usingSQLite)
                {
                    db = new DbManager();
                    db.Connect();
                    lblVersion.Text = db.Version;
                }

            }

        }

        private void DEBUG_OpenAllTheWeenies(object sender, RoutedEventArgs e)
        {
            MessageBoxResult messageBoxResult = MessageBox.Show("Are you sure?\n\nThis is a time consuming process you cannot quit.", "Open All Weenies", MessageBoxButton.YesNo);
            if (messageBoxResult == MessageBoxResult.Yes)
            {
                foreach (var w in db.WeenieNames)
                {
                    var weenie = db.GetWeenie(w.Key);
                    weenie = null;
                    /*
                    ViewWeenie(w.Key);
                    TabItem ti = tabGroup.SelectedItem as TabItem;
                    tabGroup.Items.Remove(ti);
                    */
                }
            }
        }
    }
}
