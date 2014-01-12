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
	ALLEGRO_FILECHOOSER *test;
	test=al_create_native_file_dialog("Levels/CustomMaps/","Load",NULL,ALLEGRO_FILECHOOSER_FOLDER);
	int mouse_tile_X;
	int mouse_tile_Y;
	std::stringstream executable;
	bool is_window_active=true;
	bool reload_level=false;
	std::string filePath;

	levers.push_back(Lever());
	levers[0].set_up(2,128,128,0,ALLEGRO_KEY_E);
	levers[0].add_affected_objects(DOOR,0);
	levers.push_back(Lever());
	levers[1].set_up(0,400,400,1,NULL);

	doors.push_back(Doors());
	doors[0].set_up(4,4,0,1,OPEN,UP);


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
		draw_objects();
		mouse_tile_X=edit_event.mouse.x/TileSize;
		mouse_tile_Y=edit_event.mouse.y/TileSize;
		
		al_draw_bitmap(return_appropriate_bitmap("overlay"),mouse_tile_X*TileSize-3,mouse_tile_Y*TileSize-3,NULL);
		if(get_mouse_state("LMB"))
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
		if(keyboard_input_specific(ALLEGRO_KEY_J))
			{
				int succes = system("LevelEditor.exe Save");
				cout<<succes<<endl;
				if(succes==1)
				{
					std::ifstream in("Levels/LevelEditor/temp.dat");
					std::string name;
					getline(in,name);
					remove("Levels/LevelEditor/temp.dat");
					std::string path="Levels/";
					path+=name;
					_mkdir(path.c_str());
					save_map(name);
				}
			}
		if(keyboard_input_specific(ALLEGRO_KEY_K))
		{
			al_show_native_file_dialog(display,test);
		    if( al_get_native_file_dialog_count(test) > 0 )
			{
     
			 filePath.clear();
			 filePath = al_get_native_file_dialog_path(test,0);

			 reload_level=true;
			}
 
			cout<<filePath<<endl;
		}
		if(get_mouse_state("RMB"))
		{
			std::vector<int> lever_ID;
			std::ofstream out("Levels/LevelEditor/temp.dat");
			if(map[mouse_tile_X][mouse_tile_Y].held_object==DOOR)
			{
				for(int i=0;i<count_levers();i++)
				{
					for(int j=0;j<levers[i].connections;j++)
					{
						if(levers[i].affected_object[j].type==DOOR&&levers[i].affected_object[j].ID==map[mouse_tile_X][mouse_tile_Y].held_object_ID)
							{
								out<<LEVER<<std::endl<<i<<std::endl;
								lever_ID.push_back(i);
							}
						
					}
				}
				out.close();
				out.open("Levels/LevelEditor/temp1.dat");
				for(int i=0;i<count_levers();i++)
				{
					bool can_add=true;
					for(int j=0;j<lever_ID.size();j++)
					{
						if(i==lever_ID[j])
							can_add=false;
					}
					if(can_add)
					{
						out<<LEVER<<std::endl<<i<<std::endl;
					}
				}
				bool succes = system("LevelEditor.exe Object Door 300 300 ");
			
			
			
			
			}
		}
		if(keyboard_input_specific(ALLEGRO_KEY_ESCAPE))
			edit_done=true;
		if(edit_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);									///////////APP CLOSING



		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		
		if(reload_level)
		{
			load_level(filePath,true);
			reload_level=false;
		}
	}





}