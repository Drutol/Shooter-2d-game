#pragma once
#include "link.h"
class Interaction_Indicator
{
private:
    std::string string_to_return;
public:
	void highlight_object(int tile_X,int tile_Y);
	void display_keys(int for_object,int ID);
	std::string get_key_string(int type,int ID);
	std::string compose_string(int for_object,int ID);
	Interaction_Indicator(void);
	~Interaction_Indicator(void);
};

