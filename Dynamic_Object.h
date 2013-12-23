#pragma once
#include "link.h"
class Dynamic_Object
{
protected:
	float PosX_backup;
	float PosY_backup;
	float VelX;
	float VelY;
	int current_tile_X_left;
	int current_tile_X_right;
	int current_tile_X_left_next;
	int current_tile_X_right_next;
	int current_tile_Y;

	int current_tile_Y_up;
	int direction;
	int jump_height;
	int jump_speed;
	int jump_speed_base;

public:
	//PHYSICS STUFF
	float speed;
	bool keyboard_enabled;
	bool on_ground;
	float PosX;
	float PosY;
	int current_tile_Y_below;
	void apply_move(int key);
	void move();
	void draw();
	void locate();
	void set_direction(int ALLEGRO_KEY);
	void fall();
	void remove_momentum(bool upwards);
	bool check_for_box_below();
	bool can_move_right;
	bool can_move_left;
	bool can_jump;
	bool can_fall;
	bool force_ground;
	bool on_affection_box;
	//PHYSICS STUFF END
	int get_posx();
	int get_posy();
	int get_tile_X();
	int get_tile_Y();

	Dynamic_Object();
	~Dynamic_Object();

};

