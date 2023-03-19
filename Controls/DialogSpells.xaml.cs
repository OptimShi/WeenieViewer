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
    /// <summary>
    /// Interaction logic for dialogSpells.xaml
    /// </summary>
    public partial class DialogSpells : Window
    {
        public DialogSpells()
        {
            InitializeComponent();

            txtSpellName.TextChanged += new TextChangedEventHandler(txtSearch_TextChanged);
            txtSpellName.Focus();
        }

        private void txtSearch_TextChanged(object sender, TextChangedEventArgs e)
        {
            SearchSpells(txtSpellName.Text.Trim());
        }

        public class SpellItem
        {
            public int spellId { get; set; }
            public string name { get; set; }
        }

        private void SearchSpells(string criteria)
        {
            if (criteria != "")
            {
                var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
                dgSpellResults.Items.Clear();

                var isNumeric = int.TryParse(criteria, out _);
                if (isNumeric)
                {
                    foreach(var s in main.db.SpellNames)
                    {
                        var key = s.Key.ToString();
                        if (key.Contains(criteria)){
                            SpellItem item = new SpellItem();
                            item.spellId = s.Key;
                            item.name = s.Value.ToString();
                            dgSpellResults.Items.Add(item);

                        };
                    }
                }
                else
                {
                    criteria = criteria.ToLower();
                    var results = main.db.SpellNames.Where(x => x.Value.ToLower().Contains(criteria));
                    foreach(var s in results)
                    {
                        SpellItem item = new SpellItem();
                        item.spellId = s.Key;
                        item.name = s.Value.ToString();
                        dgSpellResults.Items.Add(item);

                    }
                }
            }

        }

    }
}
