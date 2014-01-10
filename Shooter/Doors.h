#pragma once

class Doors
{
private:
	int ID;
	float crop_X;
	float crop_Y;
public:
	int tile_X;
	int tile_Y;
	int state;
	int direction;
	float door_speed;
	bool exists;
	void update_map();
	void draw_door();
	void set_up(int tile_X,int tile_Y,int ID,int speed,int initial_state,int direction);
	void change_state();
	void calculate_crop();
	Doors(void);
	~Doors(void);
};

