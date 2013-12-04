#include "link.h"
#include "main_menu.h"
void init()
{
	al_init_primitives_addon();
	srand(time(NULL));


	
	
	
	//ALLEGRO_DISPLAY *display = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
   }
   ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
   }
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
}
int main()
{
	init();
	
	main_menu menu;
	
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
	
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();	
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//al_start_timer(timer);
	while(!menu.isDone)
		{
			ALLEGRO_EVENT events; 
			al_wait_for_event_timed(event_queue, &events,0.001);
				menu.get_mouse_input();
				menu.redraw_text=true;
				menu.can_change_font=true;
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}





	return 0;
}