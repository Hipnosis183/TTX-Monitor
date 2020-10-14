using Microsoft.DirectX.DirectInput;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;

namespace TTXMonitor.Classes
{
    class Controller
    {
        public static List<Device> Devices = new List<Device>();
        public static List<string> DevicesNames = new List<string>();
        public static List<DeviceInstance> DevicesGuids = new List<DeviceInstance>();

        public static Device Current;

        public static JoystickState StateJoystick;
        public static KeyboardState StateKeyboard;

        public static int DeviceNumber;
        public static string ButtonName;

        public static void GetControllers()
        {
            int i = 0;

            ResetDevices();

            DeviceList ControllersList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);

            foreach (DeviceInstance Controller in ControllersList)
            {
                Devices.Add(new Device(Controller.InstanceGuid));

                DevicesNames.Add(" [" + i + "] - " + Controller.InstanceName.ToString());
                DevicesGuids.Add(Controller);

                i++;
            }

            DeviceList KeyboardList = Manager.GetDevices(DeviceClass.Keyboard, EnumDevicesFlags.AttachedOnly);

            foreach (DeviceInstance Keyboard in KeyboardList)
            {
                Devices.Add(new Device(Keyboard.InstanceGuid));

                DevicesNames.Add(" [" + i + "] - " + Keyboard.InstanceName.ToString());
                DevicesGuids.Add(Keyboard);

                i++;
            }
        }

        public static void ResetDevices()
        {
            Devices.Clear();
            DevicesNames.Clear();
            DevicesGuids.Clear();
        }

        public static void SetCurrentDevice(int Index, List<DeviceInstance> DeviceGuid)
        {
            int i = 0;
            
            foreach (Device Device in Devices)
            {
                if (Device.DeviceInformation.ProductGuid == DeviceGuid[Index].ProductGuid)
                {
                    try
                    {
                        Current = Device;
                        Current.Acquire();

                        if ((int)Current.DeviceInformation.DeviceType != 19)
                        {
                            StateJoystick = Current.CurrentJoystickState;
                        }

                        else
                        {
                            StateKeyboard = Current.GetCurrentKeyboardState();
                        }

                        DeviceNumber = i;
                    }

                    catch {}
                }

                i++;
            }
        }

        public static void Update()
        {
            Current.Poll();

            if ((int)Current.DeviceInformation.DeviceType != 19)
            {
                StateJoystick = Current.CurrentJoystickState;
            }

            else
            {
                StateKeyboard = Current.GetCurrentKeyboardState();
            }
        }

        public static byte[] GetInputJ() // Joystick
        {
            try
            {
                return GetInputJoystick();
            }

            catch
            {
                MessageBox.Show("No device selected.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                return null;
            }
        }

        public static byte[] GetInputJoystick()
        {
            Stopwatch StopWatch = new Stopwatch();
            StopWatch.Start();

            while (true)
            {
                Update();

                int[] POV = StateJoystick.GetPointOfView();
                byte[] Button = StateJoystick.GetButtons();

                if (StateJoystick.X > 55535) // Left X+
                {
                    ButtonName = "Left X+";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0xE8, 0x03, 0x01, NumberHex[0] };
                }

                else if (StateJoystick.X < 16535) // Left X-
                {
                    ButtonName = "Left X-";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0x18, 0xFC, 0x11, NumberHex[0] };
                }

                if (StateJoystick.Y < 16535) // Left Y+
                {
                    ButtonName = "Left Y+";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0x18, 0xFC, 0x12, NumberHex[0] };
                }

                if (StateJoystick.Y > 55535) // Left Y-
                {
                    ButtonName = "Left Y-";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0xE8, 0x03, 0x02, NumberHex[0] };
                }

                if (StateJoystick.Rx > 55535) // Right X+
                {
                    ButtonName = "Right X+";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0xE8, 0x03, 0x04, NumberHex[0] };
                }

                else if (StateJoystick.Rx < 16535) // Right X-
                {
                    ButtonName = "Right X-";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0x18, 0xFC, 0x14, NumberHex[0] };
                }

                if (StateJoystick.Ry < 16535) // Right Y+
                {
                    ButtonName = "Right Y+";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0x18, 0xFC, 0x15, NumberHex[0] };
                }

                if (StateJoystick.Ry > 55535) // Right Y-
                {
                    ButtonName = "Right Y-";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0xE8, 0x03, 0x05, NumberHex[0] };
                }

                if (StateJoystick.Z > 55535) // Trigger L
                {
                    ButtonName = "Trigger L";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0xE8, 0x03, 0x03, NumberHex[0] };
                }

                if (StateJoystick.Z < 16535) // Trigger R
                {
                    ButtonName = "Trigger R";

                    byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                    return new byte[] { 0x18, 0xFC, 0x13, NumberHex[0] };
                }

                for (int i = 0; i < POV.Length; i++) // POV
                {
                    if (POV[i] != -1)
                    {
                        byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                        switch (POV[i])
                        {
                            case 0: 
                                ButtonName = "POV Up";
                                return new byte[] { 0x00, 0x00, 0x0A, NumberHex[0] };
                            
                            case 18000: 
                                ButtonName = "POV Down";
                                return new byte[] { 0x50, 0x46, 0x0A, NumberHex[0] };
                            
                            case 27000:
                                ButtonName = "POV Left";
                                return new byte[] { 0x78, 0x69, 0x0A, NumberHex[0] };
                            
                            case 9000:
                                ButtonName = "POV Right";
                                return new byte[] { 0x28, 0x23, 0x0A, NumberHex[0] };
                        }
                    }
                }

                for (int i = 0; i < Button.Length; i++) // Button
                {
                    if (Button[i] != 0)
                    {
                        byte[] InputHex = new byte[4];

                        byte[] IHex = BitConverter.GetBytes(i);
                        byte[] NumberHex = BitConverter.GetBytes(128 + DeviceNumber);

                        ButtonName = "Button " + IHex[0].ToString();

                        InputHex[0] = IHex[0];
                        InputHex[3] = NumberHex[0];
                                                
                        return InputHex;                        
                    }
                }

                if (StopWatch.ElapsedMilliseconds > 3000)
                {
                    return null;
                }

                System.Threading.Thread.Sleep(10);
            }
        }

        public static Key GetInputK() // Keyboard
        {
            try
            {
                return GetInputKeyboard();
            }

            catch
            {
                MessageBox.Show("No device selected.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                return 0;
            }
        }

        public static Key GetInputKeyboard()
        {
            Stopwatch StopWatch = new Stopwatch();
            StopWatch.Start();
            
            while (true)
            {
                Update();

                Key[] PressedKey = Current.GetPressedKeys();

                if (PressedKey.Length != 0)
                {
                    return PressedKey[0];
                }

                if (StopWatch.ElapsedMilliseconds > 3000)
                {
                    return 0;
                }

                System.Threading.Thread.Sleep(10);
            }
        }
    }
}
