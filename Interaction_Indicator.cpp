#include "Interaction_Indicator.h"
#include "link.h"
#include "GameFunctions.h"

Interaction_Indicator::Interaction_Indicator(void)
{
}


Interaction_Indicator::~Interaction_Indicator(void)
{
}
void Interaction_Indicator::highlight_object(int tile_X,int tile_Y)
{
	al_draw_bitmap(return_appropriate_bitmap("overlay"),(tile_X*TileSize)-3,(tile_Y*TileSize)-3,NULL);
}
void Interaction_Indicator::display_keys(int for_object,int ID)
{
	if(for_object==LEVER)
	{
		if(levers[ID].button_to_interact_with==ALLEGRO_KEY_E)
			al_draw_text(game_font,al_map_rgb(30,140,90),cameraX+170,cameraY+10,ALLEGRO_ALIGN_CENTRE,Interaction_Indicator::compose_string(for_object,ID).c_str());
	}
}
std::string Interaction_Indicator::get_key_string(int type,int ID)
{
	if(type==LEVER)
	{
		if(levers[ID].button_to_interact_with==ALLEGRO_KEY_E)
			string_to_return="E";
		else if(levers[ID].button_to_interact_with==ALLEGRO_KEY_K)
			string_to_return="K";
	}
	return string_to_return;
}
std::string Interaction_Indicator::compose_string(int for_object,int ID)
{
	
	
	string_to_return="Press "+Interaction_Indicator::get_key_string(for_object,ID)+" to interact";

	return  string_to_return;
}