#define ScreenWidth 900
#define ScreenHeight 700
#define TileSize 64




//All allegro libs

#include <allegro5\allegro5.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>

//Other libs
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>

//Functions
void main_game();
bool is_tile_passable(int whichX,int whichY);
void overwrite_tile(int x,int y,bool is_passable,std::string bitmap,int held_object);
float return_player_Y();
float return_player_X();

//Vars
