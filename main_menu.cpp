#include "main_menu.h"


main_menu::main_menu(void)
{
			
	
	al_install_mouse();
	menu_event_queue = al_create_event_queue();
	al_register_event_source(menu_event_queue,al_get_mouse_event_source());
	this->isDone=false;
	this->mouse_x = 0;
	this->mouse_y = 0;
	this->FontSize1 = 0;
	this->FontSize2 = 0;
	this->Xtext1 = 450;
	this->Ytext1 = 300;
	this->Xtext2 = 450;
	this->Ytext2 = 380;
	this->default_size = 40;
	this->size_to_reach = 19;
	this->redraw_text = true;
	this->change_font=true;
	this->init_addons=true;
}


main_menu::~main_menu(void)
{
}

void main_menu::draw_menu()
{
}

void main_menu::get_mouse_input()
{
	al_get_next_event(menu_event_queue , &menu_event);
	if(menu_event.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		main_menu::set_mouse_position();
	}
	if(isHoweringText1&&menu_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		al_draw_text(menu_font_1[19],al_map_rgb(180,123,90),350,350,ALLEGRO_ALIGN_CENTRE,"Loading...");
		al_flip_display();
		main_game();
	}
	if(isHoweringText2&&menu_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		isDone=true;
	else if(increasing_in_progress1||increasing_in_progress1||decreasing_in_progress1||decreasing_in_progress2||decreasing_in_progress_all)
		main_menu::set_mouse_position();
}

void main_menu::set_mouse_position()
{
	mouse_x = menu_event.mouse.x;
	mouse_y = menu_event.mouse.y;
	check_possible_interactions();
}

void main_menu::check_possible_interactions()
{
	if(mouse_x > 450 && mouse_x < 500 && mouse_y > 300 && mouse_y < 350)
			{
				draw_text(1);
				isHoweringText1=true;
				isHoweringText2=false;
				start_decreasing_font_size(2);
			}
	else if(mouse_x > 450 && mouse_x < 500 && mouse_y > 350 && mouse_y < 450)
			{
				draw_text(2);
				isHoweringText1=false;
				isHoweringText2=true;
				start_decreasing_font_size(1);
			}	
	else 
			{
				isHoweringText1=false;
				isHoweringText2=false;
				draw_text(0);
				start_decreasing_font_size(NULL);
			}
}
void main_menu::draw_text(int text_to_highlight)
{
					
	if(init_addons)
	{
		al_init_font_addon(); 
		al_init_ttf_addon();
		init_addons=false;
	}
	
	if(change_font)
		{
			for(int i = 0;i<20;i++)
			{	
				menu_font_1[i] = al_load_font("Resources/leadcoat.ttf",default_size+i,NULL);
			}

			change_font=false;
		}
		
		if(redraw_text)
		{
			if(text_to_highlight==1)
				al_draw_text(menu_font_1[FontSize1],al_map_rgb(150,100,33),Xtext1,Ytext1,ALLEGRO_ALIGN_CENTRE,"Play!");
			else
				al_draw_text(menu_font_1[FontSize1],al_map_rgb(100,100,33),Xtext1,Ytext1,ALLEGRO_ALIGN_CENTRE,"Play!");
			if(text_to_highlight==2)
				al_draw_text(menu_font_1[FontSize2],al_map_rgb(150,100,33),Xtext2,Ytext2,ALLEGRO_ALIGN_CENTRE,"Exit");
			else
				al_draw_text(menu_font_1[FontSize2],al_map_rgb(100,100,33),Xtext2,Ytext2,ALLEGRO_ALIGN_CENTRE,"Exit");
			redraw_text=false;
		}
			if(text_to_highlight!=0)
				start_increasing_font_size(text_to_highlight);
			
		

}

void main_menu::start_increasing_font_size(int font_number)
{
	increasing_in_progress1=true;
	if(font_number==1)
	{
		increasing_in_progress1=true;
		if(FontSize1<size_to_reach)
		FontSize1++;
		if(FontSize1==size_to_reach)
		increasing_in_progress1=false;
	}
	if(font_number==2)
	{
		increasing_in_progress2=true;
		if(FontSize2<size_to_reach)
		FontSize2++;
		if(FontSize2==size_to_reach)
		increasing_in_progress2=false;

	}
}
void main_menu::start_decreasing_font_size(int font_number)
{
	if(font_number==1)
	{
		decreasing_in_progress1=true;
		if(FontSize1!=0)
		FontSize1--;
		if(FontSize1==0)
		decreasing_in_progress1=false;
		

	}
	if(font_number==2)
	{
		decreasing_in_progress2=true;
		if(FontSize2!=0)
		FontSize2--;
		if(FontSize2==0)
		decreasing_in_progress2=false;
	}
	
	if(!isHoweringText1&&!isHoweringText2)
	{
		decreasing_in_progress_all=true;
		if(FontSize1!=0)
			FontSize1--;
		if(FontSize2!=0)
			FontSize2--;
		if(FontSize1==0&&FontSize2==0)
		decreasing_in_progress_all=false;
		//change_font=true;
	}
}