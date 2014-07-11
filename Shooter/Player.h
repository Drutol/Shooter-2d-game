#pragma once
#include "link.h"
#include "Dynamic_Object.h"
class Player: public Dynamic_Object
{

public:
	float health;
	int box_ID;
	ALLEGRO_BITMAP *player_bitmap;
	void die();
	void draw();
	Player();
	~Player();
};

