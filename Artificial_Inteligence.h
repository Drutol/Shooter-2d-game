#pragma once
#include "link.h"
struct direction
{
	int dir;
	int how_far;
};
class Artificial_Inteligence
{
private:
	bool target_found;
	bool path_created;
	bool path_failed;
	bool path_done;
	std::vector<direction> path;
public:
	int behaviour_flag;
	int Estimate_distance(int to_box);
	void Gather_data();
	void Take_path();
	void Make_step();
	void Fullfil_destiny();
	void Find_enemy(int radius);
	void Prepare_path();







	Artificial_Inteligence(void);
	~Artificial_Inteligence(void);
};

