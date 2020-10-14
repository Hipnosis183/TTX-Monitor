using TTXMonitor.Classes;
using System;
using System.Windows.Forms;
using System.Diagnostics;

namespace TTXMonitor
{
    public partial class TTXConfigForm : Form
    {
        public TTXConfigForm()
        {
            InitializeComponent();

            LinkLabel_Romhack.TabStop = false;
            LinkLabel_Hipnosis.TabStop = false;
            Label_Middle.TabStop = false;

            TTXConfig.CreateJoystickValues();
        }

        private void ConfigForm_Load(object sender, EventArgs e)
        {
            TTXConfig.SetFeatureToAllControls(this.Controls);

            TTXConfig.InitialSetup();
            LoadSettings();
        }

        private void LoadSettings()
        {
            TTXConfig.LoadController(ComboBox_Device);

            LoadInputs();
            LoadMisc();
        }

        private void LoadInputs()
        {
            LoadInputs_P0();
            LoadInputs_P1();
            LoadInputs_P2();
            LoadInputs_M();
        }

        private void LoadInputs_P0()
        {
            TTXConfig.LoadInput(Button_P0_Test, 0x68);
            TTXConfig.LoadInput(Button_P0_Exit, 0x6C);
        }

        private void LoadInputs_P1()
        {
            TTXConfig.LoadInput(Button_P1_Up, 0x0C);
            TTXConfig.LoadInput(Button_P1_Down, 0x10);
            TTXConfig.LoadInput(Button_P1_Left, 0x14);
            TTXConfig.LoadInput(Button_P1_Right, 0x18);
            TTXConfig.LoadInput(Button_P1_Start, 0x00);
            TTXConfig.LoadInput(Button_P1_Service, 0x08);
            TTXConfig.LoadInput(Button_P1_ButtonA, 0x1C);
            TTXConfig.LoadInput(Button_P1_ButtonB, 0x20);
            TTXConfig.LoadInput(Button_P1_ButtonC, 0x24);
            TTXConfig.LoadInput(Button_P1_ButtonD, 0x28);
            TTXConfig.LoadInput(Button_P1_ButtonE, 0x2C);
            TTXConfig.LoadInput(Button_P1_ButtonF, 0x30);
        }

        private void LoadInputs_P2()
        {
            TTXConfig.LoadInput(Button_P2_Up, 0x40);
            TTXConfig.LoadInput(Button_P2_Down, 0x44);
            TTXConfig.LoadInput(Button_P2_Left, 0x48);
            TTXConfig.LoadInput(Button_P2_Right, 0x4C);
            TTXConfig.LoadInput(Button_P2_Start, 0x34);
            TTXConfig.LoadInput(Button_P2_Service, 0x3C);
            TTXConfig.LoadInput(Button_P2_ButtonA, 0x50);
            TTXConfig.LoadInput(Button_P2_ButtonB, 0x54);
            TTXConfig.LoadInput(Button_P2_ButtonC, 0x58);
            TTXConfig.LoadInput(Button_P2_ButtonD, 0x5C);
            TTXConfig.LoadInput(Button_P2_ButtonE, 0x60);
            TTXConfig.LoadInput(Button_P2_ButtonF, 0x64);
        }

        private void LoadInputs_M()
        {
            TTXConfig.LoadInput(Button_M_Start, 0x7C);
            TTXConfig.LoadInput(Button_M_Service, 0x78);
            TTXConfig.LoadInput(Button_M_Kong, 0xB8);
            TTXConfig.LoadInput(Button_M_Pon, 0xBC);
            TTXConfig.LoadInput(Button_M_Chi, 0xC0);
            TTXConfig.LoadInput(Button_M_Reach, 0xC4);
            TTXConfig.LoadInput(Button_M_Ron, 0xC8);
            TTXConfig.LoadInput(Button_M_ButtonA, 0x80);
            TTXConfig.LoadInput(Button_M_ButtonB, 0x84);
            TTXConfig.LoadInput(Button_M_ButtonC, 0x88);
            TTXConfig.LoadInput(Button_M_ButtonD, 0x8C);
            TTXConfig.LoadInput(Button_M_ButtonE, 0x90);
            TTXConfig.LoadInput(Button_M_ButtonF, 0x94);
            TTXConfig.LoadInput(Button_M_ButtonG, 0x98);
            TTXConfig.LoadInput(Button_M_ButtonH, 0x9C);
            TTXConfig.LoadInput(Button_M_ButtonI, 0xA0);
            TTXConfig.LoadInput(Button_M_ButtonJ, 0xA4);
            TTXConfig.LoadInput(Button_M_ButtonK, 0xA8);
            TTXConfig.LoadInput(Button_M_ButtonL, 0xAC);
            TTXConfig.LoadInput(Button_M_ButtonM, 0xB0);
            TTXConfig.LoadInput(Button_M_ButtonN, 0xB4);
        }
        private void LoadMisc()
        {
            TTXConfig.GetCheck(CheckBox_POV, 0x00);
            TTXConfig.GetCheck(CheckBox_SavePatch, 0x04);
            TTXConfig.GetCheck(CheckBox_Mahjong, 0x08);
            TTXConfig.GetCheck(CheckBox_Multithread, 0x0C);

            TTXConfig.SetConfig_CheckBox_Disable(CheckBox_Mahjong, CheckBox_Multithread);
        }

