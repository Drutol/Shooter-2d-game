#include "link.h"
#include "Multiplayer_Client.h"
ALLEGRO_DISPLAY *display;




int main()
{
	
	//main_menu menu;
	//
	//ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
	//
	//ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();	
	//al_register_event_source(event_queue, al_get_timer_event_source(timer));
	////al_start_timer(timer);
	//

	//
	//while(!menu.isDone)
	//	{
	//		ALLEGRO_EVENT events; 
	//		al_wait_for_event_timed(event_queue, &events,0.006);
	//			menu.get_mouse_input();
	//			menu.redraw_text=true;
	//			menu.can_change_font=true;
	//		al_flip_display();
	//		al_clear_to_color(al_map_rgb(0,0,0));
	//	}


	cameraX = cameraY = 0;
	forms_manager.init_startup_form();






	return 0;
}