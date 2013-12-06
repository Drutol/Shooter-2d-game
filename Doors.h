#pragma once

class Doors
{
private:
	int ID;
	int state;
	enum states {OPEN,CLOSED,OPENING,CLOSING};
	float crop_X;
	float crop_Y;
	float door_speed;
public:
	int tile_X;
	int tile_Y;
	bool exists;
	void update_map();
	void draw_door();
	void set_up(int tile_X,int tile_Y);
	void change_state();
	void calculate_crop();
	Doors(void);
	~Doors(void);
};

