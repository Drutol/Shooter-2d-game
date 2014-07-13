#pragma once
#include "GuiMainComponent.h"
#include "link.h"
class ComponentTextBox : public GuiMainComponent
{
public:
	string string_to_display;
	ComponentTextBox(int x, int y, string text);
	void draw_text();
	
	ComponentTextBox();
	~ComponentTextBox();
};

