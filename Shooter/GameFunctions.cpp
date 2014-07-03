#include "link.h"
#include "GameFunctions.h"

//VARS DEFINITIONS
ALLEGRO_TRANSFORM camera;
tile map[20][20];
Player player;
std::vector<Doors> doors;
std::vector<Lever> levers;
std::vector<Affection_box> affection_boxes;
ALLEGRO_FONT *game_font;
NPC test_NPC;
NPC dummy;
float cameraX,cameraY;
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
FormsManager forms_manager;





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
int get_mouse_state(std::string task)
{
	ALLEGRO_MOUSE_STATE mousestate;
	al_get_mouse_state(&mousestate);
	if(task == "x")
		return mousestate.x;
	if(task == "y")
		return mousestate.y;
	if(task == "LMB")
		return mousestate.buttons & 1;
	if(task == "RMB")
		return mousestate.buttons & 2; 
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
	if(!doors.empty())
		{
		for(int i=0;i<20;i++)
		{
			if(doors[i].exists==1)
				counted_doors++;
			else break;
		}
	}
	return counted_doors;
}
int count_levers()
{
	int counted_levers=0;
	if(!levers.empty())
	{
		for(int i=0;i<20;i++)
		{
			if(levers[i].exists==1)
				counted_levers++;
			else break;
		}
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
				for(int i=0;i<levers[ID].affected_object.size();i++)
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
	for(int i=0;i<doors.size();i++)
		{
			if(doors[i].exists)
				doors[i].draw_door();
		}
	for(int i=0;i<levers.size();i++)
		{
			if(levers[i].exists)
				levers[i].object_draw();
		}
		
}		

void check_affection_box_collision_NPC(int radius,NPC &npc)
{
	if(!affection_boxes.empty())
	{

		int xr,xl,yt,yb;
		xl=npc.get_posx()-radius;
		xr=npc.get_posx()+32+radius;
		yt=npc.get_posy()-radius;
		yb=npc.get_posy()+32+radius;

		bool inside=false;
		bool approaching_left=false;
		bool approaching_right=false;
		bool approaching_top=false;
		bool approaching_bottom=false;
		bool passable=true;
	
	

		for(int i=0;i<affection_boxes.size();i++)
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
		if(inside)
		{
			npc.PosY-=2;
		}
		if(!passable)
		{
			if(approaching_left&&!approaching_top)
				npc.can_move_left=false;
			else
				npc.can_move_left=true;
			if(approaching_right&&!approaching_top)
				npc.can_move_right=false;
			else
				npc.can_move_right=true;
			if(approaching_bottom)
				{
					npc.can_jump=false;
					npc.remove_momentum(true);
				}
			else
				npc.can_jump=true;
		}
	}

}
void check_affection_box_collision_player(int radius)
{
	if(!affection_boxes.empty())
	{
		int xr,xl,yt,yb;
		xl=player.get_posx()-radius;
		xr=player.get_posx()+32+radius;
		yt=player.get_posy()-radius;
		yb=player.get_posy()+32+radius;

		bool inside=false;
		bool approaching_left=false;
		bool approaching_right=false;
		bool approaching_top=false;
		bool approaching_bottom=false;
		bool passable=true;
	
	
	
		for(int i=0;i<affection_boxes.size();i++)
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
			else
			{
				player.can_move_left=true;
				player.can_jump=true;
				player.can_move_right=true;
			}
		}
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

}
bool check_door_collision()
{
	if(!doors.empty())
	{
		if(map[player.get_tile_X()][player.get_tile_Y()].passable==false&&map[player.get_tile_X()][player.get_tile_Y()].held_object==DOOR)
		{
			if(doors[map[player.get_tile_X()][player.get_tile_Y()].held_object_ID].state==OPENING||doors[map[player.get_tile_X()][player.get_tile_Y()].held_object_ID].state==CLOSING)
				return true;
		}
		return false;
	}
}
void kill_player()
{
	player.die();
}
float return_player_X()
{
	return player.get_posx();
}
float return_player_Y()
{
	return player.get_posy();
}
void overwrite_tile(int x,int y,bool is_passable,std::string bitmap,int held_object)
{
		map[x][y].passable=is_passable;
	if(bitmap!="NULL")
		map[x][y].bitmap=bitmap;
	if(held_object>-1)
		map[x][y].held_object=DOOR;
}
void save_map(std::string path)
{
	if(!levers.empty())
	{
		std::ofstream out("Levels/"+path+"/levers.dat");
		out<<levers.size()-free_lever_IDs.size()<<endl;
		for(int i=0;i<levers.size();i++)
		{
			if(levers[i].exists)
			{
				int conn_count=0;
				out<<levers[i].PosX<<endl;
				out<<levers[i].PosY<<endl;
				out<<levers[i].connections<<endl;
				for(int j=0;j<levers[i].affected_object.size();j++)
				{
					if(levers[i].affected_object[j].type!=NOTHING&&levers[i].affected_object[j].ID!=-1)
					{
						out<<levers[i].affected_object[j].type<<endl;
						out<<levers[i].affected_object[j].ID<<endl;
					}
				}
			}
		}
		out.close();
	}
	if(!doors.empty())
	{
		std::ofstream out("Levels/"+path+"/doors.dat");
		out<<doors.size()-free_door_IDs.size()<<endl;
		for(int j=0;j<doors.size();j++)
		{
			if(doors[j].exists)
			{
			out<<doors[j].tile_X<<endl;
			out<<doors[j].tile_Y<<endl;
			out<<doors[j].door_speed<<endl;
			out<<doors[j].state<<endl;
			out<<doors[j].direction<<endl;
			}
		}
		out.close();
	}
	std::ofstream out("Levels/"+path+"/map.dat");
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			out<<map[i][j].x;
			out<<std::endl;
			out<<map[i][j].y;
			out<<std::endl;
			out<<map[i][j].passable;
			out<<std::endl;
			//out<<map[i][j].held_object;
			//out<<std::endl;
			//out<<map[i][j].held_object_ID;
			//out<<std::endl;
			out<<map[i][j].bitmap;
			out<<std::endl;
		}
	}
	out.close();
}
void load_level(std::string level_path,bool full_path)
{
	string line;
	std::fstream file;
	std::string path_copy;
	path_copy=level_path.c_str();
	if(full_path)
		{
			path_copy+="/map.dat";
			cout<<"map - using path : "<<path_copy<<endl;
			file.open(path_copy);
		}
	else
		file.open("Levels/"+level_path+"/map.dat");
	
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			std::getline(file,line);
			map[i][j].x=atoi(line.c_str());
			std::getline(file,line);
			map[i][j].y=atoi(line.c_str());
			std::getline(file,line);
			map[i][j].passable=atoi(line.c_str());
			std::getline(file,line);
			cout<<line<<endl;
			map[i][j].bitmap=line;
		}
	}
   file.close();
   path_copy=level_path;
   if(full_path)
		{
			path_copy+="/levers.dat";
			file.open(path_copy);
		}
	else
		file.open("Levels/"+level_path+"/levers.dat");
	std::getline(file,line);
	int lever_number=atoi(line.c_str());
	if(lever_number>0)
	{
	
		for(int i=0;i<lever_number;i++)
		{
			levers.push_back(Lever());
			int x,y,conns=0;
			std::getline(file,line);
			x=atoi(line.c_str());
			std::getline(file,line);
			y=atoi(line.c_str());
			std::getline(file,line);
			conns=atoi(line.c_str());
			levers[i].set_up(x,y,i,LEVER,ALLEGRO_KEY_E);
			for(int j=0;j<conns;j++)
			{
				int type,obj_ID;
				std::getline(file,line);
				type=atoi(line.c_str());
				std::getline(file,line);
				obj_ID=atoi(line.c_str());
				levers[i].add_affected_objects(type,obj_ID);
			}
		
		}
	}
	file.close();
	path_copy=level_path;
		if(full_path)
		{
			path_copy+="/doors.dat";
			file.open(path_copy);
		}
	else
		file.open("Levels/"+level_path+"/doors.dat");
	std::getline(file,line);
	int door_number=atoi(line.c_str());
	cout<<"door num"<<door_number<<endl;
	cout<<"is open "<<file.is_open()<<endl;
	if(door_number>0)
	{

		for(int i=0;i<door_number;i++)
		{
			doors.push_back(Doors());
			int x,y,speed,dir,state;
			std::getline(file,line);
			x=atoi(line.c_str());
			std::getline(file,line);
			y=atoi(line.c_str());
			std::getline(file,line);
			speed=atoi(line.c_str());
			std::getline(file,line);
			state=atoi(line.c_str());
			std::getline(file,line);
			dir=atoi(line.c_str());
		
			doors[i].set_up(x,y,i,speed,state,dir);
			cout<<"loaded door"<<endl;
		}
	}
	file.close();
}
bool is_tile_passable(int whichX,int whichY)
{
	return map[whichX][whichY].passable;
}
void use_transform(float cameraX,float cameraY)
{
		al_identity_transform(&camera);
		al_translate_transform(&camera, -cameraX,-cameraY);
		al_use_transform(&camera);
}
//void makeCircleLight() MAY BE USEFUL IN THE FUTURE
//  {
//     float r = 1.0f;
//	 float g = 1.0f;
//	 float b = 1.0f;
//	 float a = 0.03f;
//	 int size = 125;
//       for(int i = 0; i < 30; i++)
//		 {
//		   al_draw_filled_circle(player.player_get_posx(), player.player_get_posy(), size, al_map_rgba_f(r*a , g*a , b*a , a));
//		   if(i < 6)
//       {
//       size -= (rand() % 7) + 3;
//       }
//       else
//       size -= (rand() % 4) + 1;
//       }
//      
//}
//EXPERIMENTAL LIGHT

