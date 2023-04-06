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
using WeenieViewer.Controls;
using WeenieViewer.Db;
using WeenieViewer.Enums;

namespace WeenieViewer
{
    /// <summary>
    /// Interaction logic for TabWeenie.xaml
    /// </summary>
    public partial class TabWeenie : UserControl
    {
        private dbWeenie _Weenie;
        public string name;
        public int wcid;

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
            _Weenie = Weenie;
            //tabItem.Visibility = Visibility.Collapsed;
            tabEmotes.Visibility = Visibility.Collapsed;
            
            FlowDocument myFlowDoc = new FlowDocument();

            ItemExamine appraisal = new ItemExamine(Weenie);
            if (Weenie.IsCreature())
            {
                tabItem.Header = "Stats";

                string info = appraisal.GetCreatureInfo();

                //var ratings = appraisal.GetRatings();
                Paragraph myParagraph = new Paragraph();
                // Name, Level, Heritage, Title, etc
                myParagraph.Inlines.Add(info);
                myFlowDoc.Blocks.Add(myParagraph);

                // Stats
                Table myTable = new Table();

                TableColumn attNameColumn = new TableColumn();
                TableColumn attValColumn = new TableColumn();
                attNameColumn.Width = new GridLength(150);
                attValColumn.Width = new GridLength(75);
                myTable.Columns.Add(attNameColumn);
                myTable.Columns.Add(attValColumn);

                var attRowGroup = new TableRowGroup();
                myTable.RowGroups.Add(attRowGroup);

                foreach (var k in Weenie.Attributes.OrderBy(x => x.Key))
                {
                    string attName;
                    switch (k.Key)
                    {
                        case 1: attName = "Strength"; break;
                        case 2: attName = "Endurance"; break;
                        case 3: attName = "Quickness"; break;
                        case 4: attName = "Coordination"; break;
                        case 5: attName = "Focus"; break;
                        case 6: attName = "Self"; break;
                        default: continue;
                    }
                    var currentRow = new TableRow();
                    currentRow.Cells.Add(new TableCell(new Paragraph(new Run(attName))));
                    var value = new Paragraph(new Run(k.Value.init_level.ToString()));
                    value.TextAlignment = TextAlignment.Right;
                    currentRow.Cells.Add(new TableCell(value));

                    if(attRowGroup.Rows.Count %2 == 1)
                        currentRow.Background = Brushes.LightGray;

                    attRowGroup.Rows.Add(currentRow);
                }

                var att2ndRowGroup = new TableRowGroup();
                myTable.RowGroups.Add(att2ndRowGroup);
                foreach (var k in Weenie.Attributes2nd.OrderBy(x => x.Key))
                {
                    string attName;
                    switch (k.Key)
                    {
                        case 1: attName = "Health"; break;
                        case 2: attName = "Endurance"; break;
                        case 3: attName = "Stamina"; break;
                        case 4: attName = "Quickness"; break;
                        case 5: attName = "Mana"; break;
                        case 6: attName = "Self"; break;
                        default: continue;
                    }
                    var currentRow = new TableRow();
                    currentRow.Cells.Add(new TableCell(new Paragraph(new Run(attName))));
                    var value = new Paragraph(new Run(k.Value.current_level.ToString()));
                    value.TextAlignment = TextAlignment.Right;
                    currentRow.Cells.Add(new TableCell(value));

                    if (att2ndRowGroup.Rows.Count % 2 == 1)
                        currentRow.Background = Brushes.LightGray;

                    att2ndRowGroup.Rows.Add(currentRow);
                }

                // SKILLS
                var specSkills = new Dictionary<int, Db.weenie.Skill>();
                foreach (var x in Weenie.Skills.Select(r => r).Where(x => x.Value.sac == 3)) 
                {
                    specSkills.Add(x.Key, x.Value);
                }
                if (specSkills.Count > 0)
                {
                    Color purple = Color.FromRgb(50, 29, 92);
                    Color purpleBlack = Color.FromRgb(24, 6, 67);
                    var rowGroup = AddSkillsToTable(specSkills, "Specialized Skills", purple);
                    myTable.RowGroups.Add(rowGroup);
                }

                var trainedSkills = new Dictionary<int, Db.weenie.Skill>();
                foreach (var x in Weenie.Skills.Select(r => r).Where(x => x.Value.sac == 2))
                {
                    trainedSkills.Add(x.Key, x.Value);
                }
                if (trainedSkills.Count > 0)
                {
                    Color teal = Color.FromRgb(51, 83, 82);
                    Color tealDark = Color.FromRgb(24, 6, 67);
                    var rowGroup = AddSkillsToTable(trainedSkills, "Trained Skills", teal);
                    myTable.RowGroups.Add(rowGroup);
                }

                var untrainedSkills = new Dictionary<int, Db.weenie.Skill>();
                foreach (var x in Weenie.Skills.Select(r => r).Where(x => x.Value.sac == 1))
                {
                    untrainedSkills.Add(x.Key, x.Value);
                }
                if (untrainedSkills.Count > 0)
                {
                    Color yellow = Color.FromRgb(88, 67, 31);
                    var rowGroup = AddSkillsToTable(untrainedSkills, "Untrained Skills", yellow);
                    myTable.RowGroups.Add(rowGroup);
                }

                var unusableSkills = new Dictionary<int, Db.weenie.Skill>();
                foreach (var x in Weenie.Skills.Select(r => r).Where(x => x.Value.sac == 0))
                {
                    unusableSkills.Add(x.Key, x.Value);
                }
                if (unusableSkills.Count > 0)
                {
                    Color grey = Color.FromRgb(83, 83, 83);
                    var rowGroup = AddSkillsToTable(unusableSkills, "Unusable Skills", grey);
                    myTable.RowGroups.Add(rowGroup);
                }

                myFlowDoc.Blocks.Add(myTable);

            }
            else
            {
                Paragraph myParagraph = new Paragraph();
                string info = "";
                string name = "";
                if (Weenie.Strings.ContainsKey(PropertyString.NAME_STRING))
                    name = Weenie.Strings[PropertyString.NAME_STRING];
                info = "Name: " + name + "\n";
                info += $"WeenieType: {(WeenieType)Weenie.WeenieType}\nWeenieClass: {Weenie.WeenieClass}\n\n";
                myParagraph.Inlines.Add(info + appraisal.Text);
                myFlowDoc.Blocks.Add(myParagraph);
            }

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

