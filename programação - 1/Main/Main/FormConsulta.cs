using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Main
{
    public partial class FormConsulta : Form
    {
        public FormConsulta()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(radioButton2.Checked = true)
            {
                FormConsultaAoTodo formConsultaAoTodo = new FormConsultaAoTodo();
                formConsultaAoTodo.ShowDialog();
            }
        }
    }
}
