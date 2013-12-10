#include "Player.h"
#include "Doors.h"
#include "Lever.h"
struct tile
{
	int x;
	int y;
	bool passable;
	int held_object;
	int held_object_ID;
	std::string bitmap;
};
 enum tile_objects {NOTHING,DOOR,LEVER};
int keyboard_input();
int camera_update(int pressed_key,float previous_camera_position,int camera);
int get_random_number(int min , int max);
int get_mouse_state(char task);
void init_bitmaps(int for_lvl);
void kill_player();
int count_doors();
int count_levers();
void check_interactions(int tile_X,int tile_Y,int with_key);
void draw_objects();
int search_for_object_ID(int tile_X,int tile_Y,int type);
ALLEGRO_BITMAP* return_appropriate_bitmap(std::string which);

///Incredibely importatnt arrays and vars
extern ALLEGRO_TRANSFORM camera;
extern tile map[20][20];
extern Player player;
extern Doors *doors;
extern Lever *levers;

