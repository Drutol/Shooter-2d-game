#include "ComponentTextBox.h"
#include "link.h"


ComponentTextBox::ComponentTextBox(int x, int y, string text)
{
	posX = x;
	posY = y;
	string_to_display = text;
	this->text_font = al_load_font("Resources/leadcoat.ttf", 10, NULL);
}
ComponentTextBox::ComponentTextBox()
{
	
}

void ComponentTextBox::draw_text()
{
	al_draw_text(text_font, al_map_rgb(100, 100, 0), posX, posY, ALLEGRO_ALIGN_CENTRE, string_to_display.c_str());
}



ComponentTextBox::~ComponentTextBox()
{
}
