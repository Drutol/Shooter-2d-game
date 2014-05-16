#pragma once
#include "ComponentButton.h"
struct form
{
	string name;
	int ID;
	std::vector<ComponentButton> buttons;

};
class FormsManager
{
private:
	ComponentButton button;


public:
	FormsManager();
	~FormsManager();
	std::vector<form> forms;
	std::vector<string> get_all_files_names_within_folder(string folder);
	std::vector<string> tokenize(string string_to_tokenize);
	void RegisterComponentButton(vector<string> attributes, form &created_form);


	vector<form> LoadForms();
};

void disable_form();//(form form_to_be_disabled);
void enable_form(form form_to_be_enabled);