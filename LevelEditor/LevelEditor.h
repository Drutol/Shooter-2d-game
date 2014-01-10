#pragma once
#include <string>
#include <stdlib.h>
#include <fstream>


value struct tile
{
	int x;
	int y;
	bool passable;
	int held_object;
	int held_object_ID;
	int bitmap_num;
};

namespace LevelEditor {
	enum tile_objects {NOTHING,DOOR,LEVER,BOX};
	enum bitmaps {DIRT,DIRT_BACK,DIRT_BACK_DOWN,DIRT_BACK_UP};
	int bitmap_ID;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LevelEditor
	/// </summary>
	public ref class LevelEditor : public System::Windows::Forms::Form
	{
	public:
		String^ image_path;
		tile tile_to_return;
	private: System::Windows::Forms::Panel^  panel_help;
	public: 
	private: System::Windows::Forms::Button^  button_help_OK;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;


	public:
		LevelEditor(array<String^>^ arg)
		{
			InitializeComponent();
			if(arg[0]!="Help")
			{
				///Constructor
				this->panel_help->Visible=false;
				this->door_set_up->Visible=false;
				int x,y,ID,held_object,passable;
				x=System::Convert::ToInt32(arg[0]);
				y=System::Convert::ToInt32(arg[1]);
				passable=System::Convert::ToInt32(arg[2]);
				held_object=System::Convert::ToInt32(arg[3]);
				ID=System::Convert::ToInt32(arg[4]);
				int bitmap=1;
				if(arg[5]=="dirt")
				{
					bitmap=DIRT;
				}
				else if(arg[5]=="dirt_back")
				{
					bitmap=DIRT_BACK;

				}
				else if(arg[5]=="dirt_back_up")
				{
					bitmap=DIRT_BACK_UP;

				}
				else if(arg[5]=="dirt_back_down")
				{
					bitmap=DIRT_BACK_DOWN;

				}
				
				image_path="Resources/"+arg[5]+".png";
				bitmap_ID=bitmap;
				this->label_tile_x->Text=arg[0];
				this->label_tile_y->Text=arg[1];
				if(passable==1)
					box_passable->Checked=true;
				else
					box_passable->Checked=false;
				this->box_bitmap->SelectedIndex=bitmap;
				this->box_object->SelectedIndex=held_object;
				this->bitmap_box->ImageLocation=image_path;
			}
			else if(arg[0]=="HELP")
			{
				panel_help->Visible=true;
			}
			if(arg[0]->Empty)
			{
				Close();
			}
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LevelEditor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^  box_passable;
	protected: 
	private: System::Windows::Forms::Label^  label_tile_x;
	private: System::Windows::Forms::Label^  label_tile_y;
	private: System::Windows::Forms::ComboBox^  box_bitmap;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  box_object;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  door_set_up;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  text_door_speed;


	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  door_opened_by;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::ComboBox^  box_door_dir;

	private: System::Windows::Forms::Label^  label_held_ID;
	private: System::Windows::Forms::Label^  label_held_object;
	private: System::Windows::Forms::Label^  label_door_ID_add;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::Button^  button_door_delete;
	private: System::Windows::Forms::Button^  button_door_add;
	private: System::Windows::Forms::Button^  OK_OF_DOOM;
	private: System::Windows::Forms::PictureBox^  bitmap_box;


	protected: 

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
			this->box_passable = (gcnew System::Windows::Forms::CheckBox());
			this->label_tile_x = (gcnew System::Windows::Forms::Label());
			this->label_tile_y = (gcnew System::Windows::Forms::Label());
			this->box_bitmap = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->box_object = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->door_set_up = (gcnew System::Windows::Forms::Panel());
			this->label_door_ID_add = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->button_door_delete = (gcnew System::Windows::Forms::Button());
			this->button_door_add = (gcnew System::Windows::Forms::Button());
			this->door_opened_by = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->box_door_dir = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->text_door_speed = (gcnew System::Windows::Forms::TextBox());
			this->label_held_ID = (gcnew System::Windows::Forms::Label());
			this->label_held_object = (gcnew System::Windows::Forms::Label());
			this->OK_OF_DOOM = (gcnew System::Windows::Forms::Button());
			this->bitmap_box = (gcnew System::Windows::Forms::PictureBox());
			this->panel_help = (gcnew System::Windows::Forms::Panel());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->button_help_OK = (gcnew System::Windows::Forms::Button());
			this->door_set_up->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bitmap_box))->BeginInit();
			this->panel_help->SuspendLayout();
			this->SuspendLayout();
			// 
			// box_passable
			// 
			this->box_passable->AutoSize = true;
			this->box_passable->Location = System::Drawing::Point(192, 12);
			this->box_passable->Name = L"box_passable";
			this->box_passable->Size = System::Drawing::Size(69, 17);
			this->box_passable->TabIndex = 0;
			this->box_passable->Text = L"Passable";
			this->box_passable->UseVisualStyleBackColor = true;
			// 
			// label_tile_x
			// 
			this->label_tile_x->AutoSize = true;
			this->label_tile_x->Location = System::Drawing::Point(13, 12);
			this->label_tile_x->Name = L"label_tile_x";
			this->label_tile_x->Size = System::Drawing::Size(37, 13);
			this->label_tile_x->TabIndex = 1;
			this->label_tile_x->Text = L"Tile X:";
			// 
			// label_tile_y
			// 
			this->label_tile_y->AutoSize = true;
			this->label_tile_y->Location = System::Drawing::Point(71, 12);
			this->label_tile_y->Name = L"label_tile_y";
			this->label_tile_y->Size = System::Drawing::Size(37, 13);
			this->label_tile_y->TabIndex = 2;
			this->label_tile_y->Text = L"Tile Y:";
			// 
			// box_bitmap
			// 
			this->box_bitmap->FormattingEnabled = true;
			this->box_bitmap->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"dirt", L"dirt_back", L"dirt_back_down", L"dirt_back_up"});
			this->box_bitmap->Location = System::Drawing::Point(140, 53);
			this->box_bitmap->Name = L"box_bitmap";
			this->box_bitmap->Size = System::Drawing::Size(121, 21);
			this->box_bitmap->TabIndex = 3;
			this->box_bitmap->SelectedIndexChanged += gcnew System::EventHandler(this, &LevelEditor::Reload_Bitmap);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(140, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Bitmap:";
			// 
			// box_object
			// 
			this->box_object->FormattingEnabled = true;
			this->box_object->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"nothing", L"lever", L"door", L"box"});
			this->box_object->Location = System::Drawing::Point(140, 97);
			this->box_object->Name = L"box_object";
			this->box_object->Size = System::Drawing::Size(121, 21);
			this->box_object->TabIndex = 5;
			this->box_object->SelectedIndexChanged += gcnew System::EventHandler(this, &LevelEditor::comboBox2_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(143, 81);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Object:";
			this->label2->Click += gcnew System::EventHandler(this, &LevelEditor::label2_Click);
			// 
			// door_set_up
			// 
			this->door_set_up->Controls->Add(this->label_door_ID_add);
			this->door_set_up->Controls->Add(this->label7);
			this->door_set_up->Controls->Add(this->comboBox3);
			this->door_set_up->Controls->Add(this->button_door_delete);
			this->door_set_up->Controls->Add(this->button_door_add);
			this->door_set_up->Controls->Add(this->door_opened_by);
			this->door_set_up->Controls->Add(this->label6);
			this->door_set_up->Controls->Add(this->checkBox1);
			this->door_set_up->Controls->Add(this->box_door_dir);
			this->door_set_up->Controls->Add(this->label5);
			this->door_set_up->Controls->Add(this->label4);
			this->door_set_up->Controls->Add(this->label3);
			this->door_set_up->Controls->Add(this->text_door_speed);
			this->door_set_up->Location = System::Drawing::Point(10, 143);
			this->door_set_up->Name = L"door_set_up";
			this->door_set_up->Size = System::Drawing::Size(250, 160);
			this->door_set_up->TabIndex = 7;
			// 
			// label_door_ID_add
			// 
			this->label_door_ID_add->AutoSize = true;
			this->label_door_ID_add->Location = System::Drawing::Point(130, 59);
			this->label_door_ID_add->Name = L"label_door_ID_add";
			this->label_door_ID_add->Size = System::Drawing::Size(47, 13);
			this->label_door_ID_add->TabIndex = 14;
			this->label_door_ID_add->Text = L"Door ID:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(110, 87);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(106, 13);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Currently Opened by:";
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(110, 103);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(92, 21);
			this->comboBox3->TabIndex = 12;
			// 
			// button_door_delete
			// 
			this->button_door_delete->Location = System::Drawing::Point(168, 130);
			this->button_door_delete->Name = L"button_door_delete";
			this->button_door_delete->Size = System::Drawing::Size(34, 24);
			this->button_door_delete->TabIndex = 11;
			this->button_door_delete->Text = L"Del";
			this->button_door_delete->UseVisualStyleBackColor = true;
			// 
			// button_door_add
			// 
			this->button_door_add->Location = System::Drawing::Point(69, 130);
			this->button_door_add->Name = L"button_door_add";
			this->button_door_add->Size = System::Drawing::Size(34, 24);
			this->button_door_add->TabIndex = 10;
			this->button_door_add->Text = L"Add";
			this->button_door_add->UseVisualStyleBackColor = true;
			// 
			// door_opened_by
			// 
			this->door_opened_by->FormattingEnabled = true;
			this->door_opened_by->Location = System::Drawing::Point(7, 104);
			this->door_opened_by->Name = L"door_opened_by";
			this->door_opened_by->Size = System::Drawing::Size(96, 21);
			this->door_opened_by->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(4, 87);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(50, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Open by:";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(130, 21);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(86, 17);
			this->checkBox1->TabIndex = 6;
			this->checkBox1->Text = L"Initially Open";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// box_door_dir
			// 
			this->box_door_dir->FormattingEnabled = true;
			this->box_door_dir->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"UP", L"DOWN"});
			this->box_door_dir->Location = System::Drawing::Point(6, 59);
			this->box_door_dir->Name = L"box_door_dir";
			this->box_door_dir->Size = System::Drawing::Size(97, 21);
			this->box_door_dir->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 42);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(52, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Direction:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 3);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(41, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Speed:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 42);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 2;
			// 
			// text_door_speed
			// 
			this->text_door_speed->Location = System::Drawing::Point(3, 19);
			this->text_door_speed->Name = L"text_door_speed";
			this->text_door_speed->Size = System::Drawing::Size(100, 20);
			this->text_door_speed->TabIndex = 0;
			// 
			// label_held_ID
			// 
			this->label_held_ID->AutoSize = true;
			this->label_held_ID->Location = System::Drawing::Point(14, 29);
			this->label_held_ID->Name = L"label_held_ID";
			this->label_held_ID->Size = System::Drawing::Size(46, 13);
			this->label_held_ID->TabIndex = 8;
			this->label_held_ID->Text = L"Held ID:";
			// 
			// label_held_object
			// 
			this->label_held_object->AutoSize = true;
			this->label_held_object->Location = System::Drawing::Point(71, 29);
			this->label_held_object->Name = L"label_held_object";
			this->label_held_object->Size = System::Drawing::Size(63, 13);
			this->label_held_object->TabIndex = 9;
			this->label_held_object->Text = L"Held Object";
			// 
			// OK_OF_DOOM
			// 
			this->OK_OF_DOOM->Location = System::Drawing::Point(94, 313);
			this->OK_OF_DOOM->Name = L"OK_OF_DOOM";
			this->OK_OF_DOOM->Size = System::Drawing::Size(75, 23);
			this->OK_OF_DOOM->TabIndex = 10;
			this->OK_OF_DOOM->Text = L"OK";
			this->OK_OF_DOOM->UseVisualStyleBackColor = true;
			this->OK_OF_DOOM->Click += gcnew System::EventHandler(this, &LevelEditor::Submit_data);
			// 
			// bitmap_box
			// 
			this->bitmap_box->Location = System::Drawing::Point(44, 54);
			this->bitmap_box->Name = L"bitmap_box";
			this->bitmap_box->Size = System::Drawing::Size(64, 64);
			this->bitmap_box->TabIndex = 12;
			this->bitmap_box->TabStop = false;
			// 
			// panel_help
			// 
			this->panel_help->Controls->Add(this->label13);
			this->panel_help->Controls->Add(this->label12);
			this->panel_help->Controls->Add(this->label11);
			this->panel_help->Controls->Add(this->label10);
			this->panel_help->Controls->Add(this->label9);
			this->panel_help->Controls->Add(this->label8);
			this->panel_help->Controls->Add(this->button_help_OK);
			this->panel_help->Location = System::Drawing::Point(10, 12);
			this->panel_help->Name = L"panel_help";
			this->panel_help->Size = System::Drawing::Size(251, 324);
			this->panel_help->TabIndex = 15;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(16, 100);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(0, 13);
			this->label13->TabIndex = 6;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(10, 85);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(120, 13);
			this->label12->TabIndex = 5;
			this->label12->Text = L"4.To Save map press M";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(10, 66);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(167, 13);
			this->label11->TabIndex = 4;
			this->label11->Text = L"3.To edit existing object fress on it";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(10, 49);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(185, 13);
			this->label10->TabIndex = 3;
			this->label10->Text = L"2.To add object click on empty space";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(10, 34);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(137, 13);
			this->label9->TabIndex = 2;
			this->label9->Text = L"1.To change tile press LMB";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(7, 16);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(38, 13);
			this->label8->TabIndex = 1;
			this->label8->Text = L"HELP:";
			// 
			// button_help_OK
			// 
			this->button_help_OK->Location = System::Drawing::Point(87, 272);
			this->button_help_OK->Name = L"button_help_OK";
			this->button_help_OK->Size = System::Drawing::Size(75, 23);
			this->button_help_OK->TabIndex = 0;
			this->button_help_OK->Text = L"OK";
			this->button_help_OK->UseVisualStyleBackColor = true;
			this->button_help_OK->Click += gcnew System::EventHandler(this, &LevelEditor::button_help_OK_Click);
			// 
			// LevelEditor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(272, 348);
			this->Controls->Add(this->panel_help);
			this->Controls->Add(this->bitmap_box);
			this->Controls->Add(this->OK_OF_DOOM);
			this->Controls->Add(this->label_held_object);
			this->Controls->Add(this->label_held_ID);
			this->Controls->Add(this->door_set_up);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->box_object);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->box_bitmap);
			this->Controls->Add(this->label_tile_y);
			this->Controls->Add(this->label_tile_x);
			this->Controls->Add(this->box_passable);
			this->Name = L"LevelEditor";
			this->Text = L"LevelEditor";
			this->door_set_up->ResumeLayout(false);
			this->door_set_up->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bitmap_box))->EndInit();
			this->panel_help->ResumeLayout(false);
			this->panel_help->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
			 
			 
			 
			 }
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		 {
			 if(this->box_object->SelectedIndex==1)
				 this->door_set_up->Visible=true;
			 else if(this->box_object->SelectedIndex==0)
				 this->door_set_up->Visible=false;
		 }
