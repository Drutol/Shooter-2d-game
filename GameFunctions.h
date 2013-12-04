 struct tile
{
	int x;
	int y;
	bool passable;
	std::string bitmap;
};
 
int keyboard_input();
int camera_update(int pressed_key,float previous_camera_position,int camera);
int get_random_number(int min , int max);
int get_mouse_state(char task);
void init_bitmaps(int for_lvl);
ALLEGRO_BITMAP* return_appropriate_bitmap(std::string which);


