#pragma once
#include <fstream>
#include <string>
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
				ava_trig_count=0;
				cur_trig_count=0;
				combo_objects->SelectedIndex=DOOR;
				fill_arrays_with_data();
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
	private: System::Windows::Forms::Button^  button_remove_opener;
	private: System::Windows::Forms::Button^  button_add_opener;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label_tileY;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label_tileX;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label_posx;
	private: System::Windows::Forms::Label^  label_posy;

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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label_posx = (gcnew System::Windows::Forms::Label());
			this->label_posy = (gcnew System::Windows::Forms::Label());
			this->label_tileY = (gcnew System::Windows::Forms::Label());
			this->label_tileX = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->button_add_opener = (gcnew System::Windows::Forms::Button());
			this->button_remove_opener = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panel_door->SuspendLayout();
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
			this->panel_door->Controls->Add(this->label5);
			this->panel_door->Controls->Add(this->label4);
			this->panel_door->Controls->Add(this->button_remove_opener);
			this->panel_door->Controls->Add(this->button_add_opener);
			this->panel_door->Controls->Add(this->listBox2);
			this->panel_door->Controls->Add(this->listBox1);
			this->panel_door->Controls->Add(this->label_tileY);
			this->panel_door->Controls->Add(this->label6);
			this->panel_door->Controls->Add(this->label_tileX);
			this->panel_door->Controls->Add(this->label7);
			this->panel_door->Location = System::Drawing::Point(12, 55);
			this->panel_door->Name = L"panel_door";
			this->panel_door->Size = System::Drawing::Size(283, 153);
			this->panel_door->TabIndex = 2;
			this->panel_door->Visible = false;
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
			// label_tileY
			// 
			this->label_tileY->AutoSize = true;
			this->label_tileY->Location = System::Drawing::Point(230, 28);
			this->label_tileY->Name = L"label_tileY";
			this->label_tileY->Size = System::Drawing::Size(35, 13);
			this->label_tileY->TabIndex = 10;
			this->label_tileY->Text = L"label4";
			// 
			// label_tileX
			// 
			this->label_tileX->AutoSize = true;
			this->label_tileX->Location = System::Drawing::Point(171, 28);
			this->label_tileX->Name = L"label_tileX";
			this->label_tileX->Size = System::Drawing::Size(35, 13);
			this->label_tileX->TabIndex = 9;
			this->label_tileX->Text = L"label4";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(227, 9);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(52, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"For TileY:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(168, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(52, 13);
			this->label7->TabIndex = 7;
			this->label7->Text = L"For TileX:";
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
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Test3", L"Test4"});
			this->listBox2->Location = System::Drawing::Point(104, 28);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(60, 121);
			this->listBox2->TabIndex = 12;
			// 
			// button_add_opener
			// 
			this->button_add_opener->Location = System::Drawing::Point(70, 47);
			this->button_add_opener->Name = L"button_add_opener";
			this->button_add_opener->Size = System::Drawing::Size(28, 23);
			this->button_add_opener->TabIndex = 13;
			this->button_add_opener->Text = L">>";
			this->button_add_opener->UseVisualStyleBackColor = true;
			this->button_add_opener->Click += gcnew System::EventHandler(this, &LevelEditor_objects::button_add_opener_Click);
			// 
			// button_remove_opener
			// 
			this->button_remove_opener->Location = System::Drawing::Point(69, 105);
			this->button_remove_opener->Name = L"button_remove_opener";
			this->button_remove_opener->Size = System::Drawing::Size(28, 23);
			this->button_remove_opener->TabIndex = 14;
			this->button_remove_opener->Text = L"<<";
			this->button_remove_opener->UseVisualStyleBackColor = true;
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
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(94, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(76, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Current Trigers";
			// 
			// LevelEditor_objects
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(307, 220);
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
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
				while(!in.eof())
				{
					std::getline(in,reader);
					type=std::atoi(reader.c_str());
					if(type==LEVER)
					{
						std::getline(in,reader);
						ID = atoi(reader.c_str());
						this->listBox2->Items->Add(String::Format("Lever {0}",ID));
						cur_trig_count++;
					}

				}
				in.close();
				in.open("Levels/LevelEditor/temp1.dat");
				{
					while(!in.eof())
					{
						std::getline(in,reader);
						type=std::atoi(reader.c_str());
						if(type==LEVER)
						{
							std::getline(in,reader);
							ID = atoi(reader.c_str());
							this->listBox1->Items->Add(String::Format("Lever {0}",ID));
							ava_trig_count++;
						}
					}

				}

		   }
	private: System::Void button_add_opener_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			 
			 
			 
			 
			 }
};
}
