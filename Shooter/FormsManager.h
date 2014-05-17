#pragma once
#include "ComponentButton.h"
class ComponentButton;
enum FORM_TRIGGERS{TRIGGER_KEYPRESS};
enum FORM_TRIGGERS_CONDITIONS{CONDITION_GAME_RUNNING};
enum FORM_EVENTS{EVENT_CURSOR_START_OVERLAPING,EVENT_CURSOR_STOP_OVERLAPING};
struct form
{
	string name;
	int ID;
	int PosX, PosY, width, height;
	std::vector<ComponentButton> buttons;
	int trigger;
	std::vector<int> trigger_conditions;

};
class FormsManager
{
private:


public:
	FormsManager();
	~FormsManager();
	std::vector<form> forms;
	std::vector<string> get_all_files_names_within_folder(string folder);
	void tokenize(string string_to_tokenize,std::vector<string> &atributes);
	void RegisterComponentButton(vector<string> attributes, form &created_form);
	void RegisterFormTrigger(vector<string> attributes, form &created_form);
	void RegisterFormTriggerConditions(vector<string> attributes, form &created_form);

	vector<form> LoadForms();
};

void disable_form(int form_to_be_disabled_ID);
void enable_form(int form_to_be_enabled_ID);