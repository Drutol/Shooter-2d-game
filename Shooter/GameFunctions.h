#include "Player.h"
#include "Doors.h"
#include "Lever.h"
#include "Interaction_Indicator.h"
#include "Affection_box.h"
#include "NPC.h"
struct tile
{
	int x;
	int y;
	bool passable;
	int held_object;
	int held_object_ID;
	std::string bitmap;
};
struct coords
{
	int x;
	int y;
};
 enum tile_objects {NOTHING,DOOR,LEVER,BOX};
 enum directions {RIGHT,LEFT,UP,DOWN};
 enum states {OPEN,CLOSED,OPENING,CLOSING};
 enum flags {FLAG_PASSABLE,FLAG_UNPASSABLE,FLAG_DAMAGING,FLAG_PLAYER};
 enum bitmaps {DIRT,DIRT_BACK,DIRT_BACK_DOWN,DIRT_BACK_UP};
int keyboard_input();
bool keyboard_input_specific(int which_key);
int camera_update(int pressed_key,float previous_camera_position,int camera);
int get_random_number(int min , int max);
int get_mouse_state(char task);
void init_bitmaps(int for_lvl);
void kill_player();
int count_doors();
int count_levers();
int count_boxes();
void load_level(std::string level_path="level1");
void save_map();
void kill_player();
void map_draw_back();
void map_draw_front();
void use_transform(float cameraX,float cameraY);
bool check_door_collision();
void check_interactions(int tile_X,int tile_Y,int with_key);
void draw_objects();
void check_affection_box_collision_NPC(int radius,NPC &npc);
void check_affection_box_collision_player(int radius);
int search_for_object_ID(int tile_X,int tile_Y,int type);
ALLEGRO_BITMAP* return_appropriate_bitmap(std::string which);

///Incredibely importatnt arrays and vars
extern ALLEGRO_TRANSFORM camera;
extern tile map[20][20];
extern Player player;
extern Doors *doors;
extern Lever *levers;
extern Interaction_Indicator indicator;
extern NPC test_NPC;
///Not so important but still
extern ALLEGRO_FONT *game_font;
extern float cameraX;
extern float cameraY;
extern Affection_box *affection_boxes;
extern NPC dummy;