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
				int x,y,ID,held_object,passable;
				x=System::Convert::ToInt32(arg[1]);
				y=System::Convert::ToInt32(arg[2]);
				passable=System::Convert::ToInt32(arg[3]);
				held_object=System::Convert::ToInt32(arg[4]);
				ID=System::Convert::ToInt32(arg[5]);
				int bitmap=1;
				if(arg[6]=="dirt")
				{
					bitmap=DIRT;
				}
				else if(arg[6]=="dirt_back")
				{
					bitmap=DIRT_BACK;

				}
				else if(arg[6]=="dirt_back_up")
				{
					bitmap=DIRT_BACK_UP;

				}
				else if(arg[6]=="dirt_back_down")
				{
					bitmap=DIRT_BACK_DOWN;

				}
				
				image_path="Resources/"+arg[6]+".png";
				bitmap_ID=bitmap;
				this->label_tile_x->Text=arg[0];
				this->label_tile_y->Text=arg[1];
				if(passable==1)
					box_passable->Checked=true;
				else
					box_passable->Checked=false;
				this->box_bitmap->SelectedIndex=bitmap;
				this->bitmap_box->ImageLocation=image_path;
			}
			else if(arg[0]=="HELP")
			{
				panel_help->Visible=true;
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
	private: System::Windows::Forms::Label^  label_held_ID;
	private: System::Windows::Forms::Label^  label_held_object;
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
			this->OK_OF_DOOM->Location = System::Drawing::Point(84, 124);
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
			this->panel_help->Size = System::Drawing::Size(251, 135);
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
			this->button_help_OK->Location = System::Drawing::Point(85, 101);
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
			this->ClientSize = System::Drawing::Size(269, 157);
			this->Controls->Add(this->panel_help);
			this->Controls->Add(this->bitmap_box);
			this->Controls->Add(this->OK_OF_DOOM);
			this->Controls->Add(this->label_held_object);
			this->Controls->Add(this->label_held_ID);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->box_bitmap);
			this->Controls->Add(this->label_tile_y);
			this->Controls->Add(this->label_tile_x);
			this->Controls->Add(this->box_passable);
			this->Name = L"LevelEditor";
			this->Text = L"LevelEditor";
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
