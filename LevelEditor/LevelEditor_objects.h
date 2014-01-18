#pragma once
#include <fstream>
#include <string>
#include <msclr\marshal_cppstd.h>
enum tile_objects {NOTHING,DOOR,LEVER,BOX};
value struct data_package
{


};
namespace LevelEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LevelEditor_objects
	/// </summary>
	public ref class LevelEditor_objects : public System::Windows::Forms::Form
	{
	public:
		LevelEditor_objects(array<String^>^ arg)
		{
			InitializeComponent();
			if(arg[1]=="Door")
			{
				panel_door->Visible=true;
				label_posx->Text=arg[2];
				label_posy->Text=arg[3];
				combo_objects->SelectedIndex=DOOR;
				combo_objects->Enabled=false;
				fill_arrays_with_data();
				numeric_tileX->Value=System::Convert::ToInt32(arg[2])/64;
				numeric_tileY->Value=System::Convert::ToInt32(arg[3])/64;
				numeric_speed->Value=System::Convert::ToInt32(arg[4]);
				checkBox_InitialState->Checked=System::Convert::ToInt32(arg[5]);
				comboBox1->SelectedIndex=System::Convert::ToInt32(arg[6])-1;
				numeric_tileX->Enabled=false;
				numeric_tileY->Enabled=false;
				triggers_changed=false;
				label_listbox_info->Visible=false;
			}
			else if(arg[1]=="Create")
			{
				panel_door->Visible=false;
				creation=true;
				listBox1->Enabled=false;
				listBox2->Enabled=false;
				label_listbox_info->Visible=true;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LevelEditor_objects()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  combo_objects;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  panel_door;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button_remove_trigger;

	private: System::Windows::Forms::Button^  button_add_trigger;

	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::ListBox^  listBox1;

	private: System::Windows::Forms::Label^  label6;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label_posx;
	private: System::Windows::Forms::Label^  label_posy;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::NumericUpDown^  numeric_speed;
	private: System::Windows::Forms::CheckBox^  checkBox_InitialState;
	private: System::Windows::Forms::Button^  button_submit_door;
	private: System::Windows::Forms::Button^  button_cancel;
	private: System::Windows::Forms::NumericUpDown^  numeric_tileY;
	private: System::Windows::Forms::NumericUpDown^  numeric_tileX;
	private: System::Windows::Forms::Label^  label_listbox_info;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->combo_objects = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel_door = (gcnew System::Windows::Forms::Panel());
			this->label_listbox_info = (gcnew System::Windows::Forms::Label());
			this->numeric_tileY = (gcnew System::Windows::Forms::NumericUpDown());
			this->numeric_tileX = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->numeric_speed = (gcnew System::Windows::Forms::NumericUpDown());
			this->checkBox_InitialState = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button_submit_door = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button_remove_trigger = (gcnew System::Windows::Forms::Button());
			this->button_add_trigger = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label_posx = (gcnew System::Windows::Forms::Label());
			this->label_posy = (gcnew System::Windows::Forms::Label());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->panel_door->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numeric_tileY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numeric_tileX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numeric_speed))->BeginInit();
			this->SuspendLayout();
			// 
			// combo_objects
			// 
			this->combo_objects->FormattingEnabled = true;
			this->combo_objects->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Nothing", L"Door", L"Lever"});
			this->combo_objects->Location = System::Drawing::Point(12, 27);
			this->combo_objects->Name = L"combo_objects";
			this->combo_objects->Size = System::Drawing::Size(121, 21);
			this->combo_objects->TabIndex = 0;
			this->combo_objects->SelectedIndexChanged += gcnew System::EventHandler(this, &LevelEditor_objects::combo_objects_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Current Object";
			// 
			// panel_door
			// 
			this->panel_door->Controls->Add(this->label_listbox_info);
			this->panel_door->Controls->Add(this->numeric_tileY);
			this->panel_door->Controls->Add(this->numeric_tileX);
			this->panel_door->Controls->Add(this->label9);
			this->panel_door->Controls->Add(this->comboBox1);
			this->panel_door->Controls->Add(this->label8);
			this->panel_door->Controls->Add(this->numeric_speed);
			this->panel_door->Controls->Add(this->checkBox_InitialState);
			this->panel_door->Controls->Add(this->label5);
			this->panel_door->Controls->Add(this->button_submit_door);
			this->panel_door->Controls->Add(this->label4);
			this->panel_door->Controls->Add(this->button_remove_trigger);
			this->panel_door->Controls->Add(this->button_add_trigger);
			this->panel_door->Controls->Add(this->listBox2);
			this->panel_door->Controls->Add(this->listBox1);
			this->panel_door->Controls->Add(this->label6);
			this->panel_door->Controls->Add(this->label7);
			this->panel_door->Location = System::Drawing::Point(12, 55);
			this->panel_door->Name = L"panel_door";
			this->panel_door->Size = System::Drawing::Size(376, 163);
			this->panel_door->TabIndex = 2;
			this->panel_door->Visible = false;
			// 
			// label_listbox_info
			// 
			this->label_listbox_info->AutoSize = true;
			this->label_listbox_info->Location = System::Drawing::Point(4, 73);
			this->label_listbox_info->Name = L"label_listbox_info";
			this->label_listbox_info->Size = System::Drawing::Size(161, 26);
			this->label_listbox_info->TabIndex = 25;
			this->label_listbox_info->Text = L"To set triggers complete creation\r\nprocess and then edit the door";
			// 
			// numeric_tileY
			// 
			this->numeric_tileY->Location = System::Drawing::Point(301, 92);
			this->numeric_tileY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {19, 0, 0, 0});
			this->numeric_tileY->Name = L"numeric_tileY";
			this->numeric_tileY->Size = System::Drawing::Size(49, 20);
			this->numeric_tileY->TabIndex = 24;
			// 
			// numeric_tileX
			// 
			this->numeric_tileX->Location = System::Drawing::Point(301, 38);
			this->numeric_tileX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {19, 0, 0, 0});
			this->numeric_tileX->Name = L"numeric_tileX";
			this->numeric_tileX->Size = System::Drawing::Size(49, 20);
			this->numeric_tileX->TabIndex = 23;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(171, 75);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(60, 13);
			this->label9->TabIndex = 22;
			this->label9->Text = L"Movement:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"--Choose--", L"Up", L"Down"});
			this->comboBox1->Location = System::Drawing::Point(174, 91);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(97, 21);
			this->comboBox1->TabIndex = 21;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(170, 52);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(41, 13);
			this->label8->TabIndex = 20;
			this->label8->Text = L"Speed:";
			// 
			// numeric_speed
			// 
			this->numeric_speed->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 65536});
			this->numeric_speed->Location = System::Drawing::Point(217, 52);
			this->numeric_speed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			this->numeric_speed->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numeric_speed->Name = L"numeric_speed";
			this->numeric_speed->Size = System::Drawing::Size(61, 20);
			this->numeric_speed->TabIndex = 19;
			this->numeric_speed->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			// 
			// checkBox_InitialState
			// 
			this->checkBox_InitialState->AutoSize = true;
			this->checkBox_InitialState->Location = System::Drawing::Point(174, 28);
			this->checkBox_InitialState->Name = L"checkBox_InitialState";
			this->checkBox_InitialState->Size = System::Drawing::Size(92, 17);
			this->checkBox_InitialState->TabIndex = 18;
			this->checkBox_InitialState->Text = L"Initially Closed";
			this->checkBox_InitialState->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(94, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(76, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Current Trigers";
			// 
			// button_submit_door
			// 
			this->button_submit_door->Location = System::Drawing::Point(292, 137);
			this->button_submit_door->Name = L"button_submit_door";
			this->button_submit_door->Size = System::Drawing::Size(75, 23);
			this->button_submit_door->TabIndex = 17;
			this->button_submit_door->Text = L"OK";
			this->button_submit_door->UseVisualStyleBackColor = true;
			this->button_submit_door->Click += gcnew System::EventHandler(this, &LevelEditor_objects::button_submit_door_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(0, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(85, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"Available Trigers";
			// 
			// button_remove_trigger
			// 
			this->button_remove_trigger->Location = System::Drawing::Point(69, 105);
			this->button_remove_trigger->Name = L"button_remove_trigger";
			this->button_remove_trigger->Size = System::Drawing::Size(28, 23);
			this->button_remove_trigger->TabIndex = 14;
			this->button_remove_trigger->Text = L"<<";
			this->button_remove_trigger->UseVisualStyleBackColor = true;
			this->button_remove_trigger->Click += gcnew System::EventHandler(this, &LevelEditor_objects::button_remove_trigger_Click);
			// 
			// button_add_trigger
			// 
			this->button_add_trigger->Location = System::Drawing::Point(70, 47);
			this->button_add_trigger->Name = L"button_add_trigger";
			this->button_add_trigger->Size = System::Drawing::Size(28, 23);
			this->button_add_trigger->TabIndex = 13;
			this->button_add_trigger->Text = L">>";
			this->button_add_trigger->UseVisualStyleBackColor = true;
			this->button_add_trigger->Click += gcnew System::EventHandler(this, &LevelEditor_objects::button_add_triger_Click);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Test3", L"Test4"});
			this->listBox2->Location = System::Drawing::Point(104, 28);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(60, 121);
			this->listBox2->TabIndex = 12;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Test", L"Test2"});
			this->listBox1->Location = System::Drawing::Point(3, 28);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(60, 121);
			this->listBox1->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(298, 75);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(52, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"For TileY:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(298, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(52, 13);
			this->label7->TabIndex = 7;
			this->label7->Text = L"For TileX:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(137, 8);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"For PosX:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(196, 8);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"For PosY:";
			// 
			// label_posx
			// 
			this->label_posx->AutoSize = true;
			this->label_posx->Location = System::Drawing::Point(140, 27);
			this->label_posx->Name = L"label_posx";
			this->label_posx->Size = System::Drawing::Size(35, 13);
			this->label_posx->TabIndex = 5;
			this->label_posx->Text = L"label4";
			// 
			// label_posy
			// 
			this->label_posy->AutoSize = true;
			this->label_posy->Location = System::Drawing::Point(199, 27);
			this->label_posy->Name = L"label_posy";
			this->label_posy->Size = System::Drawing::Size(35, 13);
			this->label_posy->TabIndex = 6;
			this->label_posy->Text = L"label4";
			// 
			// button_cancel
			// 
			this->button_cancel->Location = System::Drawing::Point(313, 224);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(75, 23);
			this->button_cancel->TabIndex = 18;
			this->button_cancel->Text = L"Cancel";
			this->button_cancel->UseVisualStyleBackColor = true;
			this->button_cancel->Click += gcnew System::EventHandler(this, &LevelEditor_objects::button_cancel_Click);
			// 
			// LevelEditor_objects
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(391, 248);
			this->Controls->Add(this->button_cancel);
			this->Controls->Add(this->label_posy);
			this->Controls->Add(this->label_posx);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panel_door);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->combo_objects);
			this->Name = L"LevelEditor_objects";
			this->panel_door->ResumeLayout(false);
			this->panel_door->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numeric_tileY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numeric_tileX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numeric_speed))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:bool creation;
	public:bool triggers_changed;
	public:array<String^>^ available_triggers;
	public:array<String^>^ current_triggers;
	public:int ava_trig_count,cur_trig_count;
	public:System::Void fill_arrays_with_data()
		   {
			   	this->listBox1->Items->Clear();
				this->listBox2->Items->Clear();
			    std::fstream in("Levels/LevelEditor/temp.dat");
				std::string reader;
				int type,ID;
				if(in.is_open())
				{
					while(!in.eof())
					{
						std::getline(in,reader);
						type=std::atoi(reader.c_str());
						std::getline(in,reader);
						ID = atoi(reader.c_str());
						if(type==LEVER)
						{
							this->listBox2->Items->Add(String::Format("Lever {0}",ID));
						}

					}
					in.close();
				}
				else
				{
					this->button_remove_trigger->Enabled=false;
				}
				in.open("Levels/LevelEditor/temp1.dat");
				if(in.is_open())
					{
					{
						while(!in.eof())
						{
							std::getline(in,reader);
							type=std::atoi(reader.c_str());
							std::getline(in,reader);
							ID = atoi(reader.c_str());
							if(type==LEVER)
							{
								this->listBox1->Items->Add(String::Format("Lever {0}",ID));
							}
						}

					}
				in.close();
				}
				else
				{
					this->button_add_trigger->Enabled=false;
				}
				std::remove("Levels/LevelEditor/temp.dat");
				std::remove("Levels/LevelEditor/temp1.dat");
		   }

private: System::Void button_add_triger_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 if(this->listBox1->SelectedItem != nullptr)
				{
					listBox2->Items->Add(this->listBox1->SelectedItem);
				    listBox1->Items->Remove(listBox1->SelectedItem);
					button_remove_trigger->Enabled=true;
					if(listBox1->Items->Count == 0 )
						button_add_trigger->Enabled=false;
				}
			 triggers_changed=true;
		 }
private: System::Void button_remove_trigger_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(this->listBox2->SelectedItem != nullptr)
				 {
					 listBox1->Items->Add(this->listBox2->SelectedItem);
					 listBox2->Items->Remove(listBox2->SelectedItem);
					 button_add_trigger->Enabled=true;
					 if(listBox2->Items->Count == 0 )
						button_remove_trigger->Enabled=false;
				}
			 triggers_changed=true;
		 }
