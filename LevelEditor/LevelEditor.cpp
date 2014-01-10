#include "LevelEditor.h"


using namespace System;
using namespace System ::Windows::Forms;
void main(array<String^>^ arg) 
{
	
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	LevelEditor::LevelEditor form(arg);
	Application::Run(%form);
}