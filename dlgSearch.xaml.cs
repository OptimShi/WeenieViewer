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
using System.Windows.Shapes;

namespace WeenieViewer
{
    /// <summary>
    /// Interaction logic for dlgSearch.xaml
    /// </summary>
    public partial class dlgSearch : Window
    {
        public string SearchCriteria = "";
        
        public dlgSearch()
        {
            InitializeComponent();
        }

        private void OK_Click(object sender, RoutedEventArgs e)
        {
            SearchCriteria = txtSearch.Text;
            Close();
        }
    }
}
