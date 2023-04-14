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
using static WeenieViewer.TabWeenie;

namespace WeenieViewer.Controls
{
    public class MissingWeenie
    {
        public int sourceWCID { get; set; }
        public string sourceName { get; set; }
        public int wcid { get; set; }
        public string context { get; set; }
    }


    /// <summary>
    /// Interaction logic for TabMissingWeenies.xaml
    /// </summary>
    public partial class TabMissingWeenies : TabItem
    {
        public TabMissingWeenies(List<string> missing)
        {
            InitializeComponent();

            var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;

            foreach (var m in missing)
            {
                var pieces = m.Split('@');

                MissingWeenie item = new MissingWeenie();
                item.sourceWCID = Convert.ToInt32(pieces[0]);
                item.sourceName = main.db.WeenieNames[item.sourceWCID]; 
                item.wcid = Convert.ToInt32(pieces[1]);
                item.context = pieces[2];

                dgMissingItems.Items.Add(item);
            }

        }
    }
}
