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
	this->keyboard_enabled=true;
	this->shoot_CD = 0;
	player_box.set_up(PosX, PosY, 32, 32, OBJECT_PLAYER, NULL, affection_boxes.size() - 1);
	health = 100;
}


Player::~Player(void)
{
}
//MOVEMENT AND PHYSICS

void Player::die()
{
	PosX=70;
	PosY=150;
}
void Player::draw()
{
	al_draw_filled_rectangle(PosX,PosY,PosX+32,PosY+32,al_map_rgb(2,65,89));
}