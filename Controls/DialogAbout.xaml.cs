using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
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
using System.Xml.Linq;

namespace WeenieViewer.Controls
{
    /// <summary>
    /// Interaction logic for DialogAbout.xaml
    /// </summary>
    public partial class DialogAbout : Window
    {
        public DialogAbout()
        {
            InitializeComponent();
            lblVersion.Content= "Version: " + Application.ResourceAssembly.GetName().Version.ToString();
        }

        private void btnOK_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Hyperlink_Click(object sender, RoutedEventArgs e)
        {
            string url = gitLink.NavigateUri.ToString();
            Process.Start(new ProcessStartInfo("cmd", $"/c start {url}") { CreateNoWindow = true });
        }
    }
}
