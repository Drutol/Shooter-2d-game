#include "LevelEditor.h"
#include "SaveForm.h"
#include "LevelEditor_objects.h"
#include <stdexcept> 
using namespace System;
using namespace System ::Windows::Forms;
void main(array<String^>^ arg) 
{
	
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	if(arg->Length==0)
	{
		MessageBox::Show("This program is not intended to run separatedly");
		std::exit(0);
	}
	else if(arg[0]=="Save")
	{
		LevelEditor::SaveForm form;
		Application::Run(%form);
	}
	else if(arg[0]=="Tile"||arg[0]=="Help")
	{
		LevelEditor::LevelEditor form(arg);	
		Application::Run(%form);
	}
	else if(arg[0]=="Object")
	{
		LevelEditor::LevelEditor_objects form(arg);
		Application::Run(%form);

	}
}