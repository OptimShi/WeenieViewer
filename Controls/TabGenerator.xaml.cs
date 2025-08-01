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
    /// Interaction logic for TabGenerator.xaml
    /// </summary>
    public partial class TabGenerator : TabItem
    {
        public TabGenerator(List<Generator> Generators, int wcid)
        {
            InitializeComponent();

            genText.Text = "";

            foreach(var gen in Generators)
            {
                if (gen.weenieClassId == wcid)
                    genText.Text += gen.ToGeneratedByString() + Environment.NewLine + Environment.NewLine;

                if (gen.objectId == wcid)
                    genText.Text += gen.ToGeneratesString() + Environment.NewLine + Environment.NewLine;
            }

        }

    }
}