private: System::Void button_submit_door_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(numeric_speed->Value > 0 && comboBox1->SelectedIndex > 0)
				{
				std::ofstream out("Levels/LevelEditor/temp.dat");
				if(out.is_open())
				{
					out<<System::Convert::ToInt32(numeric_tileX->Value)<<std::endl;
					out<<System::Convert::ToInt32(numeric_tileY->Value)<<std::endl;
					out<<checkBox_InitialState->Checked<<std::endl;
					out<<System::Convert::ToInt32(numeric_speed->Value)<<std::endl;
					out<<comboBox1->SelectedIndex+1;
					out.close();
					if(triggers_changed&&!creation)
					{
						std::string temp;
						msclr::interop::marshal_context context;
						out.open("Levels/LevelEditor/curr_trigs_temp.dat");
						for(int i=0;i<listBox2->Items->Count;i++)
							out<<context.marshal_as<std::string>(listBox2->Items[i]->ToString())<<std::endl;
						out.close();
						out.open("Levels/LevelEditor/ava_trigs_temp.dat");
						for(int i=0;i<listBox1->Items->Count;i++)
							out<<context.marshal_as<std::string>(listBox1->Items[i]->ToString())<<std::endl;
					}
				}
				std::exit(1);
			 }
			 else
			 {
				 MessageBox::Show("Please specify all neccessary options");
			 }
		 }
private: System::Void button_cancel_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 std::exit(0);
		 }
private: System::Void combo_objects_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(combo_objects->SelectedItem->ToString()=="Door")
			 {
				 panel_door->Visible=true;
			 }
			 else
			 {
				 panel_door->Visible=false;
			 }
		 
		 }
};
}
