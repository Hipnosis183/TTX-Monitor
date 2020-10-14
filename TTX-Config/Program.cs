using System;
using System.Windows.Forms;

namespace TTXMonitor
{
    static class Program
    {
        public static TTXConfigForm Launcher;

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(Launcher = new TTXConfigForm());
        }
    }
}
