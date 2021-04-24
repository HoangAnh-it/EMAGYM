#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<vector>
#include <fstream>
#include<sstream>
#include"Tile.hpp"
#include"Monster.hpp"
#include"LTexture.hpp"
#include"Player.hpp"
#include"LTime.hpp"
#include"Menu.hpp"



const int MAP_WIDTH = 6500;
const int MAP_HEIGHT = 2800;

extern  int SCREEN_WIDTH ;
extern  int SCREEN_HEIGHT ;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern TTF_Font* temp_font;
extern TTF_Font* font_count_down;

extern bool pause;
extern bool is_start_count_down;
const int MAX_TIME_COUNT_DOWN = 120; // 120 giay
extern int run_;  // chay background cloud

extern bool play_music_intro;
extern bool play_music_background_forest;
extern bool play_music_background_wind;
extern bool play_music_background_dragon;
extern bool play_music_1;
extern bool play_music_2;
extern bool play_music_3;
extern bool play_music_4;

// cac ham 
void setSizeWindow();
bool Init();

bool loadMedia(Tile* tile[TOTAL_TILE_HEIGHT][TOTAL_TILE_WIDTH]);
bool setTiles(Tile* tile[TOTAL_TILE_HEIGHT][TOTAL_TILE_WIDTH]);
bool checkMouseMotion(int& x, int& y,  SDL_Rect a);
bool checkCollision(SDL_Rect a, SDL_Rect b);
void addMonster(float posX, float posY, int frameFirst, int total_frame, int type_Monster);
void total_AddMonster();
void resetValue();
void count_down(SDL_Rect& camera);
void setMusic();
void pauseOrUnpauseMusic();

void render_main(SDL_Rect& camera);
void render_map(SDL_Rect& camera);
void render_player_and_monsters(SDL_Rect& camera);

void close();

// chi so image player trong mang
enum IMAGE_BODY_PARTS
{
	EYES,
	HEAD_AND_BODY,
	LEFT_LEG,
	RIGHT_LEG,
	TOTAL_BODY_PARTS
};
// chi so image monster trong mang
enum IMAGE_MONSTER
{
	IMAGE_TWO_BATH,
	IMAGE_SLIME_1,
	IMAGE_SLIME_2,
	IMAGE_DINOSAURS,
	IMAGE_ZOMBIE,
	IMAGE_DRAGON_BOSS,
	TOTAL_IMAGE__MONSTER
};

// chi so image_tile trong mang
enum IMAGE_TYPE_TILE
{
	LAND,
	TOP_TUBE,
	BOTTOM_TUBE,
	ROCK,
	ROCK_2,
	BOX,
	COIN,
	FLAG,
	WATER,
	HEART,
	TOTAL_TYPE_TILE
};

// chi so background trong mang
enum BACKGROUND
{
	BG_1,
	BG_NIGHT,
	BG_SUN_SET,
	BG_CLOUDS2,
	HOURSE_TREE,
	TREE_1,
	TREE_3,
	BG_RIP,
	BG_2,
	BG_3,
	BLACK_RECT,
	BOAT,
	TOTAL_BACKGROUND
};


// chi so trong SDL_Rect cut_LAND
enum CUT_IMAGE_LAND
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
	LEFT_,
	CENTER_,
	RIGHT_,
	TOP_,
	TREE,
	TOTAL_CUT_IMAGE_LAND
};

// chi so  trong SDL_Rect  cut_MONSTER
enum CUT_IMAGE_MONSTER
{
	BLACK_BATH_1,
	BLACK_BATH_2,
	BLACK_BATH_3,
	BLACK_BATH_4,
	YELLOW_BATH_1,
	YELLOW_BATH_2,
	YELLOW_BATH_3,
	YELLOW_BATH_4,
	SLIME_1_1,
	SLIME_1_2,
	SLIME_1_3,
	SLIME_2_1,
	SLIME_2_2,
	SLIME_2_3,
	SLIME_2_4,
	DINOSAURS_1,
	DINOSAURS_2,
	DINOSAURS_3,
	DINOSAURS_4,
	DINOSAURS_5,
	DINOSAURS_6,
	ZOMBIE_1,  // zombie rise
	ZOMBIE_2,
	ZOMBIE_3,
	ZOMBIE_4,
	ZOMBIE_5,
	ZOMBIE_6,
	ZOMBIE_7,
	ZOMBIE_8,  // zombie walk
	ZOMBIE_9,
	ZOMBIE_10,
	ZOMBIE_11,
	ZOMBIE_12,
	ZOMBIE_13,
	ZOMBIE_14,
	ZOMBIE_15,
	ZOMBIE_16,
	DRAGON_BOSS_1,
	DRAGON_BOSS_2,
	DRAGON_BOSS_3,
	DRAGON_BOSS_4,
	TOTAL_CUT_IMAGE_MONSTER
};

