using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using WeenieViewer.Db;

namespace WeenieViewer.Appraisal
{
    partial class ItemExamine
    {

        private string GetSpellName(int spellId)
        {
            var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
            var spell = main.db.GetSpellName(spellId);
            if (spell != null)
                return spell;
            return "Unknown_or_Missing_Spell_Name";
        }

        private string GetSpellDescription(int spellId)
        {
            return "SPELL_DESCRIPTION_TBD";
        }

    }
}
