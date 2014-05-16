#pragma once
#include "link.h"
#include "GameFunctions.h"
void listener(std::vector<game_event> &ev_queue);
class GuiMainComponent
{
private:
	int posX, posY;
public:
	void evaluate_event();
	void render();
	void fetch_action();
	void start_listener();
	void inject_stopper();
	std::vector<game_event> ev_queue;
	
	
	GuiMainComponent();
	~GuiMainComponent();
};

