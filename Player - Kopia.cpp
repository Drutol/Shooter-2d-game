#include "Player.h"


Player::Player(void)
{
	this->PosX=70;
	this->PosY=150;
	this->VelX=0;
	this->VelY=0;
	this->speed=3;
	this->current_tile_X=PosX/TileSize;
	this->current_tile_Y=PosY/TileSize;
	this->on_ground=false;
	this->jump_height=25;
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
	if(is_tile_passable(current_tile_X,current_tile_Y)||is_tile_passable(current_tile_X-1,current_tile_Y)&&direction==LEFT)
		{
			if(which_direction==ALLEGRO_KEY_RIGHT&&is_tile_passable((int)(PosX+37)/TileSize,current_tile_Y))
					{
						VelX++;
					}
		}
	if(is_tile_passable(current_tile_X,current_tile_Y)||is_tile_passable(current_tile_X+1,current_tile_Y)&&direction==RIGHT)
		{
			if(which_direction==ALLEGRO_KEY_LEFT&&is_tile_passable((int)(PosX-5)/TileSize,current_tile_Y))
					{
						VelX--;
					}
		}
	if(which_direction==ALLEGRO_KEY_SPACE&&on_ground&&is_tile_passable((int)(PosX-3)/TileSize,current_tile_Y-1)&&is_tile_passable((int)(PosX+33)/TileSize,current_tile_Y-1))
			{
				VelY+=jump_height;
			}
		if(which_direction==ALLEGRO_KEY_DOWN)
			{
				VelY++;
			}
}



void Player::player_move()
{
	std::cout<<is_tile_passable(current_tile_X,current_tile_Y);
	
	if(VelX>0)
	{
		PosX+=speed;
		VelX--;
	}
	if(VelX<0)
	{
		PosX-=speed;
		VelX++;
	}
	if(VelY>0)
	{
		PosY-=jump_speed;
		VelY--;
	}
	if(VelY<0)
	{
		PosY+=speed;
		VelY++;
	}
	Player::player_locate();
	Player::player_fall();
}

void Player::player_draw()
{
	al_draw_filled_rectangle(PosX,PosY,PosX+32,PosY+32,al_map_rgb(2,65,89));
}

void Player::player_locate()
{
	if(direction==RIGHT)
	{
		current_tile_X=(PosX+33)/TileSize;
	}
	else if(direction==LEFT)
	{
		current_tile_X=(PosX)/TileSize;
	}
	
	current_tile_Y=(PosY+32)/TileSize;
	if(is_tile_passable(current_tile_X,current_tile_Y))
		PosY--;
	if((int)(PosY+32)%64==0&&!is_tile_passable((PosX+32)/TileSize,current_tile_Y+1)||(int)(PosY+32)%64==1&&!is_tile_passable((PosX-1)/TileSize,current_tile_Y))
	{
		on_ground=true;
	}
	else
	{
		on_ground=false;
	}

	if(on_ground)
	{
		current_tile_Y--;
	}


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
	if(is_tile_passable((PosX+33)/TileSize,current_tile_Y)&&is_tile_passable((PosX-3)/TileSize,current_tile_Y)&&!on_ground)

		VelY--;
}
//END OF MOVEMENT AND PHYSIC