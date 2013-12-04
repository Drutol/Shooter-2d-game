#include "link.h"
#include "GameFunctions.h"


//Bitmaps 
ALLEGRO_BITMAP *dirt; 
ALLEGRO_BITMAP *dirt_back;
ALLEGRO_BITMAP *dirt_back_up;
ALLEGRO_BITMAP *dirt_back_down;
ALLEGRO_BITMAP *door_bitmap;

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

}

void init_bitmaps(int for_lvl)
{
	dirt=al_load_bitmap("Resources/dirt.png");
	dirt_back=al_load_bitmap("Resources/dirt_back.png");
	dirt_back_up=al_load_bitmap("Resources/dirt_back_up.png");
	dirt_back_down=al_load_bitmap("Resources/dirt_back_down.png");
	//OBJECTS//
	door_bitmap=al_load_bitmap("Resources/Doors.png");
}