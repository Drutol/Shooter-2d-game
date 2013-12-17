#include "Affection_box.h"
#include "link.h"
#include "GameFunctions.h"
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
	for(int i=0;i<all_flags;i++)
	{
		if(flags[i]==which)
		{
			if(want_index)			
				return i;
			else
				return true;
		}
	}
	if(want_index)			
		return -1;
	else
		return false;
}
void Affection_box::add_flags(int number_of_flags, ...)
{
	va_list passed_flags;
	va_start(passed_flags,number_of_flags);
	all_flags=number_of_flags;
	flags = new int[number_of_flags];

	for(int i=0;i<number_of_flags;i++)
	{
		flags[i]=va_arg(passed_flags,int);
	}

	va_end(passed_flags);
}
void Affection_box::add_flag(int flag)
{
	int index = Affection_box::check_flag(flag,true);	
	if(index==-1)
	{
		int space = find_first_free_space();
		if(space==-1)
			{
				Affection_box::resize_array();
				space=all_flags-1;
			}
		flags[space]=flag;
	}
}
void Affection_box::remove_flag(int flag)
{
	for(int i=0;i<all_flags;i++)
	{
		if(flags[i]==flag)
			flags[i]=NULL;
	}
}

int Affection_box::find_first_free_space()
{
	for(int i=0;i<all_flags;i++)
	{
		if(flags[i]==NULL)
			return i;
	}
	return -1;
}

void Affection_box::resize_array()
{
	int *temp;
	temp = new int[all_flags+1];

	memcpy(temp,flags,all_flags+1);

	delete[] flags;
	flags = temp;
	all_flags++;
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
	if(object_type!=NOTHING)
	{
		held_object.type=object_type;
		held_object.ID=object_ID;
	}

}
void Affection_box::debug_draw_frame()
{
	if(exists)	
	al_draw_rectangle(PosX_left,PosY_top,PosX_right,PosY_bottom,al_map_rgb(68,23,99),5);

}
bool Affection_box::check_if_inside(int x,int y)
{
	if(x>PosX_left&&x<PosX_right)
	{
		if(y>PosY_top&&y<PosY_bottom)
		{
			return true;
		}
	}
	return false;
}