#include "Affection_box.h"
#include "link.h"
#include "GameFunctions.h"
std::vector<int> free_box_IDs;
Affection_box::Affection_box(void)
{
	exists=false;
}


Affection_box::~Affection_box(void)
{
}


////////////////////////////////////////////////////////////////////////////////////////////////			FLAGS STUFF
int Affection_box::check_flag(int which,bool want_index)
{
	if(!flags.empty())
	{
		for(int i=0;i<flags.size();i++)
		{
			if(flags[i]==which)
			{
				if(want_index)
					return i;
				else
					return true;

			}
		}
	}
	if(want_index)
		return -1;
	else
		return false;
}
void Affection_box::add_flag(int flag)
{
	flags.push_back(flag);
}
void Affection_box::remove_flag(int flag)
{
	flags[check_flag(flag,true)]=NULL;
}



////////////////////////////////////////////////////////////////////////////////////////////////			FLAGS STUFF
void Affection_box::set_up(int x,int y,int width,int height,int object_type,int object_ID,int box_ID)
{
	exists=true;
	ID=box_ID;
	PosX_left=x;
	PosX_right=x+width;
	PosY_top=y;
	PosY_bottom=y+height;
	//map[(int)PosX_left*TileSize][(int)PosY_top*TileSize].held_object=BOX;
	//map[(int)PosX_left*TileSize][(int)PosY_top*TileSize].held_object_ID=box_ID;
	if(object_type!=NOTHING)
	{
		held_object.type=object_type;
		held_object.ID=object_ID;
	}
	if(height<32)
		shorter_than_player=true;
	else
		shorter_than_player=false;

}
void Affection_box::debug_draw_frame()
{
	if(exists)	
	al_draw_rectangle(PosX_left,PosY_top,PosX_right,PosY_bottom,al_map_rgb(68,23,99),30);

}
bool Affection_box::check_if_inside(int x,int y)
{
	if(x>=PosX_left&&x<=PosX_right)
	{
		if(y>=PosY_top&&y<=PosY_bottom)
		{
			return true;
		}
	}
	return false;
}
bool Affection_box::check_if_colides_static()
{
	int tile_left;
	int tile_right;
	int tile_y;

	tile_left=PosX_left/TileSize;
	tile_right=PosX_right/TileSize;
	tile_y=PosY_top/TileSize;

	if(!map[tile_left][tile_y].passable)
		return true;
	else if(!map[tile_right][tile_y].passable)
		return true;
	else return false;
}

void Affection_box::move_box(int x,int y)
{
	PosX_left=x;
	PosX_right=PosX_left+width;
	PosY_top=y;
	PosY_bottom=PosY_top-height;
}