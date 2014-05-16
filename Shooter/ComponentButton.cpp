#include "ComponentButton.h"


ComponentButton::ComponentButton(void (*function_to_be_called)(void))
{
	this->connected_event = function_to_be_called;
}


ComponentButton::~ComponentButton()
{
}