//chi so trong map
enum NUMBER_TILE_MAP
{
	TILE_BLACK = -9,
	TILE_HEART = -6, 
	TILE_WATER = -5,
	TILE_STATIC_WATER = -4, 
	TILE_FLAG = -2,
	TILE_COIN = -1,
	// image/Tile.png
	TILE_TOP_LEFT = 1,
	TILE_TOP_CENTER = 2,
	TILE_TOP_RIGHT = 3,
	TILE_MIDDLE_LEFT = 16,  
	TILE_MIDDLE_CENTER = 4, 
	TILE_MIDDLE_RIGHT = 17,  
	TILE_BOTTOM_LEFT = 5,    
	TILE_BOTTOM_CENTER = 6,    
	TILE_BOTTOM_RIGHT = 7,    

	TILE_TOP_ = 18,       
	
	TILE_LEFT_ = 12,    
	TILE_CENTER_ = 13,   
	TILE_RIGHT_ = 14,   
	
	TILE_TREE = 8,   
	// image/rock.png
	TILE_ROCK = 9,   
	// image/rock2.png
	TILE_ROCK_2 = 99,  
	// image/head_tube.png
	TILE_TOP_TUBE = 10,  
	// image/body_tube.png
	TILE_BOTTOM_TUBE = 11,  
	// image/box.png
	TILE_BOX = 15,   
};

enum MENU
{
	BG_CLOUDS,
	BG_,
	PLAY_GAME,
	TUTORIAL,
	QUIT,
	SELECTED_TUTORIAL,
	BG_GAME_OVER,
	BACK,
	YES,
	NO,
	OPTION,
	OPTION_EXIT,
	OPTION_RESTART,
	OPTION_PAUSE,
	OPTION_TUTORIAL,
	SURVIVAL,
	OK,
	WIN,
	TOTAL_ITEM_MENU
};

enum SOUND_EFFECTS
{
	MUSIC_JUMP,
	MUSIC_GAIN_COIN,
	MUSIC_GAIN_HEART,
	MUSIC_MOUSE_MOTION,
	MUSIC_MOUSE_SELECTED,
	MUSIC_WATER,
	MUSIC_LOSE_LIFE,
	MUSIC_WING_FLAP,
	MUSIC_FOOTSTEP,
	MUSIC_FOOTSTEP2,
	MUSIC_FOOTSTEP3,
	MUSIC_FOOTSTEP4,
	TOTAL_SOUND_EFFECTS
};

extern int total_coin;

// anh nhan vat
extern LTexture image_player[TOTAL_BODY_PARTS];
// cac anh va text khac
extern LTexture image_tile[TOTAL_TYPE_TILE];
extern LTexture image_background[TOTAL_BACKGROUND];
extern LTexture image_monster[TOTAL_IMAGE__MONSTER];
extern LTexture image_menu[TOTAL_ITEM_MENU];

extern LTexture theNumberOfHeart;    // menu - heart
extern LTexture countDown;            // dem nguoc

// class
extern Player person;
extern Tile* tile[TOTAL_TILE_HEIGHT][TOTAL_TILE_WIDTH];
extern std::vector<Monster*> ls_Monster;
extern LTime timer;
extern LTime timer_count_down;
extern Menu menu;

// cut anh
extern SDL_Rect *cut_image_LAND[TOTAL_CUT_IMAGE_LAND];
extern SDL_Rect *cut_image_MONSTER[TOTAL_CUT_IMAGE_MONSTER];
extern SDL_Rect *cut_image_coin[9];
extern SDL_Rect *cut_image_flag[6];
extern SDL_Rect *cut_image_water[9];
extern SDL_Rect *cut_image_heart[12];

// Music
extern Mix_Music* music_intro;
extern Mix_Music* music_background_forest;
extern Mix_Music* music_background_wind;
extern Mix_Music* music_background_dragon;
extern Mix_Chunk* sound_effects[TOTAL_SOUND_EFFECTS];