#include "Damage_manager.h"


Damage_manager::Damage_manager(void)
{
}


Damage_manager::~Damage_manager(void)
{
}

void Damage_manager::register_projectile(int at_x,int at_y,int to_x,int to_y,int speed)
{
	active_projectiles.push_back(projectile(to_x,to_y,at_x,at_y,speed));
	Damage_manager::register_affection_box();
}

void Damage_manager::register_affection_box()
{

}