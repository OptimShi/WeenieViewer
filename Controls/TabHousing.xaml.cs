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
    /// Interaction logic for TabHousing.xaml
    /// </summary>
    public partial class TabHousing : TabItem
    {
        public TabHousing(List<CreateListItem> Items)
        {
            InitializeComponent();

            // Look for Purchase price

            List<CreateListItem> purchaseItems = Items.Where(x => (x.destinationType & 16) > 0).ToList();
            List<CreateListItem> rentItems = Items.Where(x => (x.destinationType & 32) > 0).ToList();

            myText.Text = "";
            if (purchaseItems.Count > 0)
            {
                myText.Text += "Purchase Price:\n";
                foreach (var p in purchaseItems)
                {
                    myText.Text += $"{p.name} ({p.wcid})";
                    if (p.stackSize > 0)
                        myText.Text += $" x {p.stackSize:N0}";
                    myText.Text += "\n";
                }

                myText.Text += "\n\n";
            }

            if (rentItems.Count > 0)
            {
                myText.Text += "Maintenance Cost:\n";
                foreach (var p in rentItems)
                {
                    myText.Text += $"{p.name} ({p.wcid})";
                    if (p.stackSize > 0)
                        myText.Text += $" x {p.stackSize:N0}";
                    myText.Text += "\n";
                }
            }

        }

    }
}
