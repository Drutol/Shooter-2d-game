#include "FormsManager.h"

gui_event container;

void game_end(int with_form=-1)
{
	is_game_running = false;
	with_form != -1 ? disable_form(with_form):NULL;
}


FormsManager::FormsManager()
{
	
	
	this->prevMousePosX = 0;
	this->prevMousePosY = 0;
	this->is_form_enabled = true;
	this->previously_overlapping = false;
	this->done = false;
	main_form = -1;

	
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
	}	
	if (!al_init_primitives_addon()){
		fprintf(stderr, "Couldn't initialize primitives addon!\n");
	}
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	al_init_font_addon();
	al_init_ttf_addon();
	game_font = al_load_font("Resources/leadcoat.ttf", 40, NULL);
	display = al_create_display(ScreenWidth, ScreenHeight);
	
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
	}
	al_install_keyboard();
	al_install_mouse();

	al_init_image_addon();
	shjds = al_load_font("Resources/leadcoat.ttf", 20, NULL);
	LoadForms();
	search_for_main_form();
}


FormsManager::~FormsManager()
{
}

void FormsManager::LoadForms()
{
	std::vector<std::string> forms_found;
	forms_found = get_all_files_names_within_folder("Forma");

	vector<form> output;

	for (int i = 0; i < forms_found.size(); i++)
	{
		std::ifstream in (forms_found[i].c_str());
		if (in.is_open())
		{
			std::string line;
			vector<string> read_attributes;
			form created_form;
			while (!in.eof())
			{
				getline(in, line);
				tokenize(line,read_attributes);

				//Beware almighty switch ...it's on its way

				if (read_attributes[0]=="button")
				{
					RegisterComponentButton(read_attributes, created_form);
				}
				else if (read_attributes[0] == "trigkey")
				{
					RegisterFormTrigger(read_attributes, created_form);
				}
				else if (read_attributes[0] == "Form")
				{
					created_form.name = read_attributes[1];
				}
				else if (read_attributes[0] == "Xpos")
				{
					created_form.PosX = atoi(read_attributes[1].c_str());
				}
				else if (read_attributes[0] == "Ypos")
				{
					created_form.PosY = atoi(read_attributes[1].c_str());
				}
				else if (read_attributes[0] == "Width")
				{
					created_form.width = atoi(read_attributes[1].c_str());
				}
				else if (read_attributes[0] == "Height")
				{
					created_form.height = atoi(read_attributes[1].c_str());
				}
				else if (read_attributes[0] == "conditon")
				{
					RegisterFormTriggerConditions(read_attributes, created_form);
				}
				else if (read_attributes[0] == "MAIN_FORM")
				{
					created_form.is_main = true;
				}
				else if (read_attributes[0] == "Textbox")
				{
					RegisterComponentTextBox(read_attributes, created_form);
				}
				read_attributes.clear();
			}
			
			forms.push_back(created_form);
		}
	}
}

