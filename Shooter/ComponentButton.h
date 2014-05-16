#pragma once
#include "GuiMainComponent.h"
class ComponentButton :
	public GuiMainComponent
{
public:
	void (*connected_event)(void);

	
	ComponentButton();
	ComponentButton::ComponentButton(void (*function_to_be_called)(void),int PosX,int PosY,int of_form_ID,string Text , ALLEGRO_COLOR rgb);
	~ComponentButton();
};

