#pragma once
#include "link.h"
#include "Dynamic_Object.h"
#include "Affection_box.h"
class Player: public Dynamic_Object
{

public:
	float health;
	Affection_box player_box;
	ALLEGRO_BITMAP *player_bitmap;
	void die();
	void draw();
	Player();
	~Player();
};

