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
	forms_found=get_all_files_names_within_folder("Forms");

	vector<form> output;

	for (int i = 0; i < forms_found.size(); i++)
	{
		std::ifstream in (forms_found[i].c_str());
		if (in.is_open())
		{
			std::string line;
			vector<string> read_attributes;
			form created_form;

			getline(in, line);
			read_attributes = tokenize(line);

			//Beware almighty switch ...it's on its way

			switch (read_attributes[0][0])
			{
			case 'b':
				RegisterComponentButton(read_attributes, created_form);
			default:
				break;
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
	sprintf(search_path, "%s*.*", folder.c_str());
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

vector<string> FormsManager::tokenize(string string_to_tokenize)
{




}

void FormsManager::RegisterComponentButton(vector<string> attributes, form &created_form)
{
	void(*disabling_function)(void) = &disable_form;;
	void(*exit_function)(void) = kill_player;
	
	void(*function_to_pass)(void);

	if (attributes[3] == "RESUME")
	{
		function_to_pass = disabling_function;
	}
	else if (attributes[3] == "EXIT")
	{
		function_to_pass = exit_function;
	}

	int PosX, PosY,key;
	short r, g, b;
	PosX = atoi(attributes[1].c_str());
	PosY = atoi(attributes[2].c_str());


	r = atoi(attributes[4].c_str());
	g = atoi(attributes[5].c_str());
	b = atoi(attributes[6].c_str());

	created_form.buttons.push_back(ComponentButton(function_to_pass, PosX, PosY, this->forms.size() - 1, attributes[3], al_map_rgb(r, g, b)));


}