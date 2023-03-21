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
    public partial class TabVendor : TabItem
    {
        public TabVendor(List<CreateListItem> Items, int filter = 0)
        {
            InitializeComponent();

            if (filter == 0)
                vendorItems.ItemsSource = Items;
            else
                vendorItems.ItemsSource = Items.Where(x => x.destinationType == filter).ToList();

            Header = "Sells " + vendorItems.Items.Count + " Items";
        }

        private void View_OnClick(object sender, RoutedEventArgs e)
        {
            var selectedItem = vendorItems.SelectedItem as CreateListItem;
            if (selectedItem != null)
            {
                var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
                main.ViewWeenie(selectedItem.wcid);
            }
        }

    }
}
