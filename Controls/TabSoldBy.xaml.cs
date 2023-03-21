using System;
using System.Collections.Generic;
using System.Linq;
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
using WeenieViewer.Db.weenie;

namespace WeenieViewer.Controls
{
    /// <summary>
    /// Interaction logic for TabVendor.xaml
    /// </summary>
    public partial class TabSoldBy : TabItem
    {
        public TabSoldBy(List<CreateListItem> Items, int filter = 0)
        {
            InitializeComponent();

            if(filter == 0)
                vendors.ItemsSource = Items;
            else
                vendors.ItemsSource = Items.Where(x => x.destinationType == filter).ToList();
            Header = "Sold by " + vendors.Items.Count + " Shops";
        }

        private void View_OnClick(object sender, RoutedEventArgs e)
        {
            var selectedItem = vendors.SelectedItem as CreateListItem;
            if(selectedItem != null)
            {
                var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
                main.ViewWeenie(selectedItem.objectId);
            }
        }
    }
}
