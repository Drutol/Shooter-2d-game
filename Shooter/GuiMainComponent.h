#pragma once
class GuiMainComponent
{
	
public:
	int connected_to_form;
	int posX, posY;
	
	void recv_event(int ev);
	int last_event;

	GuiMainComponent();
	~GuiMainComponent();
};

