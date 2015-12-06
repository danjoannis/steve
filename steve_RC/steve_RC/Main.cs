using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace steve_RC
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();

            if (!serialPort1.IsOpen)
            {
                serialPort1.PortName = "COM4";
                serialPort1.BaudRate = 38400;
                serialPort1.Open();
            }
        }

        private bool bUpKey;
        private bool bDownKey;
        private bool bLeftKey;
        private bool bRightKey;
        private bool bShiftKey;

        private void evaluate()
        {
            byte[] buff = new byte[7];

            // Load element 0 with the key character.
            buff[0] = (byte)'D';
            buff[1] = (byte)'=';
            
            if (bUpKey)
            {
                buff[2] = 1;
                if (bLeftKey)
                {
                    label1.Text = "UL";
                    buff[3] = 1;
                }
                else if (bRightKey)
                {
                    label1.Text = "UR";
                    buff[3] = 2;
                }
                else
                {
                    label1.Text = "U";
                    buff[3] = 0;
                }
            }
            else if (bDownKey)
            {
                buff[2] = 2;
                if (bLeftKey)
                {
                    label1.Text = "DL";
                    buff[3] = 1;
                }
                else if (bRightKey)
                {
                    label1.Text = "DR";
                    buff[3] = 2;
                }
                else
                {
                    label1.Text = "D";
                    buff[3] = 0;
                }
            }
            else if (bLeftKey)
            {
                buff[2] = 0;
                label1.Text = "L";
                buff[3] = 1;
            }
            else if (bRightKey)
            {
                buff[2] = 0;
                label1.Text = "R";
                buff[3] = 2;
            }
            else if (!bLeftKey && !bRightKey && !bUpKey && !bDownKey)
            {
                label1.Text = "?";
            }
            
            buff[4] = 100;
            if (bShiftKey)
            {
                buff[4] = 200;
            }
            buff[5] = 5;
            buff[6] = (byte)'\r';

            if ((bLeftKey || bRightKey || bUpKey || bDownKey) && serialPort1.IsOpen)
            {
                // Send the one character buffer.
                serialPort1.Write(buff, 0, 7);
            }
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {            
            if (e.KeyCode == Keys.Up)
            {
                bUpKey = true;
            }
            else if (e.KeyCode == Keys.Down)
            {
                bDownKey = true;
            }
            else if (e.KeyCode == Keys.Left)
            {
                bLeftKey = true;
            }
            else if (e.KeyCode == Keys.Right)
            {
                bRightKey = true;
            }
            else if (e.KeyCode == Keys.ShiftKey)
            {
                bShiftKey = true;
            }

            evaluate();
        }

        private void Main_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Up)
            {
                bUpKey = false;
            }
            else if (e.KeyCode == Keys.Down)
            {
                bDownKey = false;
            }
            else if (e.KeyCode == Keys.Left)
            {
                bLeftKey = false;
            }
            else if (e.KeyCode == Keys.Right)
            {
                bRightKey = false;
            }
            else if (e.KeyCode == Keys.ShiftKey)
            {
                bShiftKey = false;
            }

            evaluate();
        }

        /*private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serialPort1.PortName = "COM4";
                serialPort1.BaudRate = 38400;
                serialPort1.Open();
                button1.Text = "Connected";
            }
            else if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                button1.Text = "Disconnected";
            }
        }*/
    }
}
