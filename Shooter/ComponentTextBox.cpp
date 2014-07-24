#include "ComponentTextBox.h"
#include "link.h"
#include "GameFunctions.h"


ComponentTextBox::ComponentTextBox(int x, int y, string text)
{
	posX = x;
	posY = y;
	string_to_display = text;
}
ComponentTextBox::ComponentTextBox()
{
	
}

void ComponentTextBox::draw_text()
{
	al_draw_text(game_font, al_map_rgb(100, 100, 0), posX, posY, NULL, string_to_display.c_str());
}



ComponentTextBox::~ComponentTextBox()
{
}
