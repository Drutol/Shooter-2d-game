#include "link.h"
#include "GameFunctions.h"
ALLEGRO_TRANSFORM camera;
tile map[20][20];
Player player;
Doors *doors;
Lever *levers;
Affection_box *affection_boxes;
ALLEGRO_FONT *game_font;
float cameraX,cameraY;
bool check_door_collison()
{
	if(map[player.player_get_tile_X()][player.player_get_tile_Y()].passable==false&&map[player.player_get_tile_X()][player.player_get_tile_Y()].held_object==DOOR)
	{
		if(doors[map[player.player_get_tile_X()][player.player_get_tile_Y()].held_object_ID].state==OPENING||doors[map[player.player_get_tile_X()][player.player_get_tile_Y()].held_object_ID].state==CLOSING)
			return true;
	}
	return false;
}
void kill_player()
{
	player.player_die();
}
float return_player_X()
{
	return player.player_get_posx();
}
float return_player_Y()
{
	return player.player_get_posy();
}
void overwrite_tile(int x,int y,bool is_passable,std::string bitmap,int held_object)
{
		map[x][y].passable=is_passable;
	if(bitmap!="NULL")
		map[x][y].bitmap=bitmap;
	if(held_object>-1)
		map[x][y].held_object=DOOR;
}
void save_map()
{
	std::ofstream out("Levels/Level1/levers.dat");
	out<<count_levers()<<endl;
	for(int i=0;i<count_levers();i++)
	{
		out<<levers[i].PosX<<endl;
		out<<levers[i].PosY<<endl;
		out<<levers[i].connections<<endl;
		for(int j=0;j<levers[i].connections;j++)
		{
			out<<levers[i].affected_object[j].type<<endl;
			out<<levers[i].affected_object[j].ID<<endl;
		}
	}
	out.close();
	out.open("Levels/Level1/doors.dat");
	out<<count_doors()<<endl;
	for(int j=0;j<count_doors();j++)
	{
		out<<doors[j].tile_X<<endl;
		out<<doors[j].tile_Y<<endl;
		out<<doors[j].door_speed<<endl;
		out<<doors[j].state<<endl;
		out<<doors[j].direction<<endl;
	}
	out.close();
	out.open("Levels/Level1/map.dat");
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
			out<<map[i][j].held_object;
			out<<std::endl;
			out<<map[i][j].held_object_ID;
			out<<std::endl;
			out<<map[i][j].bitmap;
			out<<std::endl;
		}
	}
	out.close();
}
void load_level(int level)
{
	string line;
	std::fstream file("Levels/Level1/map.dat");
	
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			getline(file,line);
			map[i][j].x=atoi(line.c_str());
			getline(file,line);
			map[i][j].y=atoi(line.c_str());
			getline(file,line);
			map[i][j].passable=atoi(line.c_str());
			getline(file,line);
			map[i][j].held_object=atoi(line.c_str());
			getline(file,line);
			map[i][j].held_object_ID=atoi(line.c_str());
			getline(file,line);
			map[i][j].bitmap=line;
		}
	}
	file.close();
	file.open("Levels/Level1/levers.dat");
	getline(file,line);
	int lever_number=atoi(line.c_str());
	levers = new Lever[lever_number];
	
	for(int i=0;i<lever_number;i++)
	{
		
		int x,y,conns=0;
		getline(file,line);
		x=atoi(line.c_str());
		getline(file,line);
		y=atoi(line.c_str());
		getline(file,line);
		conns=atoi(line.c_str());
		levers[i].set_up(conns,x,y,i,ALLEGRO_KEY_E);
		for(int j=0;j<conns;j++)
		{
			int type,obj_ID;
			getline(file,line);
			type=atoi(line.c_str());
			getline(file,line);
			obj_ID=atoi(line.c_str());
			levers[i].add_affected_objects(type,obj_ID);
		}
		
	}
	file.close();
	file.open("Levels/Level1/doors.dat");
	getline(file,line);
	int door_number=atoi(line.c_str());
	doors = new Doors[door_number];

	for(int i=0;i<door_number;i++)
	{
		int x,y,speed,dir,state;
		getline(file,line);
		x=atoi(line.c_str());
		getline(file,line);
		y=atoi(line.c_str());
		getline(file,line);
		speed=atoi(line.c_str());
		getline(file,line);
		state=atoi(line.c_str());
		getline(file,line);
		dir=atoi(line.c_str());
		
		
		doors[i].set_up(x,y,i,speed,state,dir);
	}
	file.close();
}
bool is_tile_passable(int whichX,int whichY)
{
	return map[whichX][whichY].passable;
}
void use_tranform(float cameraX,float cameraY)
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
//////////////////////////////////////////////////////////////// Drawing
void main_game()
{

	// Cam vars
	cameraX=0.5,
	cameraY=0.5;
	al_rest(1.0);

	al_clear_to_color(al_map_rgb(255,255,255));
	levers = new Lever[20];
	doors = new Doors[20];
	game_font = al_load_font("Resources/leadcoat.ttf",40,NULL);
	al_install_keyboard();
	al_init_image_addon();
	map[2][5].passable=true;
	load_level(1);
	//map[4][4].bitmap="dirt";
	//map[4][4].passable=false;
	//map[3][2].bitmap="dirt_back";
	//map[3][2].passable=true;
	//map[3][3].bitmap="dirt_back";
	//map[3][3].passable=true;
	//map[3][4].bitmap="dirt_back";
	//map[3][4].passable=true;
	//map[3][5].bitmap="dirt_back_down";
	//map[3][5].passable=true;
	affection_boxes=new Affection_box[2];
	ALLEGRO_EVENT_QUEUE *game_events = al_create_event_queue();
	al_register_event_source(game_events, al_get_keyboard_event_source());
	
	
	
	affection_boxes[0].set_up(100,300,50,32,NOTHING,NULL,0);
	//affection_boxes[1].set_up(200,250,50,100,NOTHING,NULL,0);
	affection_boxes[0].add_flags(1,FLAG_UNPASSABLE);
	
	
	bool game_done=false;
	while(!game_done)
	{
		ALLEGRO_EVENT game_event;
		al_wait_for_event_timed(game_events,&game_event,0.01);
		cameraX=camera_update(keyboard_input(),cameraX,0);
		cameraY=camera_update(keyboard_input(),cameraY,1);
		map_draw_front();
		draw_objects();
		map_draw_back();
		if(check_door_collison())
			kill_player();
		check_interactions(player.player_get_tile_X(),player.player_get_tile_Y(),keyboard_input());


		affection_boxes[0].debug_draw_frame();
		affection_boxes[1].debug_draw_frame();
		check_affection_box_collision(3);


		//----------------------//
		
		//PLAYER STUFF
		player.player_move();
		player.player_apply_move();
		player.player_draw();
		//END Player STUFF
		
		//----------------------//
		
		//SCROLLING
		use_tranform(cameraX,cameraY);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		//SCROLLING ENDING
		
		//----------------------//
		
		//LOOP ENDING//
		if(keyboard_input()==ALLEGRO_KEY_ESCAPE)
			game_done=true;
		//END//
		
		//----------------------//

	}
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(game_font,al_map_rgb(180,123,90),350,350,ALLEGRO_ALIGN_CENTRE,"Loading...");
	al_flip_display();
	game_done=true;
	al_rest(1.0);
	//save_map();
}