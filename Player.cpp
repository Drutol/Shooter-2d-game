#include "Player.h"
#include "GameFunctions.h"

Player::Player(void)
{
	this->PosX=70;
	this->PosY=150;
	this->VelX=0;
	this->VelY=0;
	this->speed=3;
	this->on_ground=false;
	this->jump_height=32;
	this->jump_speed_base=6;
	this->jump_speed=6;
	this->can_move_left=true;
	this->can_move_right=true;
	this->can_fall=true;
	this->can_jump=true;
	this->force_ground=false;
	this->on_affection_box=false;
}


Player::~Player(void)
{
}
//MOVEMENT AND PHYSICS
void Player::player_apply_move()
{

	Player::player_set_direction(keyboard_input());
	if(is_tile_passable(current_tile_X_right_next,current_tile_Y))
		{
			if(keyboard_input_specific(ALLEGRO_KEY_RIGHT)&&can_move_right)
					{
						VelX++;
					}
		}
	if(is_tile_passable(current_tile_X_left_next,current_tile_Y)&&can_move_left)
		{
			if(keyboard_input_specific(ALLEGRO_KEY_LEFT))
					{
						VelX--;
					}
		}
	if(on_ground&&is_tile_passable(current_tile_X_left,current_tile_Y_up)&&is_tile_passable(current_tile_X_right,current_tile_Y_up)&&keyboard_input_specific(ALLEGRO_KEY_SPACE)&&can_jump)
			{
				VelY+=jump_height;
				on_ground=false;
			}
}



void Player::player_move()
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
	Player::player_locate();
	Player::player_fall();
	//cout<<current_tile_X_left<<endl<<current_tile_Y<<endl;
}

void Player::player_draw()
{
	al_draw_filled_rectangle(PosX,PosY,PosX+32,PosY+32,al_map_rgb(2,65,89));
}

void Player::player_locate()
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
void Player::player_set_direction(int ALLEGRO_KEY)
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
void Player::player_fall()
{
	if(!on_ground&&is_tile_passable(current_tile_X_right,current_tile_Y_below)&&is_tile_passable(current_tile_X_left,current_tile_Y_below)&&!check_for_box_below())
		VelY--;
	//cout<<on_ground<<endl;
}
void Player::remove_momentum(bool upwards)
{
	if(VelY>0&&upwards)
	VelY=0;
}
bool Player::check_for_box_below()
{
	for(int i=0;i<count_boxes();i++)
	{
		if(affection_boxes[i].check_if_inside(PosX,PosY+36)||affection_boxes[i].check_if_inside(PosX+32,PosY+36))
		{
			force_ground=true;
			return true;
		}
	}
	
	force_ground=false;
	return false;

}
//END OF MOVEMENT AND PHYSIC
int Player::player_get_posx()
{
	return PosX;
}
int Player::player_get_posy()
{
	return PosY;
}
void Player::player_die()
{
	PosX=70;
	PosY=150;
}
int Player::player_get_tile_X()
{
	return current_tile_X_right;
}
int Player::player_get_tile_Y()
{
	return current_tile_Y;
}