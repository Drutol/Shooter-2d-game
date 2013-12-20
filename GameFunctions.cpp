#include "link.h"
#include "GameFunctions.h"


//Bitmaps 
ALLEGRO_BITMAP *dirt; 
ALLEGRO_BITMAP *dirt_back;
ALLEGRO_BITMAP *dirt_back_up;
ALLEGRO_BITMAP *dirt_back_down;
ALLEGRO_BITMAP *door_bitmap;
ALLEGRO_BITMAP *lever_bitmap;
ALLEGRO_BITMAP *overlay;
ALLEGRO_BITMAP *dark_test;
bool bitmaps_initialized=false;
Interaction_Indicator indicator;
using namespace std;
bool keyboard_input_specific(int which_key)
{
	ALLEGRO_KEYBOARD_STATE keystate;
	al_get_keyboard_state(&keystate);
	if(al_key_down(&keystate,which_key))
		return true;
	else
		return false;
}



int keyboard_input()
{
	ALLEGRO_KEYBOARD_STATE keystate;
	al_get_keyboard_state(&keystate);
	if(al_key_down(&keystate,ALLEGRO_KEY_D))
		return ALLEGRO_KEY_D;
	if(al_key_down(&keystate,ALLEGRO_KEY_A))
		return ALLEGRO_KEY_A;
	if(al_key_down(&keystate,ALLEGRO_KEY_W))
		return ALLEGRO_KEY_W;
	if(al_key_down(&keystate,ALLEGRO_KEY_S))
		return ALLEGRO_KEY_S;
	if(al_key_down(&keystate,ALLEGRO_KEY_ESCAPE))
		return ALLEGRO_KEY_ESCAPE;
	if(al_key_down(&keystate,ALLEGRO_KEY_RIGHT))
		return ALLEGRO_KEY_RIGHT;
	if(al_key_down(&keystate,ALLEGRO_KEY_LEFT))
		return ALLEGRO_KEY_LEFT;
	if(al_key_down(&keystate,ALLEGRO_KEY_SPACE))
		return ALLEGRO_KEY_SPACE;
	if(al_key_down(&keystate,ALLEGRO_KEY_E))
		return ALLEGRO_KEY_E;
	if(al_key_down(&keystate,ALLEGRO_KEY_K))
		return ALLEGRO_KEY_K;
	
	return NULL;
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
	if(which=="overlay")
		return overlay;
	if(which=="darkener")
		return dark_test;
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
	overlay=al_load_bitmap("Resources/Overlay.png");
	dark_test=al_load_bitmap("Resources/darkener.png");
	//OBJECTS//
	door_bitmap=al_load_bitmap("Resources/Doors.png");
	lever_bitmap=al_load_bitmap("Resources/lever.png");
}
////////////////////////////////////////////////////////////////	Counting
int count_doors()
{
	int counted_doors=0;
	for(int i=0;i<20;i++)
	{
		if(doors[i].exists==1)
			counted_doors++;
		else break;
	}
	return counted_doors;
}
int count_levers()
{
	int counted_levers=0;
	for(int i=0;i<20;i++)
	{
		if(levers[i].exists==1)
			counted_levers++;
		else break;
	}
	return counted_levers;
}
int count_boxes()
{
	int counted_boxes=0;
	for(int i=0;i<20;i++)
	{
		if(affection_boxes[i].exists==1)
			counted_boxes++;
		else break;
	}
	return counted_boxes;
}
//////////////////////////////////////////////////////////////// End Counting
void check_interactions(int tile_X,int tile_Y,int with_key)
{

		if(map[tile_X][tile_Y].held_object==LEVER)
		{
			int ID=search_for_object_ID(tile_X,tile_Y,LEVER);
			if(with_key!=NULL&&with_key!=ALLEGRO_KEY_SPACE&&with_key!=ALLEGRO_KEY_LEFT&&with_key!=ALLEGRO_KEY_RIGHT)
			{
				if(ID!=-1)
				{
					levers[ID].apply_new_state(with_key);
				}
			}
			else
			{
				for(int i=0;i<levers[ID].connections;i++)
				{
					if(levers[ID].affected_object[i].type==DOOR)
					indicator.highlight_object(doors[levers[ID].affected_object[i].ID].tile_X,doors[levers[ID].affected_object[i].ID].tile_Y);
				}
			}
			indicator.display_keys(LEVER,ID);
			}
		
		
		}

int search_for_object_ID(int tile_X,int tile_Y,int type)
{
	if(type==LEVER)
	{
		if(map[tile_X][tile_Y].held_object==LEVER)
			return map[tile_X][tile_Y].held_object_ID;

	}
	return -1;
}

void draw_objects()
{
	for(int i=0;i<count_doors();i++)
		{
			if(doors[i].exists)
				doors[i].draw_door();
		}
	for(int i=0;i<count_levers();i++)
		{
			if(levers[i].exists)
				levers[i].object_draw();
		}
		
}		

void check_affection_box_collision(int radius)
{
	int xr,xl,yt,yb;
	xl=player.player_get_posx()-radius;
	xr=player.player_get_posx()+32+radius;
	yt=player.player_get_posy()-radius;
	yb=player.player_get_posy()+32+radius;

	bool inside=false;
	bool approaching_left=false;
	bool approaching_right=false;
	bool approaching_top=false;
	bool approaching_bottom=false;
	bool passable=true;
	
	
	
	for(int i=0;i<count_boxes();i++)
	{
		int modifier=0;
		if(affection_boxes[i].shorter_than_player)
			modifier=16;
		if(affection_boxes[i].check_if_inside(xl,yt+modifier))
			{
					inside=true;
					approaching_left=true;
			}
		else if(affection_boxes[i].check_if_inside(xl,yb-modifier))
			{
					inside=true;
					approaching_left=true;
			}
		else if(affection_boxes[i].check_if_inside(xr,yt+modifier))
			{
					inside=true;
					approaching_right=true;
			}
		else if(affection_boxes[i].check_if_inside(xr,yb-modifier))
			{
					inside=true;
					approaching_right=true;
			}

		if(affection_boxes[i].check_if_inside(xl+2,yt)||affection_boxes[i].check_if_inside(xr-2,yt))
			approaching_bottom=true;
		if(affection_boxes[i].check_if_inside(xl,yb+3)||affection_boxes[i].check_if_inside(xr,yb+3))
				approaching_top=true;

		
		if(affection_boxes[i].check_flag(FLAG_UNPASSABLE,false))
			passable=false;
	}
	cout<<inside<<endl;
	if(inside)
	{
		player.PosY-=2;
	}
	if(!passable)
	{
		//if(approaching_top)
		//	player.force_ground=true;
		//else
		//	player.force_ground=false;
		if(approaching_left&&!approaching_top)
			player.can_move_left=false;
		else
			player.can_move_left=true;
		if(approaching_right&&!approaching_top)
			player.can_move_right=false;
		else
			player.can_move_right=true;
		if(approaching_bottom)
			{
				player.can_jump=false;
				player.remove_momentum(true);
			}
		else
			player.can_jump=true;
	}

}
