using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace MapMaker
{
    public partial class Form2 : Form
    {
        static byte[,] MapData;
        static int xall = 0;
        static int yall = 0;
        static float xunit = 0;
        static float yunit = 0;
        static Image[] textures = new Image[2];
        public Form2()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int lev = int.Parse(textBox3.Text);
            FileStream fs = new FileStream("level" + lev + ".dat", FileMode.Create);
            BinaryWriter bw = new BinaryWriter(fs);
            bw.Write(lev);
            bw.Write(xall);
            bw.Write(yall);
            byte[] temparray=new byte[xall*yall];
                            
              for(int i=0;i<xall*yall;i++)
              {
               int r = i / yall;
               int c = i % yall;
               temparray[i] = MapData[r, c];
              }
            bw.Write(temparray, 0, temparray.Length);
            bw.Flush();
            bw.Close();
            fs.Close();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            for (int i = 0; i != 2; i++)
            {
                textures[i]=Image.FromFile("textures/"+i+".bmp");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Bitmap bmp = new Bitmap(400, 250);
            Graphics g = Graphics.FromImage(bmp);
            xall = int.Parse(textBox1.Text);
            yall = int.Parse(textBox2.Text);
            xunit = 400 / xall;
            yunit = 250 / yall;
            MapData = new byte[xall, yall];
            g.DrawImage(textures[0], 0, 0, 399, 249);
            g.DrawLine(new Pen(Color.Black, 1), new Point(0, 0), new Point(399, 0));
            g.DrawLine(new Pen(Color.Black, 1), new Point(399, 0), new Point(399, 249));
            g.DrawLine(new Pen(Color.Black, 1), new Point(0, 249), new Point(399, 249));
            g.DrawLine(new Pen(Color.Black, 1), new Point(0, 0), new Point(0, 249));
            for (int x = 1; x < xall; x++)
            {
                g.DrawLine(new Pen(Color.Black, 1), new Point((int)(x * xunit), 0), new Point((int)(x * xunit), 250));
            }
            for (int y = 1; y < yall; y++)
            {
                g.DrawLine(new Pen(Color.Black, 1), new Point(0, (int)(y * yunit)), new Point(400, (int)(y * yunit)));
            }
            pictureBox1.Image = bmp;
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (xall == 0 || yall == 0 || xunit == 0 || yunit == 0) return;
            int xpos=(int)(e.X / xunit);
            int ypos=(int)(e.Y / yunit);
            byte setval = (byte)(MapData[xpos, ypos] + 1);
            if (setval >= 2) setval = 0;
            MapData[xpos, ypos] = setval;
            Bitmap bmp = new Bitmap(pictureBox1.Image);
            Graphics g = Graphics.FromImage(bmp);
            g.DrawImage(textures[setval], xpos * xunit, ypos * yunit, xunit, yunit);
            //g.DrawString(((int)setval).ToString(), new Font("微软雅黑", 16), new SolidBrush(Color.Black), xpos*xunit, ypos*yunit);
            pictureBox1.Image = bmp;
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            System.Environment.Exit(0);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            System.Environment.Exit(0);
        }
    }
}
