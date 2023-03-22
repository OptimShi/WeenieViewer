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
using WeenieViewer.Enums;

namespace WeenieViewer.Controls
{
    /// <summary>
    /// Interaction logic for TabEquipment.xaml
    /// </summary>
    public partial class TabEquipment : TabItem
    {
        public TabEquipment(List<CreateListItem> Items, int filter = 0)
        {
            InitializeComponent();

            List<CreateListItem> filteredItems;
            if(filter == 0)
                filteredItems = Items;
            else
                filteredItems = Items.Where(x => (x.destinationType & filter) > 0).ToList();

            foreach(var filteredItem in filteredItems)
            {
                var myItem = new equippedItem();
                myItem.name = filteredItem.name;
                myItem.wcid = filteredItem.wcid;
                myItem.shade = filteredItem.shade; 
                myItem.stackSize = filteredItem.stackSize;
                if (filteredItem.palette < 1 || filteredItem.palette > 93)
                    myItem.pal = "";
                else
                    myItem.pal = ((PaletteTemplate)filteredItem.palette).ToString() + $" ({filteredItem.palette})";

                equippedItems.Items.Add(myItem);
            }

            if (equippedItems.Items.Count > 1)
                Header += "s";

            Header += " (" + equippedItems.Items.Count.ToString() + ")";
        }

        private class equippedItem: CreateListItem
        {
            public string pal { get; set;  }
        }

        private void View_OnClick(object sender, RoutedEventArgs e)
        {
            var selectedItem = equippedItems.SelectedItem as equippedItem;
            if(selectedItem != null)
            {
                var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
                main.ViewWeenie(selectedItem.wcid);
            }
        }
    }
}
