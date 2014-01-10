#include "link.h"
#include "GameFunctions.h"
void update_map()
{
	ifstream in("Levels/LevelEditor/temp.dat");
	if(in)
	{
		tile temp_tile;
		std::string reader;
		int bitmap_ID;
		getline(in,reader);
		temp_tile.x=atoi(reader.c_str());
		getline(in,reader);
		temp_tile.y=atoi(reader.c_str());
		getline(in,reader);
		temp_tile.passable=atoi(reader.c_str());
		getline(in,reader);
		temp_tile.held_object=atoi(reader.c_str());
		getline(in,reader);
		temp_tile.held_object_ID=atoi(reader.c_str());
		getline(in,reader);
		bitmap_ID=atoi(reader.c_str());
		if(bitmap_ID==DIRT)
			temp_tile.bitmap="dirt";
		else if(bitmap_ID==DIRT_BACK)
			temp_tile.bitmap="dirt_back";
		else if(bitmap_ID==DIRT_BACK_DOWN)
			temp_tile.bitmap="dirt_back_down";
		else if(bitmap_ID==DIRT_BACK_UP)
			temp_tile.bitmap="dirt_back_down";


		map[temp_tile.x/TileSize][temp_tile.y/TileSize]=temp_tile;
		in.close();
		remove("Levels/LevelEditor/temp.dat");

	}
}


void prepare_command(std::stringstream &stream,int x,int y)
{
	cout<<map[x][y].passable<<endl;
	stream<<"LevelEditor.exe "
		  <<map[x][y].x<<" "
		  <<map[x][y].y<<" "
		  <<map[x][y].passable<<" "
		  <<map[x][y].held_object<<" "
		  <<map[x][y].held_object_ID<<" "
		  <<map[x][y].bitmap<<" ";

}

void level_editor()
{
	load_level("LevelEditor");
	bool edit_done=false;
	ALLEGRO_EVENT_QUEUE *edit_event_queue = al_create_event_queue();
	al_install_keyboard();
	al_register_event_source(edit_event_queue,al_get_mouse_event_source());
	al_register_event_source(edit_event_queue,al_get_display_event_source(display));
	al_register_event_source(edit_event_queue,al_get_keyboard_event_source());
	al_init_image_addon();
	
	int mouse_tile_X;
	int mouse_tile_Y;
	std::stringstream executable;
	bool is_window_active=true;
	while(!edit_done)
	{
		ALLEGRO_EVENT edit_event;
		al_wait_for_event(edit_event_queue,&edit_event);
		if(edit_event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT)
			is_window_active=false;

		while(!is_window_active)
		{		
			ALLEGRO_EVENT edit_event_window;
			al_wait_for_event(edit_event_queue,&edit_event_window);
			if(edit_event_window.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN)
			is_window_active=true;
		}
		map_draw_back();
		map_draw_front();
		
		mouse_tile_X=edit_event.mouse.x/TileSize;
		mouse_tile_Y=edit_event.mouse.y/TileSize;
		
		al_draw_bitmap(return_appropriate_bitmap("overlay"),mouse_tile_X*TileSize-3,mouse_tile_Y*TileSize-3,NULL);
		if(edit_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				prepare_command(executable,mouse_tile_X,mouse_tile_Y);
				cout<<executable.str()<<endl;
				system(executable.str().c_str());
				executable.str(string());
				update_map();
			}
		if(keyboard_input_specific(ALLEGRO_KEY_H))
			{
				system("LevelEditor.exe Help");
			}
		if(keyboard_input_specific(ALLEGRO_KEY_ESCAPE))
			edit_done=true;
		if(edit_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);									///////////APP CLOSING



		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		
	}





}