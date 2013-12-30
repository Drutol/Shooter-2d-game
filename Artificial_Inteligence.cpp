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
				if(Artificial_Inteligence::Estimate_distance()<radius)
					target_found=true;
			}
		}
		else
			Artificial_Inteligence::Estimate_distance();

	}
int Artificial_Inteligence::Estimate_distance(int to_box,int PosX,int PosY)
{
	if(to_box==-1)	
	return sqrt(pow((player.PosX-test_NPC.PosX),2)+pow((player.PosY-test_NPC.PosY),2));
	else if(to_box!=-1)
	return sqrt(pow((PosX-test_NPC.PosX),2)+pow((PosY-test_NPC.PosY),2));
}

void Artificial_Inteligence::Gather_data()
	{
		cout<<Estimate_distance()<<endl;
		if(Estimate_distance()>5&&Estimate_distance()<110)
		{
			
			cout<<path_done<<","<<path_failed<<endl;
			
			if(!path_created&&!path_done)
				Artificial_Inteligence::Prepare_path();
			else if(path_created&&!path_done)
			{
				Artificial_Inteligence::Take_path();
			}
			else if(path_done)
			{
				path_created=false;
				path_done=false;
				path.clear();
				path.push_back(direction());
			}
		}

	}
void Artificial_Inteligence::Take_path()											///////////////////////////////////////////////////////////////////////
	{
		for(int i=0;i<path.size()&&Estimate_distance()>15;i++)
		{
			for(int j=0;j<=path[i].how_far/4;j++)
			{
				if(path[i].dir==UP)
				{
						test_NPC.apply_move(ALLEGRO_KEY_SPACE);
				}
				if(path[i].dir==LEFT&&j%(int)test_NPC.speed==0)
				{
						test_NPC.apply_move(ALLEGRO_KEY_LEFT);
				}																							//WTF.WTF.WTF.WTF//			
				if(path[i].dir==RIGHT&&j%(int)test_NPC.speed==0)													
				{
						test_NPC.apply_move(ALLEGRO_KEY_RIGHT);
				}
			}
		}
		path_done=true;
	}																				/////////////////////////////////////////////////////////////////////////
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

			dummy = test_NPC;

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
				dummy.apply_move(NULL);		

				if(on_right&&!dummy.can_move_right||on_left&&!dummy.can_move_left)
				{
					dummy.apply_move(ALLEGRO_KEY_SPACE);
					path[path.size()-1].dir=UP;
					path.push_back(direction());

				}
				if(on_right)
				{
					if(dummy.can_move_right||falling)
					{
							int i;
							bool moved=false;
							for(i=0;i<TileSize&&dummy.PosX<player.PosX;i++)
							{
								
								check_affection_box_collision_NPC(3,dummy);
								if(dummy.can_move_right||falling)
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
					if(dummy.can_move_left||falling)
					{
							int i;
							bool moved=false;
							for(i=0;i<TileSize&&dummy.PosX>player.PosX;i++)
							{
			
								check_affection_box_collision_NPC(3,dummy);
								if(dummy.can_move_left||falling)
								{
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

				
				//if(!dummy.can_move_left)
				//	{cout<<"LEFT"<<endl;
				//_getch();}
				//if(!dummy.can_move_right)
				//	{cout<<"RIGHT"<<endl;
				//_getch();}
				if(above)
				{

				}
				else if(under)
				{

				}

				if(abs(player.PosX-dummy.PosX)<15)
				{
					path_created=true;
				}
				if(path.size()>20)
					path_failed=true;

			

			}
			cout<<"player"<<player.PosX<<","<<player.PosY<<endl;
			cout<<"dummy"<<dummy.PosX<<","<<dummy.PosY<<endl;
			
				DestX=dummy.PosX;
				DestY=dummy.PosY;
		}

	}

bool Artificial_Inteligence::check_logic(int action)
{
	if(action==MOVEMENT)
	{
		if(Artificial_Inteligence::Estimate_distance()>5)
			return true;
	}
	else if(action==IN_RANGE)
	{
		if(test_NPC.PosX>player.PosX-5&&test_NPC.PosX<player.PosX+5)
			return true;
	}


	return false;
}