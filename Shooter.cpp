#include "link.h"
#include "GameFunctions.h"
#include "Player.h"
#include "Doors.h"
enum bitmaps {DIRT,DIRT_BACK,DIRT_BACK_DOWN,DIRT_BACK_UP};
ALLEGRO_TRANSFORM camera;
tile map[20][20];
Player player;
bool check_door_collison()
{
	if(map[player.player_get_tile_X()][player.player_get_tile_Y()].passable==false&&map[player.player_get_tile_X()][player.player_get_tile_Y()].held_object==DOOR)
		return true;
	else
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
	std::ofstream out("test.dat");
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
			out<<map[i][j].bitmap;
			/*if(map[i][j].bitmap=="dirt")
			out<<DIRT;
			if(map[i][j].bitmap=="dirt_back")
			out<<DIRT_BACK;
			if(map[i][j].bitmap=="dirt_back_down")
			out<<DIRT_BACK_DOWN;
			if(map[i][j].bitmap=="dirt_back_up")
			out<<DIRT_BACK_UP;*/
			out<<std::endl;
		}
	}
}
void load_level(int level)
{
	std::fstream file("Levels/level1.dat");
	string line;

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
			map[i][j].bitmap=line;
		}
	}

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
void map_init()
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			map[i][j].x=i*TileSize;
			map[i][j].y=j*TileSize;
			map[i][j].passable=false;
			map[i][j].bitmap="dirt";
			
		}
	}

}
void map_draw()
{
		
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			al_draw_bitmap(return_appropriate_bitmap(map[i][j].bitmap),map[i][j].x,map[i][j].y,NULL);
		}
	}

}
void main_game()
{
	//ALLEGRO TYPES
		ALLEGRO_FONT *Load_font;

	// Cam vars
	float cameraX=0.5,cameraY=0.5;
	al_rest(1.0);

	al_clear_to_color(al_map_rgb(255,255,255));

	Load_font = al_load_font("Resources/leadcoat.ttf",40,NULL);
	al_install_keyboard();
	al_init_image_addon();
	Doors door;


	//map_init();
	//map[1][2].bitmap="dirt_back_up";
	//map[1][2].passable=true;
	//map[1][3].bitmap="dirt_back";
	//map[1][3].passable=true;
	//map[1][4].bitmap="dirt_back_down";
	//map[1][4].passable=true;
	//////////////////////////////////
	//map[2][2].bitmap="dirt_back_up";
	//map[2][2].passable=true;
	//map[2][3].bitmap="dirt_back_down";
	//map[2][3].passable=true;
	/////////////////////////////////
	//map[3][3].bitmap="dirt_back";
	//map[3][3].passable=true;
	//map[3][4].bitmap="dirt_back";
	//map[3][4].passable=true;
	////////////////////////////////////
	//map[4][4].bitmap="dirt_back";
	//map[4][4].passable=true;
	//map[4][5].bitmap="dirt_back";
	//map[4][5].passable=true;
	//////////////////////////////////
	//map[5][5].bitmap="dirt_back_down";
	//map[5][5].passable=true;
	bool game_done=false;

	load_level(1);
	door.set_up(4,5);
		//save_map();
	ALLEGRO_EVENT_QUEUE *game_events = al_create_event_queue();
	al_register_event_source(game_events, al_get_keyboard_event_source());
	while(!game_done)
	{
		ALLEGRO_EVENT game_event;
		al_wait_for_event_timed(game_events,&game_event,0.01);
		cameraX=camera_update(keyboard_input(),cameraX,0);
		cameraY=camera_update(keyboard_input(),cameraY,1);
		map_draw();
		door.draw_door();
		cout<<player.player_get_tile_X()<<","<<player.player_get_tile_Y()<<endl;
		
		if(check_door_collison())
			kill_player();
		if(keyboard_input()==ALLEGRO_KEY_E)
			door.change_state();
		//----------------------//
		
		//PLAYER STUFF
		player.player_move();
		player.player_apply_move(keyboard_input());
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
	al_draw_text(Load_font,al_map_rgb(180,123,90),350,350,ALLEGRO_ALIGN_CENTRE,"Loading...");
	al_flip_display();
	game_done=true;
	al_rest(1.0);
}