        private void ComboBox_Device_SelectedIndexChanged(object sender, EventArgs e)
        {
            TTXConfig.SetDevice(ComboBox_Device);
        }

        private void Button_Refresh_Click(object sender, EventArgs e)
        {
            TTXConfig.LoadController(ComboBox_Device);
        }

        private void Button_P1_Up_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_Up, 0x0C, e);
        }

        private void Button_P1_Down_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_Down, 0x10, e);
        }

        private void Button_P1_Left_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_Left, 0x14, e);
        }

        private void Button_P1_Right_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_Right, 0x18, e);
        }

        private void Button_P1_Start_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_Start, 0x00, e);
        }

        private void Button_P1_Service_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_Service, 0x08, e);
        }

        private void Button_P1_ButtonA_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_ButtonA, 0x1C, e);
        }

        private void Button_P1_ButtonB_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_ButtonB, 0x20, e);
        }

        private void Button_P1_ButtonC_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_ButtonC, 0x24, e);
        }

        private void Button_P1_ButtonD_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_ButtonD, 0x28, e);
        }

        private void Button_P1_ButtonE_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_ButtonE, 0x2C, e);
        }

        private void Button_P1_ButtonF_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P1_ButtonF, 0x30, e);
        }

        private void Button_P2_Up_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_Up, 0x40, e);
        }

        private void Button_P2_Down_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_Down, 0x44, e);
        }

        private void Button_P2_Left_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_Left, 0x48, e);
        }

        private void Button_P2_Right_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_Right, 0x4C, e);
        }

        private void Button_P2_Start_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_Start, 0x34, e);
        }

        private void Button_P2_Service_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_Service, 0x3C, e);
        }

        private void Button_P2_ButtonA_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_ButtonA, 0x50, e);
        }

        private void Button_P2_ButtonB_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_ButtonB, 0x54, e);
        }

        private void Button_P2_ButtonC_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_ButtonC, 0x58, e);
        }

        private void Button_P2_ButtonD_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_ButtonD, 0x5C, e);
        }

        private void Button_P2_ButtonE_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_ButtonE, 0x60, e);
        }

        private void Button_P2_ButtonF_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P2_ButtonF, 0x64, e);
        }

        private void Button_M_Start_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Start, 0x7C, e);
        }

        private void Button_M_Service_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Service, 0x78, e);
        }

        private void Button_M_Kong_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Kong, 0xB8, e);
        }

        private void Button_M_Pon_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Pon, 0xBC, e);
        }

        private void Button_M_Chi_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Chi, 0xC0, e);
        }

        private void Button_M_Reach_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Reach, 0xC4, e);
        }

        private void Button_M_Ron_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_Ron, 0xC8, e);
        }

        private void Button_M_ButtonA_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonA, 0x80, e);
        }

        private void Button_M_ButtonB_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonB, 0x84, e);
        }

        private void Button_M_ButtonC_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonC, 0x88, e);
        }

        private void Button_M_ButtonD_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonD, 0x8C, e);
        }

        private void Button_M_ButtonE_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonE, 0x90, e);
        }

        private void Button_M_ButtonF_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonF, 0x94, e);
        }

        private void Button_M_ButtonG_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonG, 0x98, e);
        }

        private void Button_M_ButtonH_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonH, 0x9C, e);
        }

        private void Button_M_ButtonI_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonI, 0xA0, e);
        }

        private void Button_M_ButtonJ_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonJ, 0xA4, e);
        }

        private void Button_M_ButtonK_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonK, 0xA8, e);
        }

        private void Button_M_ButtonL_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonL, 0xAC, e);
        }

        private void Button_M_ButtonM_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonM, 0xB0, e);
        }

        private void Button_M_ButtonN_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_M_ButtonN, 0xB4, e);
        }

        private void Button_P0_Test_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P0_Test, 0x68, e);
        }

        private void Button_P0_Exit_MouseDown(object sender, MouseEventArgs e)
        {
            TTXConfig.Button_Click(Button_P0_Exit, 0x6C, e);
        }

        private void CheckBox_POV_CheckedChanged(object sender, EventArgs e)
        {
            TTXConfig.SetConfig_CheckBox(CheckBox_POV, 0x00);
        }

        private void CheckBox_SavePatch_CheckedChanged(object sender, EventArgs e)
        {
            TTXConfig.SetConfig_CheckBox(CheckBox_SavePatch, 0x04);
        }

        private void CheckBox_Mahjong_CheckedChanged(object sender, EventArgs e)
        {
            TTXConfig.SetConfig_CheckBox(CheckBox_Mahjong, 0x08);
            TTXConfig.SetConfig_CheckBox_Disable(CheckBox_Mahjong, CheckBox_Multithread);
        }

        private void CheckBox_Multithread_CheckedChanged(object sender, EventArgs e)
        {
            TTXConfig.SetConfig_CheckBox(CheckBox_Multithread, 0x0C);
        }

        private void Button_P1_SetAll_Click(object sender, EventArgs e)
        {
            TTXConfig.SetInput(Button_P1_Up, 0x0C);
            TTXConfig.SetInput(Button_P1_Down, 0x10);
            TTXConfig.SetInput(Button_P1_Left, 0x14);
            TTXConfig.SetInput(Button_P1_Right, 0x18);
            TTXConfig.SetInput(Button_P1_Start, 0x00);
            TTXConfig.SetInput(Button_P1_Service, 0x08);
            TTXConfig.SetInput(Button_P1_ButtonA, 0x1C);
            TTXConfig.SetInput(Button_P1_ButtonB, 0x20);
            TTXConfig.SetInput(Button_P1_ButtonC, 0x24);
            TTXConfig.SetInput(Button_P1_ButtonD, 0x28);
            TTXConfig.SetInput(Button_P1_ButtonE, 0x2C);
            TTXConfig.SetInput(Button_P1_ButtonF, 0x30);

            TTXConfig.SetInput(Button_P0_Test, 0x68);
            TTXConfig.SetInput(Button_P0_Exit, 0x6C);
        }

        private void Button_P2_SetAll_Click(object sender, EventArgs e)
        {
            TTXConfig.SetInput(Button_P2_Up, 0x40);
            TTXConfig.SetInput(Button_P2_Down, 0x44);
            TTXConfig.SetInput(Button_P2_Left, 0x48);
            TTXConfig.SetInput(Button_P2_Right, 0x4C);
            TTXConfig.SetInput(Button_P2_Start, 0x34);
            TTXConfig.SetInput(Button_P2_Service, 0x3C);
            TTXConfig.SetInput(Button_P2_ButtonA, 0x50);
            TTXConfig.SetInput(Button_P2_ButtonB, 0x54);
            TTXConfig.SetInput(Button_P2_ButtonC, 0x58);
            TTXConfig.SetInput(Button_P2_ButtonD, 0x5C);
            TTXConfig.SetInput(Button_P2_ButtonE, 0x60);
            TTXConfig.SetInput(Button_P2_ButtonF, 0x64);
        }

        private void Button_M_SetAll_Click(object sender, EventArgs e)
        {
            TTXConfig.SetInput(Button_M_Start, 0x7C);
            TTXConfig.SetInput(Button_M_Service, 0x78);
            TTXConfig.SetInput(Button_M_Kong, 0xB8);
            TTXConfig.SetInput(Button_M_Pon, 0xBC);
            TTXConfig.SetInput(Button_M_Chi, 0xC0);
            TTXConfig.SetInput(Button_M_Reach, 0xC4);
            TTXConfig.SetInput(Button_M_Ron, 0xC8);
            TTXConfig.SetInput(Button_M_ButtonA, 0x80);
            TTXConfig.SetInput(Button_M_ButtonB, 0x84);
            TTXConfig.SetInput(Button_M_ButtonC, 0x88);
            TTXConfig.SetInput(Button_M_ButtonD, 0x8C);
            TTXConfig.SetInput(Button_M_ButtonE, 0x90);
            TTXConfig.SetInput(Button_M_ButtonF, 0x94);
            TTXConfig.SetInput(Button_M_ButtonG, 0x98);
            TTXConfig.SetInput(Button_M_ButtonH, 0x9C);
            TTXConfig.SetInput(Button_M_ButtonI, 0xA0);
            TTXConfig.SetInput(Button_M_ButtonJ, 0xA4);
            TTXConfig.SetInput(Button_M_ButtonK, 0xA8);
            TTXConfig.SetInput(Button_M_ButtonL, 0xAC);
            TTXConfig.SetInput(Button_M_ButtonM, 0xB0);
            TTXConfig.SetInput(Button_M_ButtonN, 0xB4);
        }

        private void Button_P1_ClearAll_Click(object sender, EventArgs e)
        {
            TTXConfig.ClearInput(Button_P1_Up, 0x0C);
            TTXConfig.ClearInput(Button_P1_Down, 0x10);
            TTXConfig.ClearInput(Button_P1_Left, 0x14);
            TTXConfig.ClearInput(Button_P1_Right, 0x18);
            TTXConfig.ClearInput(Button_P1_Start, 0x00);
            TTXConfig.ClearInput(Button_P1_Service, 0x08);
            TTXConfig.ClearInput(Button_P1_ButtonA, 0x1C);
            TTXConfig.ClearInput(Button_P1_ButtonB, 0x20);
            TTXConfig.ClearInput(Button_P1_ButtonC, 0x24);
            TTXConfig.ClearInput(Button_P1_ButtonD, 0x28);
            TTXConfig.ClearInput(Button_P1_ButtonE, 0x2C);
            TTXConfig.ClearInput(Button_P1_ButtonF, 0x30);

            TTXConfig.ClearInput(Button_P0_Test, 0x68);
            TTXConfig.ClearInput(Button_P0_Exit, 0x6C);
        }

        private void Button_P2_ClearAll_Click(object sender, EventArgs e)
        {
            TTXConfig.ClearInput(Button_P2_Up, 0x40);
            TTXConfig.ClearInput(Button_P2_Down, 0x44);
            TTXConfig.ClearInput(Button_P2_Left, 0x48);
            TTXConfig.ClearInput(Button_P2_Right, 0x4C);
            TTXConfig.ClearInput(Button_P2_Start, 0x34);
            TTXConfig.ClearInput(Button_P2_Service, 0x3C);
            TTXConfig.ClearInput(Button_P2_ButtonA, 0x50);
            TTXConfig.ClearInput(Button_P2_ButtonB, 0x54);
            TTXConfig.ClearInput(Button_P2_ButtonC, 0x58);
            TTXConfig.ClearInput(Button_P2_ButtonD, 0x5C);
            TTXConfig.ClearInput(Button_P2_ButtonE, 0x60);
            TTXConfig.ClearInput(Button_P2_ButtonF, 0x64);

            TTXConfig.ClearInput(Button_P0_Test, 0x68);
            TTXConfig.ClearInput(Button_P0_Exit, 0x6C);
        }

        private void Button_M_ClearAll_Click(object sender, EventArgs e)
        {
            TTXConfig.ClearInput(Button_M_Start, 0x7C);
            TTXConfig.ClearInput(Button_M_Service, 0x78);
            TTXConfig.ClearInput(Button_M_Kong, 0xB8);
            TTXConfig.ClearInput(Button_M_Pon, 0xBC);
            TTXConfig.ClearInput(Button_M_Chi, 0xC0);
            TTXConfig.ClearInput(Button_M_Reach, 0xC4);
            TTXConfig.ClearInput(Button_M_Ron, 0xC8);
            TTXConfig.ClearInput(Button_M_ButtonA, 0x80);
            TTXConfig.ClearInput(Button_M_ButtonB, 0x84);
            TTXConfig.ClearInput(Button_M_ButtonC, 0x88);
            TTXConfig.ClearInput(Button_M_ButtonD, 0x8C);
            TTXConfig.ClearInput(Button_M_ButtonE, 0x90);
            TTXConfig.ClearInput(Button_M_ButtonF, 0x94);
            TTXConfig.ClearInput(Button_M_ButtonG, 0x98);
            TTXConfig.ClearInput(Button_M_ButtonH, 0x9C);
            TTXConfig.ClearInput(Button_M_ButtonI, 0xA0);
            TTXConfig.ClearInput(Button_M_ButtonJ, 0xA4);
            TTXConfig.ClearInput(Button_M_ButtonK, 0xA8);
            TTXConfig.ClearInput(Button_M_ButtonL, 0xAC);
            TTXConfig.ClearInput(Button_M_ButtonM, 0xB0);
            TTXConfig.ClearInput(Button_M_ButtonN, 0xB4);

            TTXConfig.ClearInput(Button_P0_Test, 0x68);
            TTXConfig.ClearInput(Button_P0_Exit, 0x6C);
        }

        private void LinkLabel_Romhack_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://github.com/zxmarcos");
        }

        private void LinkLabel_Hipnosis_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://hipnosis183.github.io/");
        }

        private void Button_Save_Click(object sender, EventArgs e)
        {
            TTXConfig.WriteTTXConfig();
            Application.ExitThread();
        }

        private void Button_Cancel_Click(object sender, EventArgs e)
        {
            Application.ExitThread();
        }

        bool Last = false;

        private void TabControl_Input_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (TabControl_Input.SelectedIndex == 2)
            {
                Program.Launcher.Visible = false;

                ModifyLayout();
                Last = true;

                Program.Launcher.Visible = true;
            }

            else if (Last)
            {
                Program.Launcher.Visible = false;

                RestoreLayout();
                Last = false;

                Program.Launcher.Visible = true;
            }
        }

        private void ModifyLayout()
        {
            Program.Launcher.Size = new System.Drawing.Size(500, 554);
            Program.Launcher.CenterToScreen();
            GroupBox_Options.Hide();

            PictureBox_Logo.Location = new System.Drawing.Point(47, 12);
            LinkLabel_Romhack.Location = new System.Drawing.Point(340, 101);
            LinkLabel_Hipnosis.Location = new System.Drawing.Point(400, 101);
            Label_Middle.Location = new System.Drawing.Point(392, 101);
            TabControl_Input.Size = new System.Drawing.Size(471, 412);
            GroupBox_Device.Size = new System.Drawing.Size(447, 56);
            ComboBox_Device.Size = new System.Drawing.Size(340, 21);
            Button_Refresh.Location = new System.Drawing.Point(364, 23);
            Button_M_SetAll.Location = new System.Drawing.Point(166, 317);
            Button_M_ClearAll.Location = new System.Drawing.Point(166, 344);
            GroupBox_P1_Other.Location = new System.Drawing.Point(24, 416);
            GroupBox_OptionsM.Location = new System.Drawing.Point(256, 293);
            Button_Save.Location = new System.Drawing.Point(388, 440);
            Button_Cancel.Location = new System.Drawing.Point(388, 469);
        }

        private void RestoreLayout()
        {
            Program.Launcher.Size = new System.Drawing.Size(452, 490);
            Program.Launcher.CenterToScreen();
            GroupBox_Options.Show();

            PictureBox_Logo.Location = new System.Drawing.Point(23, 12);
            LinkLabel_Romhack.Location = new System.Drawing.Point(316, 101);
            LinkLabel_Hipnosis.Location = new System.Drawing.Point(376, 101);
            Label_Middle.Location = new System.Drawing.Point(368, 101);
            TabControl_Input.Size = new System.Drawing.Size(424, 348);
            GroupBox_Device.Size = new System.Drawing.Size(400, 56);
            ComboBox_Device.Size = new System.Drawing.Size(284, 21);
            Button_Refresh.Location = new System.Drawing.Point(318, 23);
            GroupBox_P1_Other.Location = new System.Drawing.Point(24, 353);
            Button_Save.Location = new System.Drawing.Point(342, 376);
            Button_Cancel.Location = new System.Drawing.Point(342, 405);
        }
    }
}