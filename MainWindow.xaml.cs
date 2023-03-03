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
using WeenieViewer.Db;

namespace WeenieViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DbManager db;

        public MainWindow()
        {
            InitializeComponent();

            // Init our SQLite Database
            db = new DbManager();
            db.Connect();
            lblVersion.Text = db.Version;
        }

        private void miExit_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        private void miSearchWeenies_Click(object sender, RoutedEventArgs e)
        {
            db.SearchForWeenie("asher");
        }
    }
}
