#pragma once
#include "GameFunctions.h"
#include "ComponentButton.h"
#include "ComponentTextBox.h"
class ComponentButton;
class ComponentTextBox;
enum FORM_TRIGGERS{TRIGGER_KEYPRESS};
enum FORM_TRIGGERS_CONDITIONS{CONDITION_GAME_RUNNING};
enum FORM_EVENTS{EVENT_CURSOR_START_OVERLAPING,EVENT_CURSOR_STOP_OVERLAPING,GUI_KEY_PRESS};



struct form
{
	string name;
	int ID;
	int PosX, PosY, width, height;
	std::vector<ComponentButton> buttons;
	std::vector<ComponentTextBox> text_boxes;
	int trigger;
	std::vector<int> trigger_conditions;
	bool is_main;
};
struct gui_event
{
	int MouseX, MouseY, key;
};
class FormsManager
{
private:
	form *startup_form;
	gui_event collected_data;
	int prevMousePosX, prevMousePosY;
	bool is_form_enabled;
	
	

public:
	FormsManager();
	~FormsManager();
	std::vector<form> forms;
	std::vector<string> get_all_files_names_within_folder(string folder);
	void tokenize(string string_to_tokenize,std::vector<string> &atributes);
	void RegisterComponentButton(vector<string> attributes, form &created_form);
	void RegisterFormTrigger(vector<string> attributes, form &created_form);
	void RegisterFormTriggerConditions(vector<string> attributes, form &created_form);
	void RegisterComponentTextBox(vector<string> attributes, form &created_form);
	void evaluate_input(gui_event event_pkg);
	void SendEventInfoToForm(std::vector<int> info);
	int search_for_main_form();
	vector<form*> currently_enabled_forms;
	void draw_forms(); 
	void LoadForms();
	vector<int> free_form_IDs;
};

void disable_form(int form_to_be_disabled_ID);
void enable_form(int form_to_be_enabled_ID);