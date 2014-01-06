#pragma once
#include "link.h"
enum actions {IDLE,MOVEMENT,IN_RANGE};
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
	std::vector<direction> uncomfirmed_path;
	int DestX;
	int DestY;
	bool stuck;
	int current_path_element;
public:
	int behaviour_flag;
	int Estimate_distance(int to_box=-1,int PosX=0,int PosY=0);
	void Gather_data();
	void Take_path();
	bool Make_step(int dir);
	void Fullfil_destiny();
	void Find_enemy(int radius);
	void Prepare_path();
	bool check_logic(int action);
	void merge_paths();





	Artificial_Inteligence(void);
	~Artificial_Inteligence(void);
};

