#include "link.h"
#include "GameFunctions.h"


//////////////////////////////////////////////////////////////// Drawing
void main_game()
{
	
	//ARG PASSING ORDER: 
	system("LevelEditor.exe 200 300 1 1 5 dirt");
	// Cam vars
	cameraX=0.5,
	cameraY=0.5;
	al_rest(1.0);

	al_clear_to_color(al_map_rgb(255,255,255));
	game_font = al_load_font("Resources/leadcoat.ttf",40,NULL);
	al_install_keyboard();
	al_init_image_addon();
	load_level();
	/*map[3][5].bitmap="dirt";
	map[3][5].passable=false;*/
	//map[5][2].bitmap="dirt_back";
	//map[5][2].passable=true;
	//map[5][3].bitmap="dirt_back";
	//map[5][3].passable=true;
	//map[5][4].bitmap="dirt_back";
	//map[5][4].passable=true;
	//map[5][5].bitmap="dirt_back_down";
	//map[5][5].passable=true;
	ALLEGRO_EVENT_QUEUE *game_events = al_create_event_queue();
	al_register_event_source(game_events, al_get_keyboard_event_source());
	
	test_NPC.PosX=300;
	test_NPC.PosY=300;


	affection_boxes.push_back(Affection_box());
	affection_boxes[0].set_up(1,1,10,10,NOTHING,NULL,0);
	affection_boxes[0].add_flag(FLAG_UNPASSABLE);
	//--Creating Instance of Damage manager--//
	Damage_manager damage_manager;
	//--------------------------------------//

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
		if(check_door_collision())
			kill_player();
		
		check_interactions(player.get_tile_X(),player.get_tile_Y(),keyboard_input());

		check_affection_box_collision_NPC(3,test_NPC);
		
		//-----Shooting test---//
		if(get_mouse_state("LMB"))
		{
			al_rest(0.01);
			int mouse_tile_x,mouse_tile_y;
			mouse_tile_x=get_mouse_state("x")/TileSize;
			mouse_tile_y=get_mouse_state("y")/TileSize;
			if(map[mouse_tile_x][mouse_tile_y].passable)
			{
				damage_manager.register_projectile(player.PosX,player.PosY,get_mouse_state("x"),get_mouse_state("y"),5);
			}
		}
		damage_manager.process_projectiles();
		//-----Shooting Test----//
		
		
		
		
		//----------------------//
		test_NPC.Gather_data();
		test_NPC.move();
		test_NPC.draw();
		//----------------------//
		
		

		//----------------------//
		
		//PLAYER STUFF
		check_affection_box_collision_player(3);
		player.move();
		player.apply_move(NULL);
		player.draw();
		//END Player STUFF
		
		//----------------------//
		
		//SCROLLING
		use_transform(cameraX,cameraY);
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