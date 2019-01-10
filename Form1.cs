using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test1C3
{
    public partial class SortToFolder : Form
    {
        //Sort Buttom


        [DllImport("FileOrganizerDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string startApplication(bool perm = false, string[] arr = null, int size = 0);

        private static DialogResult ShowInputDialog(ref string input)
        {
            System.Drawing.Size size = new System.Drawing.Size(200, 70);
            Form inputBox = new Form();

            inputBox.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            inputBox.ClientSize = size;
            inputBox.Text = "Name";

            System.Windows.Forms.TextBox textBox = new TextBox();
            textBox.Size = new System.Drawing.Size(size.Width - 10, 23);
            textBox.Location = new System.Drawing.Point(5, 5);
            textBox.Text = input;
            inputBox.Controls.Add(textBox);

            Button okButton = new Button();
            okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            okButton.Name = "okButton";
            okButton.Size = new System.Drawing.Size(75, 23);
            okButton.Text = "&OK";
            okButton.Location = new System.Drawing.Point(size.Width - 80 - 80, 39);
            inputBox.Controls.Add(okButton);

            Button cancelButton = new Button();
            cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            cancelButton.Name = "cancelButton";
            cancelButton.Size = new System.Drawing.Size(75, 23);
            cancelButton.Text = "&Cancel";
            cancelButton.Location = new System.Drawing.Point(size.Width - 80, 39);
            inputBox.Controls.Add(cancelButton);

            inputBox.AcceptButton = okButton;
            inputBox.CancelButton = cancelButton;

            DialogResult result = inputBox.ShowDialog();
            input = textBox.Text;
            return result;
        }
        //List<string> allInput = new List<string>();

        public static class Globals
        {
            public const Int32 BUFFER_SIZE = 512; // Unmodifiable
            public static String FILE_NAME = "Output.txt"; // Modifiable
            public static readonly String CODE_PREFIX = "US-"; // Unmodifiable
            public static int lastID = 0; // Modifiable
            public static string lastStringTB = ""; // Modifiable
        }
        Dictionary<String, int> allLocations = new Dictionary<string, int>();
        public SortToFolder()
        {
            
            InitializeComponent();
            try
            {
                this.textBox1.Multiline = true;
                string path = Environment.CurrentDirectory + "/" + "sortToFolderFinal.conf";
                FileInfo fInfo = new FileInfo(path);

                if (!fInfo.Exists)
                {
                    File.CreateText(path);
                }
                else
                {
                    using (StreamReader sr = new StreamReader(path))
                    {
                        if (new FileInfo(path).Length == 0)
                        {
                        }
                        else
                        {
                            String line;
                            line = sr.ReadLine();
                            //Continue to read until you reach end of file
                            int count = 0;
                            while (line != null)
                            {
                                //write the lie to console window
                                allLocations.Add(line, count);
                                //Read the next line
                                line = sr.ReadLine();
                                count++;
                            }
                        }
                    }
                }
            }
            catch(Exception except)
            {
                try
                {
                    string path = Environment.CurrentDirectory + "/" + "sortToFolderFinal.conf";
                    using (StreamWriter sw = new StreamWriter(path))
                    {
                        File.CreateText(path);
                    }

                    System.Windows.Forms.MessageBox.Show(GetExceptionDetails(except));
                }
                catch (Exception except2)
                {
                    System.Windows.Forms.MessageBox.Show(GetExceptionDetails(except2));
                }
            }
            
            printToScreen();
        }

        private void printToScreen()
        {
            textBox1.AppendText("Locations:----");
            textBox1.AppendText(Environment.NewLine);
            foreach (KeyValuePair<string, int> entry in allLocations)   
            {
                textBox1.AppendText(entry.Key);
                textBox1.AppendText(Environment.NewLine);

            }
        }

        string getLatest()
        {
            return Globals.lastStringTB;
        }

        public Dictionary<string, int> AllLocations { get => allLocations; set => allLocations = value; }

        private void button1_Click(object sender, EventArgs e)
        {
            //Set Sort Locations
            string path = Environment.CurrentDirectory + "/" + "sortToFolderFinal.conf";
            if(!File.Exists(path))
            {

            }
            else
            {
                textBox1.Text = String.Empty;
                try
                {
                    if(textBox1.Multiline == true)
                    {
                        //System.Windows.Forms.MessageBox.Show("MultiLined");   
                    }
                    string[] lines = Globals.lastStringTB.Split( new[] { Environment.NewLine }, StringSplitOptions.None );
                    Dictionary<string, int> AllLocationsCopy = new Dictionary<string, int>();
                    //System.Windows.Forms.MessageBox.Show(lines[0]);
                    for (int count = 0; count < lines.Length; count++)
                    {

                        if (lines[count] == "" || lines[count] == Environment.NewLine || lines[count] == "\n" || lines[count] == "Locations:----") {
                            //System.Windows.Forms.MessageBox.Show("Not added");
                        }
                        else
                        {
                            if (AllLocationsCopy.ContainsKey(lines[count]))
                            {
                                continue;
                            }
                            else
                            {
                                AllLocationsCopy.Add(lines[count], count);
                            }
                           // AllLocationsCopy.Add(lines[count], count); 

                        }

                    }
                    AllLocations = AllLocationsCopy;
                }
                catch (Exception except)
                {
                    // Something unexpected went wrong.
                    System.Windows.Forms.MessageBox.Show(GetExceptionDetails(except));
                }

                using (StreamWriter sw = new StreamWriter(path))
                {
                    foreach (KeyValuePair<string, int> entry in allLocations)
                    {
                        sw.WriteLine(entry.Key);   
                    }
                }
            }
            textBox1.Text = String.Empty;
        }
       
        private void button2_Click(object sender, EventArgs e)
        {
            //System.Windows.Forms.MessageBox.Show("Fuck");
            try
            {
                textBox1.Text = String.Empty;
                textBox1.AppendText("Locations:----");
                textBox1.AppendText(Environment.NewLine);
                //string[] stringArr = new string[AllLocations.Count()];
                // int count = 0;
                List<string> allLocsStr = new List<string>();
                foreach (KeyValuePair<string, int> entry in allLocations)
                {
                    textBox1.AppendText(entry.Key);
                    textBox1.AppendText(Environment.NewLine);
                    //stringArr[count++] = entry.Key; 
                    allLocsStr.Add(entry.Key);

                }
                /*textBox1.AppendText("Locations:----");
                textBox1.AppendText(Environment.NewLine);
                for (int x = 0; x < stringArr.Length; x++)
                {
                    textBox1.AppendText(stringArr[x]);
                    textBox1.AppendText(Environment.NewLine);
                }*/
                //System.Windows.Forms.MessageBox.Show("You");
                //System.Windows.Forms.MessageBox.Show(startApplication(true, stringArr, count));
                startApplication(true, allLocsStr.ToArray(), allLocsStr.Count);

            }
            catch (Exception whatType)
            {
                //System.Windows.Forms.MessageBox.Show(GetExceptionDetails(whatType));
            }
            
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text == "") { }
            else
            {
                Globals.lastStringTB = textBox1.Text;
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
           
        }

        string GetExceptionDetails(Exception exception)
        {
            PropertyInfo[] properties = exception.GetType()
                                    .GetProperties();
            List<string> fields = new List<string>();
            foreach (PropertyInfo property in properties)
            {
                object value = property.GetValue(exception, null);
                fields.Add(String.Format(
                                 "{0} = {1}",
                                 property.Name,
                                 value != null ? value.ToString() : String.Empty
                ));
            }
            return String.Join("\n", fields.ToArray());
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Quit button
            Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //Show currently loaded locations
            textBox1.Text = String.Empty;
            textBox1.AppendText("Locations:----");
            textBox1.AppendText(Environment.NewLine);
            foreach (KeyValuePair<string, int> entry in allLocations)
            {
                textBox1.AppendText(entry.Key);
                textBox1.AppendText(Environment.NewLine);
              
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string message = "Hello there! Welcome to the SortToFolder Readme.\n If you want to add locations to the configuration first load them using \"Show current Locations\" thereafter appending the list by clicking Set Sort Locations";
            string message2 = "\n You can quit by exiting normally or hitting the quit button, and sort the locations by clicking the sort data button";
            System.Windows.Forms.MessageBox.Show(message + message2);
        }
    }



}
