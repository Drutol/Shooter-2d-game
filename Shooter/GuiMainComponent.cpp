#include "GuiMainComponent.h"


GuiMainComponent::GuiMainComponent()
{
	start_listener();
}


GuiMainComponent::~GuiMainComponent()
{
}

void GuiMainComponent::start_listener()
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) listener(this->ev_queue), this, NULL, NULL);
}

void listener(std::vector<game_event> &ev_queue)
{
	
}

