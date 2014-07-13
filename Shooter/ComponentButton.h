#pragma once
#include "link.h"
#include "GameFunctions.h"
#include "GuiMainComponent.h"
class ComponentButton : public GuiMainComponent
{
public:
	
	void (*connected_event_void)(void);
	void (*connected_event_int)(int);

	bool int_function;
	int arg;

	void Render();
	string text;
	ALLEGRO_COLOR text_color;
	ALLEGRO_COLOR text_color_base;
	ALLEGRO_FONT *text_font;
	ComponentButton();
	ComponentButton::ComponentButton(void(*function_to_be_called)(void), int PosX, int PosY, int of_form_ID, string Text, ALLEGRO_COLOR rgb);
	ComponentButton::ComponentButton(void(*function_to_be_called)(int), int PosX, int PosY, int of_form_ID, string Text, ALLEGRO_COLOR rgb, int arg);
	void check_for_events();  //any mails yet?
	void call_function();
	bool mouse_hovering;
	~ComponentButton();
};

