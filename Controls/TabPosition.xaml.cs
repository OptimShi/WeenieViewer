using System;
using System.Collections;
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
    /// Interaction logic for TabPosition.xaml
    /// </summary>
    public partial class TabPosition : TabItem
    {
        public TabPosition(List<Position> Positions)
        {
            InitializeComponent();

            myText.Text = "Note that some locations may be in dungeons.\n\n";

            var sortedPosition = Positions.OrderBy(x => x.positionType).ToList();

            foreach (Position p in sortedPosition)
            {
                switch (p.positionType)
                {
                    case -1: myText.Text += "Spawn Location:\n" + GetLocString(p, true) + "\n\n"; break; // Landblock Instance ... custom position type
                    case 2: myText.Text += "Portal Destination:\n" + GetLocString(p) + "\n\n"; break;
                    case 4: myText.Text += "Life Stone Position:\n" + GetLocString(p) + "\n\n"; break;
                    case 12: myText.Text += "Portal Summon Destination:\n" + GetLocString(p) + "\n\n"; break;
                    default: myText.Text += "Unhandled Position Type - " + p.positionType + "\n\n"; break;
                }
            }

            if (Positions.Count > 1)
                Header = $"Locations ({Positions.Count})";
            else
                Header = "Location (1)";
        }

        private string GetLocString(Position p, bool includePOI = false)
        {
            string theText = $"0x{p.objCellId:X8} {p.x} {p.y} {p.z} {p.qw} {p.qx} {p.qy} {p.qz}\n";
            var coords = PositionExtensions.GetMapCoordStr(p);
            if ((p.objCellId & 0x100) != 0) coords += " (Indoors or in a Dungeon)";

            theText += coords;
            if (includePOI)
            {
                string loc = GetNearestPOI(p);
                theText += "\nNearest Point of Interest is " + loc;
            }
            return theText;
        }

        private string GetNearestPOI(Position p)
        {
            var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
            float distance = -1f;
            string poi_name = "";
            foreach(var poi in main.db.PointsOfInterest)
            {
                var thisDistance = PositionExtensions.Distance2D(poi.Value, p);
                if (distance == -1 | thisDistance < distance)
                {
                    distance = thisDistance;
                    poi_name = poi.Key;
                }
            }
            return poi_name;
        }
    }
}
