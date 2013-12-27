#include "Dynamic_Object.h"
#include "GameFunctions.h"


Dynamic_Object::Dynamic_Object(void)
{
}


Dynamic_Object::~Dynamic_Object(void)
{
}

void Dynamic_Object::apply_move(int key)
{

	Dynamic_Object::set_direction(keyboard_input());
	if(!is_tile_passable(current_tile_X_right_next,current_tile_Y))
			can_move_right=false;
	if(!is_tile_passable(current_tile_X_left_next,current_tile_Y))
			can_move_left=false;
	if(!keyboard_enabled)
	{
		if(!can_move_right&&VelX>0)
			VelX=0;
		if(!can_move_left&&VelX<0)
			VelX=0;
	}
	
	if(is_tile_passable(current_tile_X_right_next,current_tile_Y))
		{
			if(keyboard_input_specific(ALLEGRO_KEY_RIGHT)&&can_move_right&&keyboard_enabled||!keyboard_enabled&&can_move_right&&key==ALLEGRO_KEY_RIGHT)
					{
						VelX++;
					}
		}

	if(is_tile_passable(current_tile_X_left_next,current_tile_Y))
		{
			if(keyboard_input_specific(ALLEGRO_KEY_LEFT)&&can_move_left&&keyboard_enabled||!keyboard_enabled&&can_move_left&&key==ALLEGRO_KEY_LEFT)
					{
						VelX--;
					}
		}

	if(on_ground&&is_tile_passable(current_tile_X_left,current_tile_Y_up)&&is_tile_passable(current_tile_X_right,current_tile_Y_up)&&keyboard_input_specific(ALLEGRO_KEY_SPACE)&&can_jump&&keyboard_enabled)
			{
				VelY+=jump_height;
				on_ground=false;
			}
	else if(on_ground&&is_tile_passable(current_tile_X_left,current_tile_Y_up)&&is_tile_passable(current_tile_X_right,current_tile_Y_up)&&key==ALLEGRO_KEY_SPACE&&can_jump&&!keyboard_enabled)
			{
				VelY+=jump_height;
				on_ground=false;
			}

}



void Dynamic_Object::move()
{
	//cout<<VelY<<endl;
	if(VelY>jump_height)
		VelY=jump_height;
	if(VelX>0)
	{
		PosX+=speed;
		VelX--;
		PosX_backup=PosX;
	}
	if(VelX<0)
	{
		PosX-=speed;
		VelX++;
		PosX_backup=PosX;
	}
	if(VelY>0)
	{
		PosY-=jump_speed;
		VelY--;
		PosY_backup=PosX;
	}
	if(VelY<0)
	{
		PosY+=speed;
		VelY++;
		PosY_backup=PosX;
	}
	Dynamic_Object::locate();
	Dynamic_Object::fall();
	//cout<<current_tile_X_left<<endl<<current_tile_Y<<endl;
}


void Dynamic_Object::locate()
{
	///
	current_tile_X_left=(int)((PosX/TileSize));
	current_tile_X_right=(int)(((PosX+29)/TileSize));
	current_tile_X_right_next=(int)(((PosX+33)/TileSize));
	current_tile_X_left_next=(int)(((PosX-3)/TileSize));
	///
	current_tile_Y=(PosY)/TileSize;
	current_tile_Y_below=(PosY+33)/TileSize;
	current_tile_Y_up=(PosY-TileSize)/TileSize;
	if(!is_tile_passable(current_tile_X_left,current_tile_Y_below)||!is_tile_passable(current_tile_X_right,current_tile_Y_below)||force_ground)
		on_ground=true;
	else
		on_ground=false;

	if(!is_tile_passable(current_tile_X_left,current_tile_Y)&&!is_tile_passable(current_tile_X_right,current_tile_Y))
	{
		VelX=0;
		VelY=0;
		if(PosX!=PosX_backup&&PosY!=PosY_backup)
		{
			PosX=PosX_backup;
			PosY=PosY_backup;
		}
		else
		{
			PosY+=10;
		}
	}
	if(!is_tile_passable(current_tile_X_left,(PosY-5)/TileSize)||!is_tile_passable(current_tile_X_left,(PosY-5)/TileSize))
		VelY=0;
	if((int)(PosY+32)%64!=0&&on_ground&&!check_for_box_below())
		PosY-=2;

}
void Dynamic_Object::set_direction(int ALLEGRO_KEY)
{
	if(ALLEGRO_KEY==ALLEGRO_KEY_RIGHT)
		direction=RIGHT;
	else if(ALLEGRO_KEY==ALLEGRO_KEY_LEFT)
		direction=LEFT;
	else if(ALLEGRO_KEY==ALLEGRO_KEY_UP)
		direction=UP;
	else if(ALLEGRO_KEY==ALLEGRO_KEY_DOWN)
		direction=DOWN;
}
void Dynamic_Object::fall()
{
	if(!on_ground&&is_tile_passable(current_tile_X_right,current_tile_Y_below)&&is_tile_passable(current_tile_X_left,current_tile_Y_below)&&!check_for_box_below())
		VelY--;
	//cout<<on_ground<<endl;
}
void Dynamic_Object::remove_momentum(bool upwards)
{
	if(VelY>0&&upwards)
	VelY=0;
}
bool Dynamic_Object::check_for_box_below()
{
	for(int i=0;i<count_boxes();i++)
	{
		if(affection_boxes[i].check_if_inside(PosX,PosY+36)||affection_boxes[i].check_if_inside(PosX+32,PosY+36)&&affection_boxes[i].check_flag(FLAG_UNPASSABLE,false))
		{
			force_ground=true;
			return true;
		}
	}
	
	force_ground=false;
	return false;

}
//END OF MOVEMENT AND PHYSIC
int Dynamic_Object::get_posx()
{
	return PosX;
}
int Dynamic_Object::get_posy()
{
	return PosY;
}
int Dynamic_Object::get_tile_X()
{
	return current_tile_X_right;
}
int Dynamic_Object::get_tile_Y()
{
	return current_tile_Y;
}