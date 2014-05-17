#include "FormsManager.h"


FormsManager::FormsManager()
{
}


FormsManager::~FormsManager()
{
}

vector<form> FormsManager::LoadForms()
{
	std::vector<std::string> forms_found;
	forms_found = get_all_files_names_within_folder("Forma");

	vector<form> output;

	for (int i = 0; i < forms_found.size(); i++)
	{
		cout << forms_found[i] << endl;
		_getch();
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

				switch (read_attributes[0][0])
				{
					case 'b':		//button
						RegisterComponentButton(read_attributes, created_form);
					case 't':		//trigkey
						RegisterFormTrigger(read_attributes, created_form);
					case 'f':		//Form
						created_form.name = read_attributes[1];
					case 'X':		//posx
						created_form.PosX = atoi(read_attributes[1].c_str());
					case 'Y':		//posy
						created_form.PosY = atoi(read_attributes[1].c_str());
					case 'W':		//width
						created_form.width = atoi(read_attributes[1].c_str());
					case 'H':		//height
						created_form.height = atoi(read_attributes[1].c_str());
					case 'c':		//condition
						RegisterFormTriggerConditions(read_attributes, created_form);
					default:
						break;
				}
			}	
			output.push_back(created_form);
		}
	}

	return output;
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
		std::cout << s << std::endl;
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
	PosX = atoi(attributes[1].c_str()) + created_form.PosX;
	PosY = atoi(attributes[2].c_str()) + created_form.PosY;


	r = atoi(attributes[4].c_str());
	g = atoi(attributes[5].c_str());
	b = atoi(attributes[6].c_str());


	if (attributes[3] == "RESUME")
	{
		function_to_pass_int = disabling_function;
		created_form.buttons.push_back(ComponentButton(function_to_pass_int, PosX, PosY, this->forms.size() - 1, attributes[3], al_map_rgb(r, g, b),this->forms.size()-1));
	}
	else if (attributes[3] == "EXIT")
	{
		function_to_pass_void = exit_function;
		created_form.buttons.push_back(ComponentButton(function_to_pass_void, PosX, PosY, this->forms.size() - 1, attributes[3], al_map_rgb(r, g, b)));
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

	created_form.trigger = TRIGGER_KEYPRESS;
	created_form.trigger_conditions.push_back(trigger_value);

}

void FormsManager::RegisterFormTriggerConditions(vector<string> attributes, form &created_form)
{
	if (attributes[1] == "game_running")
	{
		created_form.trigger_conditions.push_back(CONDITION_GAME_RUNNING);
	}
}


void disable_form(int of_ID)
{
}