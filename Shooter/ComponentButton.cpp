#include "ComponentButton.h"


ComponentButton::ComponentButton(void(*function_to_be_called)(int), int PosX, int PosY, int of_form_ID, string Text, ALLEGRO_COLOR rgb,int arg)
{
	connected_event_int = function_to_be_called;
	this->posX = PosX;
	this->posY = PosY;
	this->connected_to_form = of_form_ID;
	this->text = Text;
	this->text_color = rgb;
	this->text_font = al_load_font("Resources/leadcoat.ttf", 20, NULL);
	int_function = true;
}
ComponentButton::ComponentButton(void(*function_to_be_called)(void), int PosX, int PosY, int of_form_ID, string Text, ALLEGRO_COLOR rgb)
{
	connected_event_void = function_to_be_called;
	this->posX = PosX;
	this->posY = PosY;
	this->connected_to_form = of_form_ID;
	this->text = Text;
	this->text_color = rgb;
	this->text_font = al_load_font("Resources/leadcoat.ttf", 20, NULL);
	int_function = false;
}
ComponentButton::ComponentButton()
{

}




ComponentButton::~ComponentButton()
{
}

void ComponentButton::Render()
{
	al_draw_filled_rectangle(posX, posY, posX + 150, posY + 50, al_map_rgb(0, 0, 0));
	al_draw_text(text_font, text_color, posX + 40, posY + 20, ALLEGRO_ALIGN_CENTRE, text.c_str());
}
