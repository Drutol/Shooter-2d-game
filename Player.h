#pragma once
#include "link.h"
using namespace std;
class Player
{
private:
	float PosX;
	float PosY;
	float PosX_backup;
	float PosY_backup;
	float VelX;
	float VelY;
	float health;
	float speed;
	int current_tile_X_left;
	int current_tile_X_right;
	int current_tile_X_left_next;
	int current_tile_X_right_next;
	int current_tile_Y;
	int current_tile_Y_below;
	int current_tile_Y_up;
	bool on_ground;
	ALLEGRO_BITMAP *player_bitmap;
	int direction;
	int jump_height;
	int jump_speed;
	int jump_speed_base;

public:
	//PHYSICS STUFF
	void player_apply_move();
	void player_move();
	void player_draw();
	void player_locate();
	void player_set_direction(int ALLEGRO_KEY);
	void player_fall();
	void remove_momentum(bool upwards);
	bool can_move_right;
	bool can_move_left;
	bool can_jump;
	bool can_fall;
	bool force_ground;
	//PHYSICS STUFF END
	float player_get_posx();
	float player_get_posy();
	int player_get_tile_X();
	int player_get_tile_Y();
	void player_die();

	Player(void);
	~Player(void);
};

