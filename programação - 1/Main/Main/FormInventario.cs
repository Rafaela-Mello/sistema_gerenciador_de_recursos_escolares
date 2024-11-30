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
    public partial class FormInventario : Form
    {
        public FormInventario()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (rdbCasdratro.Checked == true)
            {
                FormCadastro formCadastro = new FormCadastro();
                formCadastro.ShowDialog();
            }
            else if (rdbConsulta.Checked == true)
            {
                FormConsulta formConsulta = new FormConsulta();
                formConsulta.ShowDialog();
            }
        }

        private void btnVoltar_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
