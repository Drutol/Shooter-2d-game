#include "NPC.h"


NPC::NPC(void)
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
	this->keyboard_enabled=false;
}


NPC::~NPC(void)
{
}

void NPC::draw()
{
	al_draw_filled_rectangle(PosX,PosY,PosX+32,PosY+32,al_map_rgb(230,65,89));
}