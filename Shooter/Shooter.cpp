#include "link.h"
#include "GameFunctions.h"
#include"Multiplayer_Client.h"

Damage_manager damage_manager;
void game_cleanup()
{
	doors.clear();
	levers.clear();
	affection_boxes.clear();
	player_boxes_IDs.clear();
	damage_manager.active_projectiles.clear();
}
void shoot(int x, int y)
{

	if (x == 0 && y == 0)
	{
		al_rest(0.01);
		int mouse_tile_x, mouse_tile_y;
		mouse_tile_x = get_mouse_state("x") / TileSize;
		mouse_tile_y = get_mouse_state("y") / TileSize;
		if (map[mouse_tile_x][mouse_tile_y].passable)
		{
			damage_manager.register_projectile(player.PosX, player.PosY, get_mouse_state("x"), get_mouse_state("y"), 5, true);
			register_data(CLICK, get_mouse_state("x"), get_mouse_state("y"));
			player.shoot_CD = 60;
		}
	}
	else
	{
		damage_manager.register_projectile(o_player.x, o_player.y, x, y, 5, false); // <- Crash just because have to look inside							!!!!TODO!!!!
	}
}



//////////////////////////////////////////////////////////////// Drawing
void main_game()
{
	disable_form(forms_manager.main_form); 
	is_game_running = true;
		//ARG PASSING ORDER: 
		//system("LevelEditor.exe 200 300 1 1 5 dirt");
		// Cam vars
	cameraX = 0.5;
	cameraY=0.5;
	al_rest(1.0);
	bool online = false;
	al_clear_to_color(al_map_rgb(255,255,255));
	load_level();
	ALLEGRO_EVENT_QUEUE *game_events = al_create_event_queue();
	al_register_event_source(game_events, al_get_keyboard_event_source());
	
	test_NPC.PosX=300;
	test_NPC.PosY=300;

	Multiplayer_Client client;

	affection_boxes.push_back(Affection_box());
	affection_boxes[0].set_up(1,1,10,10,NOTHING,NULL,0);
	affection_boxes[0].add_flag(FLAG_UNPASSABLE);
	
	//--Loading Forms--//
	//-----------------//
	
	while(is_game_running)
	{	
		//cout << forms_manager.currently_enabled_forms.size() << endl;
		ALLEGRO_EVENT game_event;
		al_wait_for_event_timed(game_events,&game_event,0.016);
		cameraX=camera_update(keyboard_input(),cameraX,0);
		cameraY=camera_update(keyboard_input(),cameraY,1);
		map_draw_front();
		draw_objects();
		map_draw_back();
		if(check_door_collision())
			kill_player();
		

		check_interactions(player.get_tile_X(),player.get_tile_Y(),keyboard_input());
		if (keyboard_input() > 0)
			register_data(KEY_PRESS, player.PosX, player.PosY,keyboard_input());

		check_affection_box_collision_NPC(3,test_NPC);
		//-----Forms----//
		forms_manager.draw_forms();
		//-----Forms----//
		
		
		
		//-----Shooting test---//
		if (get_mouse_state("LMB") && player.shoot_CD == 0)
		{
			shoot();
		}
		damage_manager.process_projectiles();
		//-----Shooting Test----//
		
		
		//-----Multiplayer-----//
		if(keyboard_input_specific(ALLEGRO_KEY_M)&&!online)
		{
			if(client.attempt_connection())
				online = true;
		}

		if (online)
			al_draw_filled_rectangle(o_player.x, o_player.y, o_player.x + 20, o_player.y + 20, al_map_rgb(100, 255, 0));
		//-----Multiplayer-----//

		for (size_t i = 0; i < affection_boxes.size(); i++)
		{
			affection_boxes[i].debug_draw_frame();
		}
		
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
		player.player_box.move_box(player.PosX, player.PosY);
		if (player.shoot_CD != 0)
			player.shoot_CD-=2;
		
		//END Player STUFF
		
		//----------------------//
		
		//SCROLLING
		use_transform(cameraX,cameraY);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		//SCROLLING ENDING
		
		//----------------------//
		
		//----------------------//

	}
	
	
	game_cleanup();
	is_game_running = false;
	al_rest(0.4);
	forms_manager.init_startup_form();
}