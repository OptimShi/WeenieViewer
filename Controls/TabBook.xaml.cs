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
    /// Interaction logic for TabBook.xaml
    /// </summary>
    public partial class TabBook : TabItem
    {
        public TabBook(Dictionary<int, BookPageData> Pages)
        {
            InitializeComponent();

            myText.Text = "";
            var sortedPages = Pages.OrderBy(x => x.Value.PageId).ToList();
            foreach (var page in sortedPages)
            {
                myText.Text += page.Value.PageText;
                myText.Text += "\n________________________________\n\n";
            }

            Header = "Pages (" + Pages.Count.ToString() + ")";
        }
    }
}