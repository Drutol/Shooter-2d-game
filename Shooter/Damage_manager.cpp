#include "Damage_manager.h"


Damage_manager::Damage_manager(void)
{
}


Damage_manager::~Damage_manager(void)
{
}

void Damage_manager::register_projectile(int at_x,int at_y,int to_x,int to_y,int speed)
{
	
	projectile temp_proj(to_x,to_y,at_x,at_y,speed);
	if(free_projectile_ID.empty())
	{
		temp_proj.ID=active_projectiles.size()-1;	
		active_projectiles.push_back(temp_proj);
		Damage_manager::register_affection_box(active_projectiles[active_projectiles.size()-1]);
	}
	else
	{
		temp_proj.ID=free_projectile_ID[free_projectile_ID.size()-1];
		active_projectiles[free_projectile_ID[free_projectile_ID.size()-1]]=temp_proj;
		Damage_manager::register_affection_box(active_projectiles[free_projectile_ID[free_projectile_ID.size()-1]]);
		free_projectile_ID.pop_back();
	}
	
}

void Damage_manager::register_affection_box(projectile &proj)
{
	if(free_box_IDs.empty())
	{
		affection_boxes.push_back(Affection_box());
		affection_boxes[affection_boxes.size()-1].set_up(proj.x,proj.y,20,10,NON_STATIC_PROJECTILE,proj.ID,affection_boxes.size()-1);
		proj.box_ID=affection_boxes.size()-1;
	}
	else
	{
		affection_boxes[free_box_IDs[free_box_IDs.size()-1]].set_up(proj.x,proj.y,20,10,NON_STATIC_PROJECTILE,proj.ID,free_box_IDs.size()-1);
		proj.box_ID=free_box_IDs[free_box_IDs.size()-1];
		free_box_IDs.pop_back();
	}

}

void Damage_manager::remove_projectile(int ID)
{
	remove_affection_box(active_projectiles[ID].box_ID);
	active_projectiles[ID]=projectile();
	free_projectile_ID.push_back(ID);
}

void Damage_manager::process_projectiles()
{
	for(int i=0;i<active_projectiles.size();i++)
	{
		if(active_projectiles[i].exists)
		{
			active_projectiles[i].move();
			
			affection_boxes[active_projectiles[i].box_ID].move_box(active_projectiles[i].x,active_projectiles[i].y);
			if(affection_boxes[active_projectiles[i].box_ID].check_if_colides_static())
				remove_projectile(i);
		}
	}

}