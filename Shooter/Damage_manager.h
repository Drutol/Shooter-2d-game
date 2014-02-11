#pragma once
#include "link.h"
#include"GameFunctions.h"
class Damage_manager
{
private:
		void register_affection_box();
		struct projectile
		{
			int x,y,a,b,t;
			int x_to,y_to;
			int speed;
			bool parabolic;
			bool moving;

			void move()
			{
				calculate_height();
				draw();
			}
			void draw()
			{
				al_draw_rectangle(x,y,x+10,y+20,al_map_rgb(255,0,0),5);
			}
			void calculate_height()
			{
				if(!parabolic)
				{
					y=a*x+b;
				}
			}
			void set_movement_pattern()
			{
				a=(y_to-y)/(x_to-x);
				b=y-a*x;
			}
			projectile(int x_to,int y_to,int x,int y,int speed)
			{
				this->x=x;
				this->y=y;
				this->x_to=x_to;
				this->y_to=y_to;
				this->t=0;
				this->speed=speed;
				this->moving=false;
				this->parabolic=false;
			}
		};
public:
	//--Shooting--//
	
	std::vector<projectile> active_projectiles;
	void register_projectile(int at_x,int at_y,int to_x,int to_y,int speed);
	void process_projectiles();
	void remove_projectile();
	//--Shotting--//
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	Damage_manager(void);
	~Damage_manager(void);
};

