using System;
using System.Collections.Generic;
using System.Globalization;
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
using WeenieViewer.Appraisal;
using WeenieViewer.Db;

namespace WeenieViewer
{
    /// <summary>
    /// Interaction logic for TabWeenie.xaml
    /// </summary>
    public partial class TabWeenie : UserControl
    {
        public TabWeenie()
        {
            InitializeComponent();
        }

        public class DataItem
        {
            public string propertyType { get; set; }
            public string propertyValue { get; set; }
        }

        public void DisplayWeenie(dbWeenie Weenie)
        {
            if (Weenie == null) { return; }

            //tabItem.Visibility = Visibility.Collapsed;
            tabEmotes.Visibility = Visibility.Collapsed;
            
            ItemExamine appraisal = new ItemExamine(Weenie);
            FlowDocument myFlowDoc = new FlowDocument();
            Paragraph myParagraph = new Paragraph();
            myParagraph.Inlines.Add(appraisal.Text);
            myFlowDoc.Blocks.Add(myParagraph);
            txtInfo.Document = myFlowDoc;
            txtInfo.IsReadOnly = true;

            dgProps.Items.Clear();
            foreach (var e in Weenie.Bools)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = e.Value.ToString();
                dgProps.Items.Add(item);
            }
            foreach (var e in Weenie.DIDs)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = "0x" + e.Value.ToString("X8");
                dgProps.Items.Add(item);
            }
            foreach (var e in Weenie.Floats)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = e.Value.ToString();
                dgProps.Items.Add(item);
            }
            foreach (var e in Weenie.IIDs)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = "0x" + e.Value.ToString("X8");
                dgProps.Items.Add(item);
            }
            foreach (var e in Weenie.Ints)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = e.Value.ToString();
                dgProps.Items.Add(item);
            }
            foreach (var e in Weenie.Int64s)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = e.Value.ToString();
                dgProps.Items.Add(item);
            }
            foreach (var e in Weenie.Strings)
            {
                DataItem item = new DataItem();
                item.propertyType = e.Key.ToString() + " (" + (int)e.Key + ")";
                item.propertyValue = e.Value.ToString();
                dgProps.Items.Add(item);
            }

            //tabProps.IsSelected = true;
            tabItem.IsSelected = true;
        }
    }
}