std::vector<string> FormsManager::get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	char search_path[200];
	sprintf_s(search_path, "%s*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void FormsManager::tokenize(string string_to_tokenize,std::vector<string> &attributes)
{
	std::istringstream f(string_to_tokenize);
	std::string s;
	while (std::getline(f, s, '='))
	{
		attributes.push_back(s);
	}
}

void FormsManager::RegisterComponentButton(vector<string> attributes, form &created_form)
{
	void(*disabling_function)(int) = &disable_form;
	void(*exit_function)(void) = &kill_player;
	
	void(*function_to_pass_int)(int);
	void(*function_to_pass_void)(void);


	int PosX, PosY, key;
	short r, g, b;
	int font_size;
	if (!created_form.is_main)
	{
		PosX = atoi(attributes[1].c_str()) + created_form.PosX;
		PosY = atoi(attributes[2].c_str()) + created_form.PosY;
	}
	else
	{
		PosX = atoi(attributes[1].c_str());
		PosY = atoi(attributes[2].c_str());
	}


	r = atoi(attributes[4].c_str());
	g = atoi(attributes[5].c_str());
	b = atoi(attributes[6].c_str());

	font_size = atoi(attributes[7].c_str());

	if (attributes[3] == "RESUME")
	{
			created_form.buttons.push_back(ComponentButton(&disable_form, PosX, PosY, this->forms.size() - 1, attributes[8], al_map_rgb(r, g, b), forms.empty() ? 0 : forms.size(),font_size));	
	}
	else if (attributes[3] == "EXIT"&&!created_form.is_main)
	{
		created_form.buttons.push_back(ComponentButton(&game_end, PosX, PosY, forms.size(), attributes[8], al_map_rgb(r, g, b), forms.size(),font_size));
	}
	else if (attributes[3] == "Exit"&&created_form.is_main)
	{
		function_to_pass_int = &std::exit;
		created_form.buttons.push_back(ComponentButton(function_to_pass_int, PosX, PosY, this->forms.size() - 1, attributes[8], al_map_rgb(r, g, b), 125, font_size));
	}
	else if (attributes[3] == "Start")
	{
		function_to_pass_void = &main_game;
		created_form.buttons.push_back(ComponentButton(function_to_pass_void, PosX, PosY, this->forms.size() - 1, attributes[8], al_map_rgb(r, g, b), font_size));
	}
	else if (attributes[3] == "Level Editor")
	{
		function_to_pass_void = &level_editor;
		created_form.buttons.push_back(ComponentButton(function_to_pass_void, PosX, PosY, this->forms.size() - 1, attributes[8], al_map_rgb(r, g, b), font_size));
	}




}

void FormsManager::RegisterFormTrigger(vector<string> attributes, form &created_form)
{
	int trigger;
	int trigger_value;
	if (attributes[0] == "trigkey")
	{
		trigger = TRIGGER_KEYPRESS;
	}
	if (attributes[1] == "ESC")
	{
		trigger_value = ALLEGRO_KEY_ESCAPE;
	}
	else if (attributes[1] == "P")
	{
		trigger_value = ALLEGRO_KEY_P;
	}

	created_form.trigger = trigger;
	created_form.trigger_conditions.push_back(trigger_value);

}

void FormsManager::RegisterFormTriggerConditions(vector<string> attributes, form &created_form)
{
	if (attributes[1] == "game_running")
	{
		created_form.trigger_conditions.push_back(CONDITION_GAME_RUNNING);
	}
}

void FormsManager::RegisterComponentTextBox(vector<string> attributes, form &created_form)
{
	int x, y;
	string text;
	x = atoi(attributes[1].c_str());
	y = atoi(attributes[2].c_str());
	text = attributes[3];
	created_form.text_boxes.push_back(ComponentTextBox(x, y, text));
}

void FormsManager::evaluate_input(gui_event event_pkg)
{
	if (is_form_enabled)
	{
		for (int i = 0; i < forms.size(); i++)
		{
			for (size_t j = 0; j < forms[i].buttons.size(); j++)
			{
				if (event_pkg.MouseX >= forms[i].buttons[j].posX+cameraX && event_pkg.MouseX <= forms[i].buttons[j].posX+cameraX+150)
				{
					if (event_pkg.MouseY >= forms[i].buttons[j].posY+cameraY &&event_pkg.MouseY <= forms[i].buttons[j].posY + cameraY + 50)
					{
						forms[i].buttons[j].mouse_hovering = true;
						if (get_mouse_state("LMB"))
						{
							forms[i].buttons[j].recv_event(GUI_KEY_PRESS);
						}
					}
					else
					forms[i].buttons[j].mouse_hovering = false;
				}
				else
					forms[i].buttons[j].mouse_hovering = false;
			}
			if(forms[i].trigger == TRIGGER_KEYPRESS && vector_contains(forms[i].trigger_conditions, event_pkg.key))
			{
				if (vector_contains(forms[i].trigger_conditions, CONDITION_GAME_RUNNING))
				{
					if (is_game_running)
					{
						disable_form(i);
						al_rest(.1);
					}
				}
				else
				{
					disable_form(i);
					al_rest(.1);
				}
			}
		}
	}
	else
	{
		
		for (int i = 0; i < forms.size(); i++)
		{
			
			if (forms[i].trigger == TRIGGER_KEYPRESS && vector_contains(forms[i].trigger_conditions, event_pkg.key))
			{
				if (vector_contains(forms[i].trigger_conditions, CONDITION_GAME_RUNNING))
				{
					if (is_game_running)
					{
						enable_form(i);
						al_rest(.1);
					}
				}
				else
				{
					enable_form(i);
					al_rest(.1);
				}
			}
		}
		
	}


}

void FormsManager::draw_forms()
{
	for (int i = 0; i < currently_enabled_forms.size()&&currently_enabled_forms[i]!=NULL; i++)
	{
		al_draw_filled_rectangle(currently_enabled_forms[i]->PosX + cameraX,currently_enabled_forms[i]->PosY + cameraY,	currently_enabled_forms[i]->PosX + cameraX + currently_enabled_forms[i]->width,			currently_enabled_forms[i]->PosY + cameraY + currently_enabled_forms[i]->height,			al_map_rgba(200, 200, 200, .5));
		for (size_t j = 0; j < currently_enabled_forms[i]->buttons.size(); j++)
		{
			currently_enabled_forms[i]->buttons[j].Render();
		}
		for (size_t j = 0; j < currently_enabled_forms[i]->text_boxes.size(); j++)
		{
			currently_enabled_forms[i]->text_boxes[j].draw_text();
		}

	}
	slaughter_forms();
}


void enable_form(int of_ID)
{
	bool already_enabled = false;
	if (forms_manager.free_form_IDs.empty())
	{
		for (size_t i = 0; i < forms_manager.currently_enabled_forms.size(); i++)
		{
			if (&forms_manager.forms[of_ID] == forms_manager.currently_enabled_forms[i])
			{
				already_enabled = true;
				break;
			}
		}

		if (!already_enabled)
			forms_manager.currently_enabled_forms.push_back(&forms_manager.forms[of_ID]);
	}
	else
	{
		forms_manager.currently_enabled_forms[forms_manager.free_form_IDs[forms_manager.free_form_IDs.size()-1]] = &forms_manager.forms[of_ID];
		forms_manager.free_form_IDs.pop_back();
	}
	forms_manager.is_form_enabled = true;

}


void slaughter_forms()
{
	if (forms_manager.currently_enabled_forms.size() == 1 && forms_manager.forms_to_be_disabled.size() == 1)
	{
		forms_manager.currently_enabled_forms.clear();
		forms_manager.forms_to_be_disabled.clear();
		forms_manager.is_form_enabled = false;
		return;
	}
	
	for (size_t i = 0; i < forms_manager.currently_enabled_forms.size(); i++)
	{
		for (size_t ID = 0; ID < forms_manager.forms_to_be_disabled.size(); ID++)
		{
			if (&forms_manager.forms[forms_manager.forms_to_be_disabled[ID]] == forms_manager.currently_enabled_forms[i])
			{
				forms_manager.currently_enabled_forms[i] = NULL;
				forms_manager.free_form_IDs.push_back(i);
			}
		}

	}
	forms_manager.forms_to_be_disabled.clear();
}

void FormsManager::search_for_main_form()
{
	for (int i = 0; i < forms.size(); i++)
	{
		if (forms[i].is_main)
		{
			forms[i].PosX = 0;
			forms[i].PosY = 0;
			forms[i].width = ScreenWidth;
			forms[i].height = ScreenHeight;
			main_form = i;
			

			break;
		}
	}
}

void disable_form(int of_ID)
{
	forms_manager.forms_to_be_disabled.push_back(of_ID);
}

void FormsManager::init_startup_form()
{
	if (main_form == -1)
	{
		fprintf(stderr, "Failed to load startup form, you should't have messed around...!\n");
		_getch();
		std::exit(-1);
	}
	else
	{
		enable_form(main_form);
		while (!done)
		{
			cout << currently_enabled_forms.size() << endl;
			forms_manager.draw_forms();
			check_interactions(-1, -1, keyboard_input());
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_rest(0.016);
			if (is_game_running)
				return;
		}
	}
}