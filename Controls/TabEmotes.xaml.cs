using System;
using System.Collections.Generic;
using System.IO;
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
using WeenieViewer.SQLWriter;

namespace WeenieViewer.Controls
{
    /// <summary>
    /// Interaction logic for TabEmotes.xaml
    /// </summary>
    public partial class TabEmotes : TabItem
    {
        public TabEmotes(List<Emote> Emotes)
        {
            InitializeComponent();

            WeenieSQLWriter writer = new WeenieSQLWriter();
            var main = Window.GetWindow(App.Current.MainWindow) as MainWindow;
            writer.WeenieNames = main.db.WeenieNames;
            using (var stream = new MemoryStream())
            {
                using (var sw = new StreamWriter(stream))
                {
                    writer.CreateSQLINSERTStatement(Emotes, sw);
                }

                byte[] buff = stream.ToArray();
                string sql = Encoding.UTF8.GetString(buff, 0, buff.Length);
                //myText.Text = sql;
                //EmoteScriptLib.C
                //EmoteScriptLib.Converter.sql2es(sql);
                string[] lines = sql.Split(Environment.NewLine);

                var es = EmoteScriptLib.Converter.sql2es(lines);

                myText.Text = "";
                foreach (var line in es )
                {
                    myText.Text += line + "\n";
                }

            }
            Header = "Emotes (" + Emotes.Count.ToString() + ")";
        }
    }
}
