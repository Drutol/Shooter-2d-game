#include "Interactive_object.h"
#include "GameFunctions.h"
#include "link.h"

Interactive_object::Interactive_object(void)
{
	this->connections=0;
}


Interactive_object::~Interactive_object(void)
{
}

void Interactive_object::create_array_of_affected_objects(int how_many)
{
	affected_object = new object[how_many];
}

void Interactive_object::add_affected_objects(int type,int ID)
{
	affected_object[connections].ID=ID;
	affected_object[connections].type=type;
	connections++;
}

void Interactive_object::object_draw()
{
	
	al_draw_bitmap(return_appropriate_bitmap(bitmap),PosX,PosY,NULL);
}

void Interactive_object::set_up(int how_many_connections,int x,int y,int object_type)
{
	create_array_of_affected_objects(how_many_connections);
	PosX=x;
	PosY=y;
	exists=true;
	map[PosX/TileSize][PosY/TileSize].held_object=object_type;
}

void Interactive_object::send_state()
{
	for(int i=0;i<connections;i++)
	{
		if(affected_object[i].type==DOOR)
			doors[affected_object[i].ID].change_state();

	}

}