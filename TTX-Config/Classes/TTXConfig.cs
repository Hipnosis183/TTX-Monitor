using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace TTXMonitor.Classes
{
    class TTXConfig
    {
        // Initialize configuration files.
        public static byte[] MonitorInputLoad = new byte[0xE0];
        public static byte[] MonitorMiscLoad = new byte[0x10];

        public const string MonitorInputFile = "monitor_input.bin";
        public const string MonitorMiscFile = "monitor_misc.bin";

        public static void InitialSetup()
        {
            if (File.Exists(MonitorInputFile))
            {
                MonitorInputLoad = File.ReadAllBytes(MonitorInputFile);
            }

            if (File.Exists(MonitorMiscFile))
            {
                MonitorMiscLoad = File.ReadAllBytes(MonitorMiscFile);
            }
        }

        // Write configuration files.
        public static void WriteTTXConfig()
        {
            // Little hack for mahjong inputs.
            for (int i = 0x68, k = 0xD8; i < 0x70; i++, k++)
            {
                MonitorInputLoad[k] = MonitorInputLoad[i];
            }

            WriteTTXFile(MonitorInputFile, MonitorInputLoad, 0x00, 0xE0);
            WriteTTXFile(MonitorMiscFile, MonitorMiscLoad, 0x00, 0x10);
        }

        public static void WriteTTXFile(string FileNameInput, byte[] FileNameOutput, int Offset, int Lenght)
        {
            if (File.Exists(FileNameInput))
            {
                File.Delete(FileNameInput);
            }
            
            using (BinaryWriter Stream = new BinaryWriter(new FileStream(FileNameInput, FileMode.Create)))
            {
                Stream.Write(FileNameOutput, Offset, Lenght);
            }
        }

        // Handle checkboxes status with the configuration.
        public static void GetCheck(CheckBox Check, int HexPosition)
        {
            Check.Checked = MonitorMiscLoad[HexPosition] == 0x01;
        }

        public static void SetConfig_CheckBox(CheckBox Check, int HexPosition)
        {
            MonitorMiscLoad[HexPosition] = Check.Checked ? (byte)0x01 : (byte)0x00;
        }

        // Handle checkboxes' parent and child (de)activation.
        public static void SetConfig_CheckBox_Disable(CheckBox CheckBoxIn, CheckBox CheckBoxOut)
        {
            CheckBoxOut.Enabled = CheckBoxIn.Checked;
        }

        public static void SetDevice(ComboBox Combo)
        {
            try
            {
                Controller.SetCurrentDevice(Combo.SelectedIndex, Controller.DevicesGuids);
            }

            catch
            {
                Controller.SetCurrentDevice(0, Controller.DevicesGuids);
            }
        }

        private static void SetConfig_Input(Button ButtonText, string Text, byte[] ByteArray, int HexPosition)
        {
            MonitorInputLoad[HexPosition] = ByteArray[0];
            MonitorInputLoad[HexPosition + 1] = ByteArray[1];
            MonitorInputLoad[HexPosition + 2] = ByteArray[2];
            MonitorInputLoad[HexPosition + 3] = ByteArray[3];

            ButtonText.Text = Text;
        }

        public static void ClearInput(Button ButtonText, int HexPosition)
        {
            MonitorInputLoad[HexPosition] = 0x00;
            MonitorInputLoad[HexPosition + 1] = 0x00;
            MonitorInputLoad[HexPosition + 2] = 0x00;
            MonitorInputLoad[HexPosition + 3] = 0x00;

            ButtonText.Text = null;
        }

        public static void SetFeatureToAllControls(Control.ControlCollection CCollection)
        {
            if (CCollection != null)
            {
                foreach (Control Control in CCollection)
                {
                    Control.PreviewKeyDown += new PreviewKeyDownEventHandler(Control_PreviewKeyDown);

                    SetFeatureToAllControls(Control.Controls);
                }
            }
        }

        private static void Control_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Up || e.KeyCode == Keys.Down || e.KeyCode == Keys.Left ||
                e.KeyCode == Keys.Right || e.KeyCode == Keys.Enter || e.KeyCode == Keys.Space)
            {
                e.IsInputKey = true;
            }
        }

        public static void LoadController(ComboBox Combo)
        {
            Combo.DataSource = null;
            Combo.Items.Clear();

            Controller.GetControllers();

            Combo.DataSource = Controller.DevicesNames;
            Combo.SelectedIndex = 0;

            Controller.SetCurrentDevice(0, Controller.DevicesGuids);

            Controller.DeviceNumber = Combo.SelectedIndex;
        }

        public static void LoadInput(Button ButtonText, int HexPosition)
        {
            byte[] StoredHex = new byte[3];

            StoredHex[0] = MonitorInputLoad[HexPosition];
            StoredHex[1] = MonitorInputLoad[HexPosition + 1];
            StoredHex[2] = MonitorInputLoad[HexPosition + 2];

            if (MonitorInputLoad[HexPosition + 3] != 0x00)
            {
                for (int i = 0; i < JoystickHex.Count; i++)
                {
                    byte[] CurrentHex = JoystickHex[i];

                    if (CurrentHex[0] == StoredHex[0] && CurrentHex[1] == StoredHex[1] && CurrentHex[2] == StoredHex[2])
                    {
                        ButtonText.Text = JoystickNames[i];

                        return;
                    }
                }

                ButtonText.Text = "Button " + Convert.ToInt32(StoredHex[0]);
            }

            else
            {
                if (MonitorInputLoad[HexPosition] != 0x00)
                {
                    foreach (Microsoft.DirectX.DirectInput.Key temp in Enum.GetValues(typeof(Microsoft.DirectX.DirectInput.Key)))
                    {
                        if (Convert.ToInt32(StoredHex[0]) == (int)temp && StoredHex[1] == 0x00 && StoredHex[2] == 0x00)
                        {
                            ButtonText.Text = temp.ToString();

                            return;
                        }
                    }
                }

                else
                {
                    ButtonText.Text = null;
                }
            }
        }

        // Handle mouse buttons clicks.
        public static void Button_Click(Button ButtonText, int HexPosition, MouseEventArgs e)
        {
            // If left mouse button is clicked, start polling for inputs.
            if (e.Button == MouseButtons.Left)
            {
                if ((int)Controller.Current.DeviceInformation.DeviceType != 19)
                {
                    Button_Click_J(ButtonText, HexPosition);
                }

                else
                {
                    Button_Click_K(ButtonText, HexPosition);
                }
            }

            // If right mouse button is clicked, clear the input.
            else
            {
                ClearInput(ButtonText, HexPosition);
            }
        }

        // Handle joystick input polling.
        private static void Button_Click_J(Button ButtonText, int HexPosition)
        {
            string CurrentText = ButtonText.Text;

            ButtonText.Text = "...";
            ButtonText.Update();

            byte[] Input = Controller.GetInputJ();

            if (Input != null)
            {
                SetConfig_Input(ButtonText, Controller.ButtonName, Input, HexPosition);
            }

            else
            {
                ButtonText.Text = CurrentText;
            }
        }

        // Handle keyboard input polling.
        private static void Button_Click_K(Button ButtonText, int HexPosition)
        {
            string CurrentText = ButtonText.Text;

            ButtonText.Text = "...";
            ButtonText.Update();

            Microsoft.DirectX.DirectInput.Key Input = Controller.GetInputK();

            byte[] InputHex = new byte[4];
            byte[] InputKey = BitConverter.GetBytes((int)Input);

            InputHex[0] = InputKey[0];

            if (Input != 0)
            {
                SetConfig_Input(ButtonText, Input.ToString(), InputHex, HexPosition);
            }

            else
            {
                ButtonText.Text = CurrentText;
            }
        }

        public static void SetInput(Button ButtonText, int HexPosition)
        {
            if ((int)Controller.Current.DeviceInformation.DeviceType != 19)
            {
                Button_Click_J(ButtonText, HexPosition);
            }

            else
            {
                Button_Click_K(ButtonText, HexPosition);
            }

            ButtonText.Update();

            System.Threading.Thread.Sleep(200);
        }

        // Initialize joystick configuration structures.
        private static List<byte[]> JoystickHex = new List<byte[]>();
        private static List<string> JoystickNames = new List<string>();

        public static void CreateJoystickValues()
        {
            CreateJoystickHex();
            CreateJoystickNames();
        }

        private static void CreateJoystickHex()
        {
            JoystickHex.Add(new byte[] { 0x00, 0x00, 0x0A });
            JoystickHex.Add(new byte[] { 0x50, 0x46, 0x0A });
            JoystickHex.Add(new byte[] { 0x78, 0x69, 0x0A });
            JoystickHex.Add(new byte[] { 0x28, 0x23, 0x0A });
            JoystickHex.Add(new byte[] { 0x18, 0xFC, 0x12 });
            JoystickHex.Add(new byte[] { 0xE8, 0x03, 0x02 });
            JoystickHex.Add(new byte[] { 0x18, 0xFC, 0x11 });
            JoystickHex.Add(new byte[] { 0xE8, 0x03, 0x01 });
            JoystickHex.Add(new byte[] { 0x18, 0xFC, 0x15 });
            JoystickHex.Add(new byte[] { 0xE8, 0x03, 0x05 });
            JoystickHex.Add(new byte[] { 0x18, 0xFC, 0x14 });
            JoystickHex.Add(new byte[] { 0xE8, 0x03, 0x04 });
            JoystickHex.Add(new byte[] { 0xE8, 0x03, 0x03 });
            JoystickHex.Add(new byte[] { 0x18, 0xFC, 0x13 });
        }

        private static void CreateJoystickNames()
        {
            JoystickNames.Add("POV Up");
            JoystickNames.Add("POV Down");
            JoystickNames.Add("POV Left");
            JoystickNames.Add("POV Right");
            JoystickNames.Add("Left Y+");
            JoystickNames.Add("Left Y-");
            JoystickNames.Add("Left X-");
            JoystickNames.Add("Left X+");
            JoystickNames.Add("Right Y+");
            JoystickNames.Add("Right Y-");
            JoystickNames.Add("Right X-");
            JoystickNames.Add("Right X+");
            JoystickNames.Add("Trigger L");
            JoystickNames.Add("Trigger R");
        }
    }
}