private: System::Void Submit_data(System::Object^  sender, System::EventArgs^  e) 
		 {
			 tile_to_return.x=System::Convert::ToInt32(label_tile_x->Text);
			 tile_to_return.y=System::Convert::ToInt32(label_tile_y->Text);
			 tile_to_return.passable=box_passable->Checked;
			 tile_to_return.held_object=NOTHING;
			 tile_to_return.held_object_ID=0;
			 tile_to_return.bitmap_num=bitmap_ID;
			 std::ofstream out("Levels/LevelEditor/temp.dat");
			 out<<tile_to_return.x<<std::endl<<tile_to_return.y<<std::endl<<tile_to_return.passable<<std::endl<<tile_to_return.held_object<<std::endl<<
				 tile_to_return.held_object_ID<<std::endl<<tile_to_return.bitmap_num<<std::endl;

			 LevelEditor::Close();
		 }

private: System::Void Reload_Bitmap(System::Object^  sender, System::EventArgs^  e) 
		{
					if(this->box_bitmap->SelectedIndex==DIRT)
					{
						image_path="Resources/dirt.png";
						bitmap_ID=DIRT;
					}
					else if(this->box_bitmap->SelectedIndex==DIRT_BACK)
					{
						image_path="Resources/dirt_back.png";
						bitmap_ID=DIRT_BACK;
					}
					else if(this->box_bitmap->SelectedIndex==DIRT_BACK_DOWN)
					{
						image_path="Resources/dirt_back_down.png";
						bitmap_ID=DIRT_BACK_DOWN;
					}
					else if(this->box_bitmap->SelectedIndex==DIRT_BACK_UP)
					{
						image_path="Resources/dirt_back_up.png";
						bitmap_ID=DIRT_BACK_UP;
					}

					try
					{
						bitmap_box->ImageLocation=image_path;
					}
					catch(System::IO::FileNotFoundException^)
					{
						std::exit(-99);
					}
				 
		}
private: System::Void button_help_OK_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Close();
		 }
};
	

}
