#include "Damage_manager.h"
#include "Multiplayer_Client.h"


Damage_manager::Damage_manager(void)
{
	active_projectiles.clear();
}


Damage_manager::~Damage_manager(void)
{
}

void Damage_manager::register_projectile(int at_x,int at_y,int to_x,int to_y,int speed,bool friendly)
{
	
	projectile temp_proj(to_x,to_y,at_x,at_y,speed,friendly);
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

void Damage_manager::slaughter_projectiles()
{
	for (size_t i = 0;i< projectiles_to_bo_removed.size(); i++)
	{
		active_projectiles[projectiles_to_bo_removed[i]].exists = false;

		free_projectile_ID.push_back(projectiles_to_bo_removed[i]);
		remove_affection_box(active_projectiles[projectiles_to_bo_removed[i]].box_ID);
	}
	projectiles_to_bo_removed.clear();
}

void Damage_manager::remove_projectile(int ID)
{
	projectiles_to_bo_removed.push_back(ID);
}

void Damage_manager::process_projectiles()
{
	for(int i=0;i<active_projectiles.size();i++)
	{
		if(active_projectiles[i].exists)
		{
			active_projectiles[i].move();
			check_player_collison();
			affection_boxes[active_projectiles[i].box_ID].move_box(active_projectiles[i].x,active_projectiles[i].y);
			if(affection_boxes[active_projectiles[i].box_ID].check_if_colides_static())
				remove_projectile(i);
		}
	}
	slaughter_projectiles();

}

void Damage_manager::check_player_collison()
{
	for (size_t i = 0; i < active_projectiles.size(); i++)
	{
		if (player.player_box.check_if_inside(active_projectiles[i].x,active_projectiles[i].y) && !active_projectiles[i].friendly)
		{
			player.health -= 5;
		}
	}
}