#include "Artificial_Inteligence.h"
#include "GameFunctions.h"
#include "link.h"
Artificial_Inteligence::Artificial_Inteligence(void)
{
	this->path.push_back(direction());
	this->target_found=false;
	this->path_created=false;
	this->path_failed=false;
	this->path_done=false;
}



Artificial_Inteligence::~Artificial_Inteligence(void)
{
}
void Artificial_Inteligence::Find_enemy(int radius)
	{
		if(!target_found)
		for(int i=0;i<count_boxes();i++)
		{
			if(affection_boxes[i].check_flag(FLAG_PLAYER,false))
			{
				if(Artificial_Inteligence::Estimate_distance(i)<radius)
					target_found=true;
			}
		}
		else
			Artificial_Inteligence::Estimate_distance(0);

	}
int Artificial_Inteligence::Estimate_distance(int to_box)
{
	int distance=sqrt(pow((player.PosX-test_NPC.PosX),2)+pow((player.PosY-test_NPC.PosY),2));
	return distance;
}
void Artificial_Inteligence::Gather_data()
	{
		if(Artificial_Inteligence::Estimate_distance(0)<100&&!path_created)
			Artificial_Inteligence::Prepare_path();
		if(path_created&&!path_done)
		{
			Artificial_Inteligence::Take_path();
		}

	}
void Artificial_Inteligence::Take_path()
	{
		for(int i=0;i<path.size();i++)
		{
			cout<<path[i].dir<<endl;
			for(int j=0;j<=path[i].how_far/(int)test_NPC.speed;j++)
			{
				if(path[i].dir==LEFT)
				test_NPC.apply_move(ALLEGRO_KEY_LEFT);
				else if(path[i].dir==RIGHT)
				test_NPC.apply_move(ALLEGRO_KEY_RIGHT);
			}
		}
		path_done=true;
	}
void Artificial_Inteligence::Make_step()
	{

	}
void Artificial_Inteligence::Fullfil_destiny()
	{

	}
void Artificial_Inteligence::Prepare_path()
	{
		if(!path_created&&!path_failed)
		{
			NPC dummy;
			coords Player_coords;
			coords NPC_coords;
			Player_coords.x=player.get_posx();
			Player_coords.y=player.get_posy();

			NPC_coords.x=test_NPC.PosX;
			NPC_coords.y=test_NPC.PosY;

			dummy.PosX=NPC_coords.x;
			dummy.PosY=NPC_coords.y;

			bool on_left;
			bool on_right;
			bool above;
			bool under;
			bool falling;
			
			
			while(!path_created&&!path_failed)
			{

				check_affection_box_collision_NPC(3,dummy);
				if(!dummy.on_ground)
					falling=true;
				else
					falling=true;
				if(player.PosX>dummy.PosX)
				{
					on_right=true;
					on_left=false;
				}
				else
				{
					on_right=false;
					on_left=true;
				}
				if(Player_coords.y>NPC_coords.y)
				{
					above=true;
					under=false;
				}
				else
				{
					above=false;
					under=true;
				}
				if(on_right)
				{
					if(dummy.can_move_left)
					{
							int i;
							bool moved=false;
							for(i=0;i<TileSize&&dummy.PosX<player.PosX;i++)
							{
			
								check_affection_box_collision_NPC(3,dummy);
								if(dummy.can_move_right)
								{
									dummy.PosX++;
									moved=true;
								}
								else
								{
									path[path.size()-1].dir=RIGHT;
									path[path.size()-1].how_far=i;
									path.push_back(direction());
									moved=false;
									break;
								}
							}
					
							if(moved)
							{
									path[path.size()-1].dir=RIGHT;
									path[path.size()-1].how_far=i;
									path.push_back(direction());
							}
					}

				}
				else if(on_left)
				{
					if(dummy.can_move_left)
					{
							int i;
							bool moved=false;
							for(i=0;i<TileSize&&dummy.PosX>player.PosX;i++)
							{
			
								check_affection_box_collision_NPC(3,dummy);
								if(dummy.can_move_left)
								{
									cout<<"I'm here"<<endl;	
									dummy.PosX--;
									moved=true;
								}
								else
								{
									path[path.size()-1].dir=LEFT;
									path[path.size()-1].how_far=i;
									path.push_back(direction());
									moved=false;
									break;
								}
							}
					
							if(moved)
							{
									path[path.size()-1].dir=LEFT;
									path[path.size()-1].how_far=i;
									path.push_back(direction());
							}
					}

				}
				if(above)
				{

				}
				else if(under)
				{

				}

				if(abs(player.PosX-dummy.PosX)<10)
				{
					path_created=true;
				}
				if(path.size()>20)
					path_failed=true;

			}
			cout<<"player"<<player.PosX<<","<<player.PosY<<endl;
			cout<<"dummy"<<dummy.PosX<<","<<dummy.PosY<<endl;
			cout<<path.size()<<endl;
		}

	}