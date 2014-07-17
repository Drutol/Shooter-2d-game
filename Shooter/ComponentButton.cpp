#include "ComponentButton.h"


ComponentButton::ComponentButton(void(*function_to_be_called)(int), int PosX, int PosY, int of_form_ID, string Text, ALLEGRO_COLOR rgb,int arg,int font_size)
{
	connected_event_int = function_to_be_called;

	this->connected_to_form = of_form_ID;
	this->text = Text;
	this->text_color = rgb;
	this->text_color_base = rgb;
	this->text_font = game_font;
	this->last_event = -1;
    this->arg = arg;
	int_function = true;
	this->mouse_hovering = false;
	text_font = al_load_ttf_font("Resources/leadcoat.ttf", font_size, NULL);
	width = al_get_text_width(text_font, Text.c_str());
	height = al_get_font_line_height(text_font);
	if (PosX == 450)
	{
		PosX -= width / 2;
	}
	this->posX = PosX;
	this->posY = PosY;
}
ComponentButton::ComponentButton(void(*function_to_be_called)(void), int PosX, int PosY, int of_form_ID, string Text, ALLEGRO_COLOR rgb,int font_size)
{
	connected_event_void = function_to_be_called;

	this->connected_to_form = of_form_ID;
	this->text = Text;
	this->text_color = al_map_rgb(255,255,255);
	this->text_color_base = rgb;
	this->last_event = -1;
	int_function = false;
	this->mouse_hovering = false;
	cout << font_size << endl;
	text_font = al_load_ttf_font("Resources/leadcoat.ttf", font_size, NULL);
	width = al_get_text_width(text_font, Text.c_str());
	height = al_get_font_line_height(text_font);
	if (PosX == 450)//we want centre
	{
		PosX -= width /2;
	}
	this->posX = PosX;
	this->posY = PosY;
}
ComponentButton::ComponentButton()
{

}





ComponentButton::~ComponentButton()
{
}

void ComponentButton::Render()
{
		if (mouse_hovering)
		{
			text_color = al_map_rgb(255, 100, 100);
		}
		else
		{
			text_color = text_color_base;
		}
	al_draw_filled_rectangle(posX, posY, posX + width, posY + height, al_map_rgb(0, 0, 0));
	al_draw_text(text_font,text_color , posX + 40, posY + 20, ALLEGRO_ALIGN_CENTRE, text.c_str());
	check_for_events();
}

void ComponentButton::call_function()
{
	if (int_function)
	{
		connected_event_int(arg);
	}
	else
	{
		connected_event_void();
	}
}

void ComponentButton::check_for_events()
{
	if (last_event != -1)
	{
		if (last_event == GUI_KEY_PRESS)
		{
			last_event = -1;
			call_function();
			
		}

	}

}