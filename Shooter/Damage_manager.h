#pragma once
#include "link.h"
#include "GameFunctions.h"
class Damage_manager
{
private:
		struct projectile
		{
			float x,y,a,b,t;
			int x_to,y_to;
			int speed;
			int ID,box_ID;
			bool parabolic;
			bool moving;
			bool exists;
			int dir;
			bool friendly;
			void move()
			{
				calculate_height();
				draw();
			}
			void draw()
			{
				al_draw_filled_rectangle(x,y,x+20,y+10,al_map_rgb(255,0,0));
			}
			void calculate_height()
			{
				if(!parabolic)
				{
					if(dir==0)x+=1;
					else if(dir==1)x-=1;
					y=a*x+b;
				}
			}
			void set_movement_pattern()
			{
				a=(y_to-y)/(x_to-x);
				b=y-a*x;
			}
			projectile(int x_to,int y_to,int x,int y,int speed,bool friendly)
			{
				this->x=x;
				this->y=y;
				this->x_to=x_to;
				this->y_to=y_to;
				this->t=0;
				this->speed=speed;
				this->moving=false;
				this->parabolic=false;
				this->exists=true;
				this->friendly = friendly;
				if(x>x_to)
					dir=1;
				else if(x<x_to)
					dir=0;
				set_movement_pattern();
			}
			projectile()
			{
				this->exists=false;
			}

		};
		void register_affection_box(projectile &proj);
		std::vector<int> free_projectile_ID;
public:
	//--Shooting--//
	
	std::vector<projectile> active_projectiles;
	void register_projectile(int at_x,int at_y,int to_x,int to_y,int speed,bool friendly);
	void process_projectiles();
	void remove_projectile(int ID);
	void update_boxes();
	void check_player_collison();
	//--Shotting--//
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	Damage_manager(void);
	~Damage_manager(void);
};