            var vendorItems = Weenie.CreateList.Where(x => x.destinationType == 4).ToList();
            if(vendorItems.Count > 0)
            {
                var vendorTab = new TabVendor(Weenie.CreateList, 4);
                WeenieTabControl.Items.Add(vendorTab);
            }

            var soldItems = Weenie.SoldBy.Where(x => x.destinationType == 4).ToList();
            if (soldItems.Count > 0)
            {
                var soldTab = new TabSoldBy(Weenie.SoldBy, 4);
                WeenieTabControl.Items.Add(soldTab);
            }

            var equippedItems = Weenie.CreateList.Where(x => (x.destinationType & 2) > 0).ToList();
            if (equippedItems.Count > 0)
            {
                var equippedTab = new TabEquipment(Weenie.CreateList, 2);
                WeenieTabControl.Items.Add(equippedTab);
            }

            var trophies = Weenie.CreateList.Where(x => (x.destinationType & 8) > 0).ToList();
            if (trophies.Count > 0)
            {
                var trophyTab = new TabTrophies(Weenie.CreateList);
                WeenieTabControl.Items.Add(trophyTab);
            }

            var housing = Weenie.CreateList.Where(x => ((x.destinationType & 16) != 0) || (x.destinationType & 32) != 0).ToList();
            if (housing.Count > 0)
            {
                var housingTab = new TabHousing(Weenie.CreateList);
                WeenieTabControl.Items.Add(housingTab);
            }

            //tabProps.IsSelected = true;
            tabItem.IsSelected = true;

            if(Weenie.Positions.Count > 0)
            {
                var positionTab = new TabPosition(Weenie.Positions);
                WeenieTabControl.Items.Add(positionTab);
            }

            if (Weenie.BookData.Count > 0)
            {
                var pagesTab = new TabBook(Weenie.BookData);
                WeenieTabControl.Items.Add(pagesTab);
            }

            if (Weenie.Emotes.Count > 0)
            {
                var emotesTab = new TabEmotes(Weenie.Emotes);
                WeenieTabControl.Items.Add(emotesTab);
            }
        }

        private TableRowGroup AddSkillsToTable(Dictionary<int, WeenieViewer.Db.weenie.Skill> weenieSkills, string title, Color bgColor)
        {
            Dictionary<string, int> skills = new Dictionary<string, int>();
            foreach (var k in weenieSkills)
            {
                var skillName = SkillExtensions.GetSkillName((Skill)k.Key);
                skills.Add(skillName, k.Value.CurrentValue);
            }

            var skillRowGroup = new TableRowGroup();
            var titleRow = new TableRow();
            var labelCell = new TableCell(new Paragraph(new Run(title) { Foreground = Brushes.White }));
            labelCell.ColumnSpan = 2;
            titleRow.Cells.Add(labelCell);
            Color purple = Color.FromRgb(50, 29, 92);
            Color purpleBlack = Color.FromRgb(24, 6, 67);
            titleRow.Background = new SolidColorBrush(bgColor);
            skillRowGroup.Rows.Add(titleRow);

            foreach (var k in skills.OrderBy(x => x.Key))
            {
                var currentRow = new TableRow();
                currentRow.Cells.Add(new TableCell(new Paragraph(new Run(k.Key))));
                var value = new Paragraph(new Run(k.Value.ToString()));
                value.TextAlignment = TextAlignment.Right;
                currentRow.Cells.Add(new TableCell(value));

                if (skillRowGroup.Rows.Count % 2 == 0)
                    currentRow.Background = Brushes.LightGray;

                skillRowGroup.Rows.Add(currentRow);

            }
               
            return skillRowGroup;
        }
    }
}
