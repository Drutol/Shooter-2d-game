#pragma once
#include "link.h"
#include "Dynamic_Object.h"
using namespace std;
class Player: public Dynamic_Object
{

public:
	float health;
	ALLEGRO_BITMAP *player_bitmap;
	void die();
	void draw();
	Player();
	~Player();
};

