using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
    /// Interaction logic for TabTrophies.xaml
    /// </summary>
    public partial class TabTrophies : TabItem
    {
        public TabTrophies(List<CreateListItem> Items)
        {
            InitializeComponent();

            // go through the trophy list...
            var trophyList = Items.Where(x => (x.destinationType & 8) > 0).ToList();

            for(var i = 0; i< trophyList.Count; i++)
            {
                var item = new trophyDataItem();
                item.wcid = trophyList[i].wcid;
                if(item.wcid != 0)
                {
                    item.probability = (int)Math.Round(trophyList[i].shade * 100);
                    item.name = trophyList[i].name;
                    trophies.Items.Add(item);
                }
            }

        }

        private class trophyDataItem
        {
            public int wcid { get; set; }
            public string name { get; set; }
            public int probability { get; set; }
        }

        private void View_OnClick(object sender, RoutedEventArgs e)
        {
            var selectedItem = trophies.SelectedItem as CreateListItem;
            if(selectedItem != null)
            {
                var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
                main.ViewWeenie(selectedItem.wcid);
            }
        }
    }
}
