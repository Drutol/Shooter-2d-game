#pragma once
#include <fstream>
#include <msclr\marshal_cppstd.h>
namespace LevelEditor {	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SaveForm
	/// </summary>
	public ref class SaveForm : public System::Windows::Forms::Form
	{
	private:
		 MainMenu^ mainMenu1;
		 MenuItem^ fileMenuItem;
		 MenuItem^ openMenuItem;
		 MenuItem^ folderMenuItem;
		 MenuItem^ closeMenuItem;
		 String^ openFileName;
		 String^ folderName;
		 OpenFileDialog^ openFileDialog1;

	public:
		SaveForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SaveForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Button^  button_accept;
	private: System::Windows::Forms::Button^  button_cancel;
	private: System::Windows::Forms::TextBox^  textBox1;




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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_accept = (gcnew System::Windows::Forms::Button());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(49, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Save as:";
			// 
			// button_accept
			// 
			this->button_accept->Enabled = false;
			this->button_accept->Location = System::Drawing::Point(341, 44);
			this->button_accept->Name = L"button_accept";
			this->button_accept->Size = System::Drawing::Size(75, 23);
			this->button_accept->TabIndex = 1;
			this->button_accept->Text = L"Save";
			this->button_accept->UseVisualStyleBackColor = true;
			this->button_accept->Click += gcnew System::EventHandler(this, &SaveForm::Save);
			// 
			// button_cancel
			// 
			this->button_cancel->Location = System::Drawing::Point(259, 44);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(75, 23);
			this->button_cancel->TabIndex = 2;
			this->button_cancel->Text = L"Cancel";
			this->button_cancel->UseVisualStyleBackColor = true;
			this->button_cancel->Click += gcnew System::EventHandler(this, &SaveForm::button_cancel_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(69, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(265, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &SaveForm::textBox1_TextChanged);
			// 
			// SaveForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(427, 79);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button_cancel);
			this->Controls->Add(this->button_accept);
			this->Controls->Add(this->label1);
			this->Name = L"SaveForm";
			this->Text = L"SaveForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
public: String^ path;
private: System::Void Save(System::Object^  sender, System::EventArgs^  e) 
		 {
			 path=textBox1->Text;
			 std::string converted_path;
			 msclr::interop::marshal_context context;
			 converted_path = context.marshal_as<std::string>(path);

			 std::ofstream out("Levels/LevelEditor/temp.dat");
			 out<<"CustomMaps/"+converted_path;
			 out.close();
			 std::exit(1);
		 
		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
		 	     if(textBox1->TextLength>0)
					 button_accept->Enabled=true;
				 else
					 button_accept->Enabled=false;
		 }
private: System::Void button_cancel_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 std::exit(-1);
		 }
};
}
