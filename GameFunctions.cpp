#include "link.h"
#include "GameFunctions.h"


//Bitmaps 
ALLEGRO_BITMAP *dirt; 
ALLEGRO_BITMAP *dirt_back;
ALLEGRO_BITMAP *dirt_back_up;
ALLEGRO_BITMAP *dirt_back_down;
ALLEGRO_BITMAP *door_bitmap;
ALLEGRO_BITMAP *lever_bitmap;
bool bitmaps_initialized=false;
using namespace std;
int keyboard_input()
{
	ALLEGRO_KEYBOARD_STATE keystate;
	al_get_keyboard_state(&keystate);
	if(al_key_down(&keystate,ALLEGRO_KEY_D))
		return ALLEGRO_KEY_D;
	else if(al_key_down(&keystate,ALLEGRO_KEY_A))
		return ALLEGRO_KEY_A;
	else if(al_key_down(&keystate,ALLEGRO_KEY_W))
		return ALLEGRO_KEY_W;
	else if(al_key_down(&keystate,ALLEGRO_KEY_S))
		return ALLEGRO_KEY_S;
	else if(al_key_down(&keystate,ALLEGRO_KEY_ESCAPE))
		return ALLEGRO_KEY_ESCAPE;
	else if(al_key_down(&keystate,ALLEGRO_KEY_RIGHT))
		return ALLEGRO_KEY_RIGHT;
	else if(al_key_down(&keystate,ALLEGRO_KEY_LEFT))
		return ALLEGRO_KEY_LEFT;
	else if(al_key_down(&keystate,ALLEGRO_KEY_SPACE))
		return ALLEGRO_KEY_SPACE;
	else if(al_key_down(&keystate,ALLEGRO_KEY_E))
		return ALLEGRO_KEY_E;
	else return NULL;
}
int camera_update(int pressed_key,float previous_camera_position,int camera)
{
	if(camera==0)
	{
	if(pressed_key==ALLEGRO_KEY_D&&previous_camera_position<1000)
		previous_camera_position+=5;
	else if(pressed_key==ALLEGRO_KEY_A&&previous_camera_position>0.5)
		previous_camera_position-=5;
	}
	if(camera==1)
	{
	if(pressed_key==ALLEGRO_KEY_W&&previous_camera_position>0)
		previous_camera_position-=5;
	else if(pressed_key==ALLEGRO_KEY_S&&previous_camera_position<1220)
		previous_camera_position+=5;
	}
	return previous_camera_position;

}
int get_random_number(int min, int max)
{
	return rand()%(max-min+1)+min;
}
int get_mouse_state(char task)
{
	ALLEGRO_MOUSE_STATE mousestate;
	al_get_mouse_state(&mousestate);
	if(task == 'x')
		return mousestate.x;
	if(task == 'y')
		return mousestate.y;
	if(task == 'LMB')
	return al_mouse_button_down(&mousestate,1);
}
ALLEGRO_BITMAP* return_appropriate_bitmap(std::string which)
{
	if(!bitmaps_initialized)
		{
			init_bitmaps(1);
			bitmaps_initialized=true;
		}
	if(which=="dirt")
		return dirt;
	if(which=="dirt_back_up")
		return dirt_back_up;
	if(which=="dirt_back")
		return dirt_back;
	if(which=="dirt_back_down")
		return dirt_back_down;
	///////////////////////////
			//OBJECTS//
	//////////////////////////
	if(which=="door")
		return door_bitmap;
	if(which=="lever")
		return lever_bitmap;

}

void init_bitmaps(int for_lvl)
{
	dirt=al_load_bitmap("Resources/dirt.png");
	dirt_back=al_load_bitmap("Resources/dirt_back.png");
	dirt_back_up=al_load_bitmap("Resources/dirt_back_up.png");
	dirt_back_down=al_load_bitmap("Resources/dirt_back_down.png");
	//OBJECTS//
	door_bitmap=al_load_bitmap("Resources/Doors.png");
	lever_bitmap=al_load_bitmap("Resources/lever.png");
}

int count_doors()
{
	int counted_doors=0;
	for(int i=0;i<20;i++)
	{
		if(doors[i].exists)
		{
			counted_doors++;
		}
		else break;
	}
	return counted_doors;
}
int count_levers()
{
	int counted_levers=0;
	for(int i=0;i<20;i++)
	{
		if(levers[i].exists)
		{
			counted_levers++;
		}
		else break;
	}
	return counted_levers;
}
void check_interactions(int tile_X,int tile_Y,int with_key)
{

	if(map[tile_X][tile_Y].held_object==LEVER)
	{
		int ID=search_for_object_ID(tile_X,tile_Y,LEVER);
		if(ID!=-1)
		{
			levers[ID].apply_new_state(with_key);
		}
	}



}

int search_for_object_ID(int tile_X,int tile_Y,int type)
{
	if(type==LEVER)
	{
		//for(int i=0;i<20;i++)
		//{
		//	if(levers[i].PosX/TileSize==tile_X&&levers[i].PosY/TileSize==tile_Y&&levers[i].exists)
		//		return i;
		//	
		//	
		//	if(levers[i].exists==false)
		//		break;
		//}
		if(map[tile_X][tile_Y].held_object==LEVER)
			return map[tile_X][tile_Y].held_object_ID;

	}
	return -1;
}