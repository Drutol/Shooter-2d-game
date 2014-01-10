#include "link.h"
#pragma once
class main_menu
{
private:
	bool increasing_in_progress1;
	bool increasing_in_progress2;
	bool decreasing_in_progress1;
	bool decreasing_in_progress2;
	bool increasing_in_progress3;
	bool decreasing_in_progress3;
	bool decreasing_in_progress_all;
	bool isHoweringText1;
	bool isHoweringText2;
	bool isHoweringText3;
	bool change_font;
	bool init_addons;
	void font_size_increasing(int font_to_increase);
	int default_size;
	int Xtext1;
	int Ytext1;
	int Xtext2;
	int Ytext2;
	int Xtext3;
	int Ytext3;
	int size_to_reach;

public:
	//Other vars
	int mouse_x;
	int mouse_y;
	bool isDone;
	int selection;
	bool redraw_text;
	bool can_change_font;
	//Text size variables
	int FontSize1;
	int FontSize2;
	int FontSize3;
	//Allegro vars
	ALLEGRO_EVENT_QUEUE *menu_event_queue;
	ALLEGRO_EVENT menu_event;
	ALLEGRO_FONT *menu_font_1[19];
	//Methods
	main_menu(void);
	~main_menu(void);
	void get_mouse_input();
	void draw_menu();
	void set_mouse_position();
	void check_possible_interactions();
	void draw_text(int text_to_highlight);
	void start_increasing_font_size(int font_number);
	void start_decreasing_font_size(int font_number);
};

