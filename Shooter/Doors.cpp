#include "Doors.h"
#include "link.h"
#include "GameFunctions.h"
std::vector<int> free_door_IDs;
Doors::Doors(void)
{
	this->exists=false;
	this->crop_X=0;
	this->crop_Y=64;
	this->door_speed=0.1;
}


Doors::~Doors(void)
{
	//if(exists)
	//{
	//	exists=false;
	//	map[tile_X][tile_Y].held_object=NOTHING;
	//	map[tile_X][tile_Y].held_object_ID=-1;
	//	free_door_IDs.push_back(ID);
	//}
}
void Doors::set_up(int tile_X,int tile_Y,int ID,int speed,int initial_state,int direction)
{
	exists=true;
	this->tile_X=tile_X;
	this->tile_Y=tile_Y;
	this->direction=direction;
	door_speed=speed;
	state=initial_state;
	if(initial_state==OPEN&&direction==UP)
		crop_Y=124;
	else if(initial_state==OPEN&&direction==DOWN)
		crop_Y=0;
	else if(initial_state==CLOSED)
		crop_Y=64;
	map[tile_X][tile_Y].held_object=DOOR;
	map[tile_X][tile_Y].held_object_ID=ID;
	this->initial_state=initial_state;
	Doors::update_map();

}
void Doors::update_map()
{
	if(state==OPEN)
	{
		map[tile_X][tile_Y].passable=true;
	}
	else if(state==CLOSED)
	{
		map[tile_X][tile_Y].passable=false;
	}
	else if(state==OPENING&&crop_Y>=96)
	{
		map[tile_X][tile_Y].passable=true;
	}
	else if(state==CLOSING&&crop_Y<=96)
	{
		map[tile_X][tile_Y].passable=false;
	}

}

void Doors::draw_door()
{
	if(exists)
	{
		Doors::calculate_crop();
		al_draw_bitmap_region(return_appropriate_bitmap("door"),crop_X,crop_Y,crop_X+TileSize,crop_Y+TileSize,tile_X*TileSize,tile_Y*TileSize,NULL);
	}
}

void Doors::change_state()
{
	int state_to;
	if(state==OPEN)
		state_to=CLOSED;
	else
		state_to=OPEN;

	if(this->state!=state_to)
	{
		if(state_to==CLOSED)
		{
			this->state=CLOSING;
		}
		else if(state_to==OPEN)
		{
			this->state=OPENING;
		}
	}
}

void Doors::calculate_crop()
{
	if(state==OPENING||state==CLOSING)
	{
		
		if(direction==UP)
		{
			if(state==OPENING)
			{
				crop_Y+=door_speed;
				if(crop_Y>=124)
					state=OPEN;
			}
			else if(state==CLOSING)
			{
				crop_Y-=door_speed;
				if(crop_Y<=64)
					state=CLOSED;
			}
		}
		else if(direction==DOWN)
		{
			if(state==OPENING)
			{
				crop_Y-=door_speed;
				if(crop_Y<=0)
					state=OPEN;
			}
			else if(state==CLOSING)
			{
				crop_Y+=door_speed;
				if(crop_Y>=64)
					state=CLOSED;
			}
		}
		Doors::update_map();
	}
}

void Doors::remove()
{
	free_door_IDs.push_back(map[tile_X][tile_Y].held_object_ID);
	this->exists=false;
	map[tile_X][tile_Y].held_object=NOTHING;
	map[tile_X][tile_Y].held_object_ID=-1;
	tile_X=tile_Y=0;
}