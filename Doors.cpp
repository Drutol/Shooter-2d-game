#include "Doors.h"
#include "link.h"
#include "GameFunctions.h"

Doors::Doors(void)
{
	this->exists=false;
	this->state=CLOSED;
	this->crop_X=0;
	this->crop_Y=64;
	this->door_speed=0.1;
}


Doors::~Doors(void)
{
}
void Doors::set_up(int tile_X,int tile_Y)
{
	this->tile_X=tile_X;
	this->tile_Y=tile_Y;
	exists=true;
	Doors::update_map();
}
void Doors::update_map()
{
	if(state==OPEN)
	{
		overwrite_tile(tile_X,tile_Y,1,"NULL");
	}
	else if(state==CLOSED)
	{
		overwrite_tile(tile_X,tile_Y,0,"NULL");
	}
	else if(state==OPENING&&crop_Y>=96)
	{
		overwrite_tile(tile_X,tile_Y,1,"NULL");
	}
	else if(state==CLOSING&&crop_Y<=96)
	{
		overwrite_tile(tile_X,tile_Y,0,"NULL");
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
	
	if(check_if_player_under_door(crop_Y))
		state=state_to;

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
		Doors::update_map();
	}
}