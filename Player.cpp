#include "Player.h"


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
}


Player::~Player(void)
{
}
//MOVEMENT AND PHYSICS
void Player::player_apply_move(int which_direction)
{
	Player::player_set_direction(which_direction);
	if(is_tile_passable(current_tile_X_right_next,current_tile_Y))
		{
			if(which_direction==ALLEGRO_KEY_RIGHT)
					{
						VelX++;
					}
		}
	if(is_tile_passable(current_tile_X_left_next,current_tile_Y))
		{
			if(which_direction==ALLEGRO_KEY_LEFT)
					{
						VelX--;
					}
		}
	if(on_ground&&is_tile_passable(current_tile_X_left,current_tile_Y_up)&&is_tile_passable(current_tile_X_right,current_tile_Y_up)&&which_direction==ALLEGRO_KEY_SPACE)
			{
				VelY+=jump_height;
			}
}



void Player::player_move()
{

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
	if(!is_tile_passable(current_tile_X_left,current_tile_Y_below)||!is_tile_passable(current_tile_X_right,current_tile_Y_below))
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
	if((int)(PosY+32)%64!=0&&on_ground)
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
	if(!on_ground&&is_tile_passable(current_tile_X_right,current_tile_Y_below)&&is_tile_passable(current_tile_X_left,current_tile_Y_below))
		VelY--;
}
//END OF MOVEMENT AND PHYSIC
float Player::player_get_posx()
{
	return PosX;
}
float Player::player_get_posy()
{
	return PosY;
}