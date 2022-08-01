using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5_labd_MiksAre
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Exit(object sender, EventArgs e)
        {
            Close();
        }

        private void Add(object sender, EventArgs e)
        {
            try {
                Result.Text = Convert.ToString(Convert.ToDouble(FirstOperand.Text) + Convert.ToDouble(SecondOperand.Text));
            }
            catch {
                MessageBox.Show("Error in operands!", "Calculator Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void Sub(object sender, EventArgs e)
        {
            try
            {
                Result.Text = Convert.ToString(Convert.ToDouble(FirstOperand.Text) - Convert.ToDouble(SecondOperand.Text));
            }
            catch
            {
                MessageBox.Show("Error in operands!", "Calculator Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Mul(object sender, EventArgs e)
        {
            try
            {
                Result.Text = Convert.ToString(Convert.ToDouble(FirstOperand.Text) * Convert.ToDouble(SecondOperand.Text));
            }
            catch
            {
                MessageBox.Show("Error in operands!", "Calculator Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Div(object sender, EventArgs e)
        {
            try
            {
                Result.Text = Convert.ToString(Convert.ToDouble(FirstOperand.Text) / Convert.ToDouble(SecondOperand.Text));
            }
            catch
            {
                MessageBox.Show("Error in operands!", "Calculator Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
