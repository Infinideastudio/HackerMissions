using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapMaker
{
    public partial class Form3 : Form
    {
        static int xall = 0;
        static int yall = 0;
        static float xunit = 0;
        static float yunit = 0;
        static int choX = -1;
        static int choY = -1;
        public Form3(int level=-1)
        {
            InitializeComponent();
            if (level != -1) textBox3.Text = level.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int lev = int.Parse(textBox3.Text);
            FileStream fs = new FileStream("level" + lev + ".dat", FileMode.Open);
            BinaryReader br = new BinaryReader(fs);
            int level = br.ReadInt32();
            xall = br.ReadInt32();
            yall = br.ReadInt32();

            byte[] tmpMap = new byte[xall * yall];

            tmpMap = br.ReadBytes(xall * yall);

            byte[,] map = new byte[xall, yall];

            br.Close();
            fs.Close();

            Image[] textures = new Image[2];
            for (int i = 0; i != 2; i++)
            {
                textures[i] = Image.FromFile("textures/" + i + ".bmp");
            }
            Bitmap bmp = new Bitmap(400, 250);
            Graphics g = Graphics.FromImage(bmp);
            xunit = 400 / xall;
            yunit = 250 / yall;
            for (int x = 0; x < xall; x++)
            {
                for (int y = 0; y < yall; y++)
                {
                    map[x, y] = tmpMap[x * yall + y];
                    g.DrawImage(textures[map[x, y]], x * xunit, y * yunit, xunit, yunit);
                }
            }
            g.DrawLine(new Pen(Color.Gray, 1), new Point(0, 0), new Point(399, 0));
            g.DrawLine(new Pen(Color.Gray, 1), new Point(399, 0), new Point(399, 249));
            g.DrawLine(new Pen(Color.Gray, 1), new Point(0, 249), new Point(399, 249));
            g.DrawLine(new Pen(Color.Gray, 1), new Point(0, 0), new Point(0, 249));
            for (int x = 1; x < xall; x++)
            {
                g.DrawLine(new Pen(Color.Gray, 1), new Point((int)(x * xunit), 0), new Point((int)(x * xunit), 250));
            }
            for (int y = 1; y < yall; y++)
            {
                g.DrawLine(new Pen(Color.Gray, 1), new Point(0, (int)(y * yunit)), new Point(400, (int)(y * yunit)));
            }
            pictureBox1.Image = bmp;

        }

        private void Form3_FormClosed(object sender, FormClosedEventArgs e)
        {
            System.Environment.Exit(0);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            System.Environment.Exit(0);
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (xall == 0 || yall == 0 || xunit == 0 || yunit == 0) return;
            int xpos = (int)(e.X / xunit);
            int ypos = (int)(e.Y / yunit);
            label2.Text = "(" + xpos + "," + ypos + ")";
            choX = xpos;
            choY = ypos;
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            textBox2.ReadOnly = comboBox2.Text != "特殊条件";
            textBox4.ReadOnly = comboBox2.Text != "移动触发";
            button4.Enabled = comboBox2.Text == "移动触发";
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox4.Text = choX + "," + choY;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            string gen="",extra1="",extra2="";
            if(comboBox1.Text=="一次性"){
                if(comboBox2.Text=="无条件"){
                    MessageBox.Show("不支持的类型！");
                    return;
                }else{
                    extra1="eventGen.setRequirement([]()->bool{"+textBox1.Text+"});";
                }
                if(textBox4.Text==""){
                    gen="Event eventGen(true);";
                }else{
                    gen="Event eventGen(AABB("+ textBox4.Text +"), true);";
                }
            }else{
                if(comboBox2.Text=="无条件"){
                    if(textBox1.Text!=""){
                        gen="Event eventGen([&]{"+textBox1.Text+"});";
                    }
                    else{
                        gen="Event eventGen();";
                    }
                }
                else if (comboBox2.Text == "特殊条件")
                {
                    extra1="eventGen.setRequirement([]()->bool{"+textBox1.Text+"});";
                }
                else
                {
                    gen = "Event eventGen(AABB(" + textBox4.Text + "), true);";
                }
            }
            if(textBox1.Text!=""&&extra2=="") extra2="eventGen.setAction([&]{"+textBox1.Text+"});";
            if (gen == "") gen = "Event eventGen;";
            textBox5.Text = gen + "\r\n" + extra1 + "\r\n" + extra2;
        }
    }
}
