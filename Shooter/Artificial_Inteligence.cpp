#include "Artificial_Inteligence.h"
#include "GameFunctions.h"
#include "link.h"
Artificial_Inteligence::Artificial_Inteligence(void)
{
	this->uncomfirmed_path.push_back(direction());
	this->path.push_back(direction());
	this->target_found=false;
	this->path_created=false;
	this->path_failed=false;
	this->path_done=false;
	this->stuck=false;
	this->current_path_element=0;
}



Artificial_Inteligence::~Artificial_Inteligence(void)
{
}
void Artificial_Inteligence::Find_enemy(int radius)
	{
		if(!target_found)
			for(int i=0;i<affection_boxes.size();i++)
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
		return sqrt(pow((player.PosX-PosX),2)+pow((player.PosY-PosY),2));
}

void Artificial_Inteligence::Gather_data()
	{
		if(Estimate_distance()>20&&Estimate_distance()<110)
		{	
			if(!path_created&&!path_done)
				Artificial_Inteligence::Prepare_path();
		}
		if(path_created&&!path_done)
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
		//TODO Timer class for stuck

	}
void Artificial_Inteligence::Take_path()											///////////////////////////////////////////////////////////////////////
	{
		if(current_path_element<path.size())
		{
			if(path[current_path_element].dir==RIGHT)
			{
				if(path[current_path_element].how_far>0)
				{
					test_NPC.apply_move(ALLEGRO_KEY_RIGHT);
					path[current_path_element].how_far--;
				}
				else
					current_path_element++;
			}
			if(path[current_path_element].dir==LEFT)
			{
				if(path[current_path_element].how_far>0)
				{
					test_NPC.apply_move(ALLEGRO_KEY_LEFT);
					path[current_path_element].how_far--;
				}
				else
					current_path_element++;
			}
			if(path[current_path_element].dir==UP)
			{
			if(path[current_path_element].how_far>0)
				{
					test_NPC.apply_move(ALLEGRO_KEY_SPACE);
					path[current_path_element].how_far--;
				}
				else
					current_path_element++;

			}

		}
		else
		{
			path_done=true;
			current_path_element=0;
		}
	}																				/////////////////////////////////////////////////////////////////////////
bool Artificial_Inteligence::Make_step(int dir)
{
		check_affection_box_collision_NPC(3,dummy);
		dummy.apply_move(NULL);	
		bool done=false;
		while(!done)
			{
			
			dummy.move();
			cout<<dummy.PosY<<endl;
			cout<<dir<<endl;

			if(dir==RIGHT)
			{
				if(dummy.can_move_right||!dummy.on_ground)
				{
					int counter=0;
					while(dummy.can_move_right||!dummy.on_ground)
					{
						check_affection_box_collision_NPC(3,dummy);
						
						dummy.apply_move(ALLEGRO_KEY_RIGHT);
						dummy.move();
						
						if(Estimate_distance(0,dummy.PosX,dummy.PosY)<15||!dummy.can_move_right)
							break;
						if(abs(player.PosX-dummy.PosX)<15)
							break;
						counter++;
					}
					if(counter>0)
					{
						uncomfirmed_path[uncomfirmed_path.size()-1].dir=RIGHT;
						uncomfirmed_path[uncomfirmed_path.size()-1].how_far=counter;
						uncomfirmed_path.push_back(direction());
					}
				}
			}
			if(dir==LEFT)
			{
				if(dummy.can_move_left||!dummy.on_ground)
				{
					int counter=0;
					while(dummy.can_move_left||!dummy.on_ground)
					{
						check_affection_box_collision_NPC(3,dummy);
						
						dummy.apply_move(ALLEGRO_KEY_LEFT);
						dummy.move();
						if(Estimate_distance(0,dummy.PosX,dummy.PosY)<15||!dummy.can_move_left)
							break;
						if(abs(player.PosX-dummy.PosX)<15)
							break;
						counter++;
					}
					if(counter>0)
					{
						uncomfirmed_path[uncomfirmed_path.size()-1].dir=LEFT;
						uncomfirmed_path[uncomfirmed_path.size()-1].how_far=counter;
						uncomfirmed_path.push_back(direction());
					}
				}
			}
			if(abs(player.PosY-dummy.PosY)>15&&dummy.on_ground||player.PosX>dummy.PosX&&!dummy.can_move_right||player.PosX<dummy.PosX&&!dummy.can_move_left)
			{
				bool above=false;
				bool under=false;
				bool on_right=false;
				bool on_left=false;
				
				if(player.PosX>dummy.PosX)
					on_right=true;
				else
					on_left=true;
				if(player.PosY<dummy.PosY)
					above=true;
				else
					under=true;

				if(on_right&&!dummy.can_move_right||on_left&&!dummy.can_move_left)
				{
					
						dummy.apply_move(ALLEGRO_KEY_SPACE);
						dummy.move();
						uncomfirmed_path[uncomfirmed_path.size()-1].dir=UP;
						uncomfirmed_path[uncomfirmed_path.size()-1].how_far=1;
						uncomfirmed_path.push_back(direction());
				}
				if(on_right)
					dir=RIGHT;
				if(on_left)
					dir=LEFT;
			}
			if(Estimate_distance(0,dummy.PosX,dummy.PosY)<15||abs(player.PosX-dummy.PosX)<15)
				done=true;

		}
		if(done)
			return true;
		else
			return false;
	
}
void Artificial_Inteligence::Fullfil_destiny()
	{

	}

void Artificial_Inteligence::Prepare_path()
{
		if(!path_created&&!path_failed)
		{
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
			
			int first_dir_to_check;

			while(!path_created&&!path_failed&&!stuck)
			{
				
				check_affection_box_collision_NPC(3,dummy);
				dummy.apply_move(NULL);	
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
				if(Player_coords.y==NPC_coords.y)
				{
					above=false;
					under=false;
				}
				
				


				
					if(on_right)
					{
						
						bool succes=Make_step(RIGHT);
						if(succes)
							merge_paths();
						else
							succes=Make_step(LEFT);
						if(succes)
							merge_paths();

					}
					if(on_left)
					{
						
						bool succes=Make_step(LEFT);
						if(succes)
							merge_paths();
						else
							succes=Make_step(RIGHT);
						if(succes)
							merge_paths();
					}
				
				
		
			
			
			path_created=true;
			
			
			
			
			
			}//While
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		}//Main check





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

void Artificial_Inteligence::merge_paths()
{
	try
	{
		if(uncomfirmed_path.size()>0)
		{
			for(int i=0;i<uncomfirmed_path.size();i++)
			{
				path.push_back(uncomfirmed_path[i]);
			}
		
			uncomfirmed_path.clear();
			uncomfirmed_path.push_back(direction());
		
		}
		else throw -1;
	}
	catch(int ex)
	{
		cout<<ex<<endl;
		_getch();
	}
}