//////////////////////////////////////////////////////////////// Drawing
void map_draw_back()
{
		
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(map[i][j].bitmap=="dirt")
			al_draw_bitmap(return_appropriate_bitmap(map[i][j].bitmap),map[i][j].x,map[i][j].y,NULL);
		}
	}

}
void map_draw_front()
{
		
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(map[i][j].bitmap!="dirt")	
				al_draw_bitmap(return_appropriate_bitmap(map[i][j].bitmap),map[i][j].x,map[i][j].y,NULL);
			
		
		}
	}
}

void remove_connections(int for_obj_type,int for_object_ID,int in_objects)
{
	if(in_objects==LEVER)
	{
		for(int i=0;i<levers.size();i++)
		{
			for(int j=0;j<levers[i].affected_object.size();j++)
			{
				if(levers[i].affected_object[j].ID==for_object_ID&&levers[i].affected_object[j].type==for_obj_type)
				{
					levers[i].affected_object[j].type=NOTHING;
					levers[i].affected_object[j].ID=-1;
				}
			}
		}
	}





}

void remove_affection_box(int ID)
{
	affection_boxes[ID]=Affection_box();
	free_box_IDs.push_back(ID);
}

bool vector_contains(std::vector<int> vec,int searched)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == searched)
			return true;
	}
	return false;
}