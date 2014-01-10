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
	levers = new Lever[20];
	doors = new Doors[20];
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
	affection_boxes=new Affection_box[2];
	ALLEGRO_EVENT_QUEUE *game_events = al_create_event_queue();
	al_register_event_source(game_events, al_get_keyboard_event_source());
	
	test_NPC.PosX=200;
	test_NPC.PosY=200;


	affection_boxes[0].set_up(100,100,50,32,NOTHING,NULL,0);
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
		if(check_door_collision())
			kill_player();
		check_interactions(player.get_tile_X(),player.get_tile_Y(),keyboard_input());


		check_affection_box_collision_NPC(3,test_NPC);

		test_NPC.Gather_data();
		//test_NPC.apply_move(ALLEGRO_KEY_SPACE);
		test_NPC.move();
		test_NPC.draw();
		//----------------------//
		
		
		affection_boxes[0].debug_draw_frame();
		affection_boxes[1].debug_draw_frame();
		

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