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


void prepare_command(std::stringstream &stream,int x,int y,std::string for_obj,int ID=0)
{
	if(for_obj=="tile")
	{
		stream<<"LevelEditor.exe Tile "
			  <<map[x][y].x<<" "
			  <<map[x][y].y<<" "
			  <<map[x][y].passable<<" "
			  <<map[x][y].held_object<<" "
			  <<map[x][y].held_object_ID<<" "
			  <<map[x][y].bitmap<<" ";
	}
	else if(for_obj=="door")
	{
		stream<<"LevelEditor.exe Object Door "
			<<doors[ID].tile_X*TileSize<<" "
			<<doors[ID].tile_Y*TileSize<<" "
			<<doors[ID].door_speed<<" "
			<<doors[ID].initial_state<<" "
			<<doors[ID].direction;
	}
	else if(for_obj=="lever")
	{
		stream<<"LevelEditor.exe Object Lever "
			  <<x<<" "
			  <<y<<" ";
	}
	else if(for_obj=="create")
	{
		stream<<"LevelEditor.exe Object Create "
			<<x<<" "
			<<y<<" ";
	}

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
	ALLEGRO_FILECHOOSER *test;
	test=al_create_native_file_dialog("Levels/CustomMaps/","Load",NULL,ALLEGRO_FILECHOOSER_FOLDER);
	int mouse_tile_X;
	int mouse_tile_Y;
	std::stringstream executable;
	bool is_window_active=true;
	bool reload_level=false;
	std::string filePath;

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
		//--LMB--//
		if(get_mouse_state("LMB"))
			{
				al_rest(0.1);
				prepare_command(executable,mouse_tile_X,mouse_tile_Y,"tile");
				cout<<executable.str()<<endl;
				system(executable.str().c_str());
				executable.str(string());
				update_map();
			}
		//--LMB--//

		//--Help--//
		if(keyboard_input_specific(ALLEGRO_KEY_H))
			{
				al_rest(0.1);
				system("LevelEditor.exe Help");
			}
		//--Help--//

		//--Save--//
		if(keyboard_input_specific(ALLEGRO_KEY_J))
			{
				al_rest(0.1);
				int succes = system("LevelEditor.exe Save");
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
		//--Save--//

		//--Load--//
		if(keyboard_input_specific(ALLEGRO_KEY_K))
		{
			al_rest(0.1);
			al_show_native_file_dialog(display,test);
		    if( al_get_native_file_dialog_count(test) > 0 )
			{
     
			 filePath.clear();
			 filePath = al_get_native_file_dialog_path(test,0);

			 reload_level=true;
			}
 
			cout<<filePath<<endl;
		}
		//--Load--//

		//--RMB--//
		if(get_mouse_state("RMB"))
		{
			bool removal=false;
			al_rest(0.1);
			cout<<" x "<<mouse_tile_X<<" y "<<mouse_tile_Y<<endl;
			std::vector<int> lever_ID;
			std::ofstream out("Levels/LevelEditor/temp.dat");
			//--Door Edit--//
			if(map[mouse_tile_X][mouse_tile_Y].held_object==DOOR)
			{
				int doorID=map[mouse_tile_X][mouse_tile_Y].held_object_ID;
				for(int i=0;i<count_levers();i++)
				{
					for(int j=0;j<levers[i].affected_object.size();j++)
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
				out.close();
				cout<<"door ID : "<<doorID<<endl;
				prepare_command(executable,mouse_tile_X,mouse_tile_Y,"door",doorID);
				cout<<executable.str()<<endl;
				bool succes = system(executable.str().c_str());
				executable.str(std::string());
				
				if(succes)
				{
					Doors temp_door;
					temp_door=doors[doorID];
					std::ifstream in ("Levels/LevelEditor/temp_door.dat");
					std::string reader;
					getline(in,reader);
					if(reader=="Remove")
					{
						removal=true;
						doors[doorID].remove();
						remove_connections(DOOR,doorID,LEVER);
					}
					else
					{
						if(in.is_open())
							{
								int x,y,speed,is_open,dir;
								x=atoi(reader.c_str());
								getline(in,reader);
								y=atoi(reader.c_str());
								getline(in,reader);
								is_open=atoi(reader.c_str());
								getline(in,reader);
								speed=atoi(reader.c_str());
								getline(in,reader);
								dir=atoi(reader.c_str());
							
								doors[doorID].set_up(x,y,doorID,speed,is_open,dir);
							
							}
						in.close();
						remove("Levels/LevelEditor/temp.dat");
						in.open("Levels/LevelEditor/curr_trigs_temp.dat");
						if(in.is_open())
						{
							std::vector<int>IDs;
							while(!in.eof())
							{
								getline(in,reader);
								int ID;
								if(reader[0]=='L')
								{
									if(reader.length()==7)
									{
										ID=reader[6]-'0';
										IDs.push_back(ID);
									}
									else if(reader.length()==8)
									{
										int temp;
										temp=(reader[6]-'0')*10;
										ID=(reader[7]-'0')+temp;
										IDs.push_back(ID);
									}
								}
							}
							// Adding an object to specified ID
							for(int i=0;i<IDs.size();i++)
							{
								levers[IDs[i]].add_affected_objects(DOOR,doorID);
								cout<<"ADDED"<<doorID<<endl;
							}
							IDs.clear();
						in.close();
						remove("Levels/LevelEditor/curr_trigs_temp.dat");
						in.open("Levels/LevelEditor/ava_trigs_temp.dat");
						if(in.is_open())
						{
							std::vector<int>IDs;
							while(!in.eof())
							{
								getline(in,reader);
								int ID;
								if(reader[0]=='L')
								{
									if(reader.length()==7)
									{
										ID=reader[6]-'0';
										IDs.push_back(ID);
									}
									else if(reader.length()==8)
									{
										int temp;
										temp=(reader[6]-'0')*10;
										ID=(reader[7]-'0')+temp;
										IDs.push_back(ID);
									}
								}
							}
							//Checking if Lever object contains door's ID specified
							for(int i=0;i<IDs.size();i++)
							{
								for(int j=0;j<levers[IDs[i]].affected_object.size();j++)
								{
									if(levers[IDs[i]].affected_object[j].ID==doorID&&levers[IDs[i]].affected_object[j].type==DOOR)
									{
										levers[IDs[i]].remove_connection(j);
									}
								}

							}



						
						}
						in.close();
						remove("Levels/LevelEditor/ava_trigs_temp.dat");
					}
			}
		}
	}	
			//--Door Edit--//
			
			//--Lever Edit--//
			if(map[mouse_tile_X][mouse_tile_Y].held_object==LEVER)
			{
				
				int leverID = map[mouse_tile_X][mouse_tile_Y].held_object_ID;
				prepare_command(executable,mouse_tile_X,mouse_tile_Y,"lever");
				bool succes=false;
				succes=system(executable.str().c_str());

				if(succes)
				{
					std::ifstream in("Levels/LevelEditor/temp_lever.dat");
					if(in.is_open())
					{
						std::string reader;
						getline(in,reader);
						if(reader=="Succes")
							levers[leverID].set_up(edit_event.mouse.x,edit_event.mouse.y,leverID,LEVER,ALLEGRO_KEY_E);
						else if(reader=="Remove")
							{
								removal=true;
								levers[leverID].remove();
							}

					}

				}
			}


			//--Lever Edit--//



			//--Object Creation--//
			if(map[mouse_tile_X][mouse_tile_Y].held_object==NOTHING&&!removal)
			{
				prepare_command(executable,mouse_tile_X,mouse_tile_Y,"Create");
				bool succes = system("LevelEditor.exe Object Create");
				executable.str(std::string());
				if(succes)
				{
					std::ifstream in ("Levels/LevelEditor/temp_door.dat");
					if(in.is_open())
						{
							int x,y,speed,is_open,dir;
							std::string reader;
							getline(in,reader);
							x=atoi(reader.c_str());
							getline(in,reader);
							y=atoi(reader.c_str());
							getline(in,reader);
							is_open=atoi(reader.c_str());
							getline(in,reader);
							speed=atoi(reader.c_str());
							getline(in,reader);
							dir=atoi(reader.c_str());
							if(free_door_IDs.empty())
							{
								doors.push_back(Doors());
							    doors[doors.size()-1].set_up(x,y,doors.size()-1,speed,is_open,dir);
							}
							else
							{
								doors[free_door_IDs[free_door_IDs.size()-1]].set_up(x,y,free_door_IDs.size()-1,speed,is_open,dir);
								free_door_IDs.pop_back();
							}
							
						}
					else
					{
						in.close();
						in.open("Levels/LevelEditor/temp_lever.dat");
						if(in.is_open())
						{
							int x,y;
							std::string reader;
							getline(in,reader);
							x=atoi(reader.c_str());
							getline(in,reader);
							y=atoi(reader.c_str());
							if(free_lever_IDs.empty())
							{
								levers.push_back(Lever());
								levers[levers.size()-1].set_up(edit_event.mouse.x,edit_event.mouse.y,levers.size()-1,LEVER,ALLEGRO_KEY_E);
							}
							else
							{
								levers[free_lever_IDs[free_lever_IDs.size()-1]].set_up(edit_event.mouse.x,edit_event.mouse.y,free_lever_IDs[free_lever_IDs.size()-1],LEVER,ALLEGRO_KEY_E);
								free_lever_IDs.pop_back();
							}
						}

					}
					in.close();
				}
					remove("Levels/LevelEditor/temp_door.dat");
					remove("Levels/LevelEditor/temp_lever.dat");
			}
			//--Object Creation--//
	}
		//--RMB--//

		if(keyboard_input_specific(ALLEGRO_KEY_ESCAPE))
			edit_done=true;
		if(edit_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);									///////////APP CLOSING



		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		
		if(reload_level)
		{
			std::ifstream in(filePath+"/map.dat");
			if(in.is_open())
			{
				doors.clear();
				levers.clear();
				load_level(filePath,true);
			}
			reload_level=false;
		}
	}
}