#include "GuiMainComponent.h"


GuiMainComponent::GuiMainComponent()
{

}


GuiMainComponent::~GuiMainComponent()
{
}


void GuiMainComponent::recv_event(int ev)
{
	last_event = ev;
}
