#include"Function.hpp"

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
TTF_Font* temp_font = NULL;
TTF_Font* font_count_down = NULL;

bool pause = false;
bool is_start_count_down = false;
int total_coin = 0;
int run_ = 0;

bool play_music_intro = false;
bool play_music_background_forest = false;
bool play_music_background_wind = false;
bool play_music_background_dragon = false;
bool play_music_1 = false;
bool play_music_2 = false;
bool play_music_3 = false;
bool play_music_4 = false;

// anh nhan vat
LTexture image_player[TOTAL_BODY_PARTS];
// anh khac
LTexture image_tile[TOTAL_TYPE_TILE];
LTexture image_background[TOTAL_BACKGROUND];
LTexture image_monster[TOTAL_IMAGE__MONSTER];
LTexture image_menu[TOTAL_ITEM_MENU];

LTexture theNumberOfHeart;
LTexture countDown;

// cut anh 
SDL_Rect *cut_image_LAND[TOTAL_CUT_IMAGE_LAND];
SDL_Rect *cut_image_MONSTER[TOTAL_CUT_IMAGE_MONSTER];
SDL_Rect* cut_image_coin[9];
SDL_Rect* cut_image_flag[6];
SDL_Rect* cut_image_water[9];
SDL_Rect* cut_image_heart[12];

// class 
Player person(MAP_WIDTH-100, 200);
Tile* tile[TOTAL_TILE_HEIGHT][TOTAL_TILE_WIDTH];
std::vector<Monster*> ls_Monster;
LTime timer;
LTime timer_count_down;
Menu menu;

// Music
Mix_Music* music_intro;
Mix_Music* music_background_forest;
Mix_Music* music_background_wind;
Mix_Music* music_background_dragon;
Mix_Chunk* sound_effects[TOTAL_SOUND_EFFECTS];

// cac ham
void setSizeWindow()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	SCREEN_WIDTH = DM.w;
	SCREEN_HEIGHT = DM.h;
}

bool Init()
{
	bool kt = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Error: SDL_Init" << SDL_GetError() << std::endl;
		kt = false;
	}
	else
	{
		setSizeWindow();
		window = SDL_CreateWindow("EMAGYM_VHA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			kt = false;
		}
		else
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				std::cout << "Error: Loc tuyen tinh " << SDL_GetError() << std::endl;
			else
			{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (renderer == NULL)
				{
					std::cout << "Error: renderer" << SDL_GetError() << std::endl;
					kt = false;
				}
				else
				{
					int img = IMG_INIT_PNG;
					if (!(IMG_Init(img) & img))
					{
						std::cout << "Error: IMG" << IMG_GetError() << std::endl;
						kt = false;
					}
					else
					{
						if (TTF_Init() == -1)
						{
							std::cout << "Error: init TTF. " << TTF_GetError() << std::endl;
							kt = false;
						}
						else
						{
							if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
							{
								std::cout << "Error: init SDL_Mixer" << Mix_GetError() << std::endl;
								kt = false;
							}
						}
					}
				}
			}
		}
	}
	return kt;
}

bool loadMedia(Tile* tile[TOTAL_TILE_HEIGHT][TOTAL_TILE_WIDTH])
{
	// ANH NHAN VAT
	if (!image_player[EYES].loadTextureFromFile("image/eyes.png",1,1,1))
	{
		std::cout << "Error: load eyes" << std::endl;
		return false;
	}

	if (!image_player[HEAD_AND_BODY].loadTextureFromFile("image/headAndBody.png",1,1,1))
	{
		std::cout << "Error: load head" << std::endl;
		return false;
	}
	if (!image_player[LEFT_LEG].loadTextureFromFile("image/left_leg_2.png",1,1,1))
	{
		std::cout << "Error: load left leg" << std::endl;
		return false;
	}
	if (!image_player[RIGHT_LEG].loadTextureFromFile("image/right_leg_2.png",1,1,1))
	{
		std::cout << "Error: load right leg" << std::endl;
		return false;
	}

	// ANH MONSTER
	for (int i = 0; i < TOTAL_CUT_IMAGE_MONSTER; i++)
	{
		cut_image_MONSTER[i] = new SDL_Rect;
	}
		// load cac anh monster
	if (!image_monster[IMAGE_TWO_BATH].loadTextureFromFile("image/bath.png", 1, 1, 1))
	{
		std::cout << "Error: load two bath" << std::endl;
		return false;
	}
	else
	{
		*cut_image_MONSTER[BLACK_BATH_1] = { 10,23,99,37 };
		*cut_image_MONSTER[BLACK_BATH_2] = { 128,24,80,37 };
		*cut_image_MONSTER[BLACK_BATH_3] = { 245,8,61,53 };
		*cut_image_MONSTER[BLACK_BATH_4] = { 361,24,80,38 };
		*cut_image_MONSTER[YELLOW_BATH_1] = { 10,95, 109,47 };
		*cut_image_MONSTER[YELLOW_BATH_2] = { 128,95,80,47 };
		*cut_image_MONSTER[YELLOW_BATH_3] = { 245,95,66,47 };
		*cut_image_MONSTER[YELLOW_BATH_4] = { 362,95,80,47 };
	}
	if (!image_monster[IMAGE_SLIME_1].loadTextureFromFile("image/slime_1.png", 1, 1, 1))
	{
		std::cout << "Error: load slime_1" << std::endl;
		return false;
	}
	else
	{
		*cut_image_MONSTER[SLIME_1_1] = { 33,13,100,91 };
		*cut_image_MONSTER[SLIME_1_2] = { 156,13,124,91 };
		*cut_image_MONSTER[SLIME_1_3] = { 284,13,129,91 };
	}
	if (!image_monster[IMAGE_SLIME_2].loadTextureFromFile("image/slime_2.png", 1, 1, 1))
	{
		std::cout << "Error: load slime_2" << std::endl;
		return false;
	}
	else
	{
		*cut_image_MONSTER[SLIME_2_1] = { 23,41,88,67 };
		*cut_image_MONSTER[SLIME_2_2] = { 148,32,92,76 };
		*cut_image_MONSTER[SLIME_2_3] = { 280,29,86,79 };
		*cut_image_MONSTER[SLIME_2_4] = { 407,33,90,75 };
	}
	if (!image_monster[IMAGE_DINOSAURS].loadTextureFromFile("image/dinosaur.png", 1, 1, 1))
	{
		std::cout << "Error: load dinosaur" << std::endl;
		return false;
	}
	else
	{
		*cut_image_MONSTER[DINOSAURS_1] = { 690,22,85,95 };
		*cut_image_MONSTER[DINOSAURS_2] = { 557,22,85,95 };
		*cut_image_MONSTER[DINOSAURS_3] = { 423,22,85,95 };
		*cut_image_MONSTER[DINOSAURS_4] = { 289,22,85,95 };
		*cut_image_MONSTER[DINOSAURS_5] = { 155,22,85,95 };
		*cut_image_MONSTER[DINOSAURS_6] = { 21,22,85,95 };
	}
	if (!image_monster[IMAGE_ZOMBIE].loadTextureFromFile("image/zombie.png", 1, 1, 1))
	{
		std::cout << "Error: load image Zombie" << std::endl;
		return false;
	}
	else
	{
		*cut_image_MONSTER[ZOMBIE_1] = { 27,97,49,61 };
		*cut_image_MONSTER[ZOMBIE_2] = { 166,97,47,61 };
		*cut_image_MONSTER[ZOMBIE_3] = { 235,97,52,61 };
		*cut_image_MONSTER[ZOMBIE_4] = { 305,97,53,61 };
		*cut_image_MONSTER[ZOMBIE_5] = { 373,97,54,61 };
		*cut_image_MONSTER[ZOMBIE_6] = { 441,97,54,61 };
		*cut_image_MONSTER[ZOMBIE_7] = { 507,97,60,61 };
		*cut_image_MONSTER[ZOMBIE_8] = { 29,17,50,61 };
		*cut_image_MONSTER[ZOMBIE_9] = { 97,17,47,61 };
		*cut_image_MONSTER[ZOMBIE_10] = { 166,17,44,61 };
		*cut_image_MONSTER[ZOMBIE_11] = { 235,17,46,61 };
		*cut_image_MONSTER[ZOMBIE_12] = { 305,17,52,61 };
		*cut_image_MONSTER[ZOMBIE_13] = { 374,17,50,61 };
		*cut_image_MONSTER[ZOMBIE_14] = { 444,17,45,61 };
		*cut_image_MONSTER[ZOMBIE_15] = { 511,17,46,61 };
		*cut_image_MONSTER[ZOMBIE_16] = { 580,17,48,61 };
	}
	if (!image_monster[IMAGE_DRAGON_BOSS].loadTextureFromFile("image/dragon.png", 1, 1, 1))
	{
		std::cout << "Error: load image dragon" << std::endl;
		return false;
	}
	else
	{
		*cut_image_MONSTER[DRAGON_BOSS_1] = {33,533,148,76  };
		*cut_image_MONSTER[DRAGON_BOSS_2] = { 221,525,154,84 };
		*cut_image_MONSTER[DRAGON_BOSS_3] = { 412,486,153,123 };
		*cut_image_MONSTER[DRAGON_BOSS_4] = { 221,525,154,84 };
	}

	// ANH TILE
	if (!image_tile[TOP_TUBE].loadTextureFromFile("image/body_tube.png",1,1,1))
	{
		std::cout << "Error: load BODY_TUBE" << std::endl;
		return false;
	}
	if (!image_tile[BOTTOM_TUBE].loadTextureFromFile("image/head_tube.png",1,1,1))
	{
		std::cout << "Error: load HEAD_TUBE" << std::endl;
		return false;
	}
	if (!image_tile[ROCK].loadTextureFromFile("image/rock.png", 1, 1, 1))
	{
		std::cout << "Error: load ROCK" << std::endl;
		return false;
	}
	if (!image_tile[ROCK_2].loadTextureFromFile("image/rock2.png", 1, 1, 1))
	{
		std::cout << "Error: load ROCK2" << std::endl;
		return false;
	}
	if (!image_tile[BOX].loadTextureFromFile("image/box.png", 1, 1, 1))
	{
		std::cout << "Error: load BOX" << std::endl;
		return false;
	}
	if (!image_tile[LAND].loadTextureFromFile("image/tile.png", 1, 1, 1))
	{
		std::cout << "Error: load LAND" << std::endl;
		return false;
	}
	else
	{
		for (int i = 0; i < TOTAL_CUT_IMAGE_LAND; i++)
		{
			cut_image_LAND[i] = new SDL_Rect;
		}
		*cut_image_LAND[TOP_LEFT] = { 0,1,30,30 };
		*cut_image_LAND[TOP_CENTER] = { 34,1,30,30 };
		*cut_image_LAND[TOP_RIGHT] = { 65,1,35,30 };
		*cut_image_LAND[MIDDLE_LEFT] = { 3,32,30,30 };
		*cut_image_LAND[MIDDLE_CENTER] = { 34,32,30,30 };
		*cut_image_LAND[MIDDLE_RIGHT] = { 65,32,34,30 };
		*cut_image_LAND[BOTTOM_LEFT] = { 1,64,30,30 };
		*cut_image_LAND[BOTTOM_CENTER] = { 34,64,30,30 };
		*cut_image_LAND[BOTTOM_RIGHT] = { 66,64,30,30 };
		*cut_image_LAND[LEFT_] = { 0,126,30,30 };
		*cut_image_LAND[CENTER_] = { 34,126,30,29 };
		*cut_image_LAND[RIGHT_] = { 66,126,35,30 };
		*cut_image_LAND[TREE] = { 226,1,16,30 };
		*cut_image_LAND[TOP_] = { 172,33,35,30 };
	}
	if (!image_tile[COIN].loadTextureFromFile("image/coin.png", 0, 0, 0))
	{
		std::cout << "Error Load coin" << std::endl;
		return false;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			cut_image_coin[i] = new SDL_Rect;
		}
		*cut_image_coin[0] = { 14,53,40,38 };
		*cut_image_coin[1] = { 59,53,35,38 };
		*cut_image_coin[2] = { 101,53,31,38 };
		*cut_image_coin[3] = { 134,53,31,38 };
		*cut_image_coin[4] = { 164,53,22,38 };
		*cut_image_coin[5] = { 189,53,23,38 };
		*cut_image_coin[6] = { 220,53,29,38 };
		*cut_image_coin[7] = { 257,53,34,38 };
		*cut_image_coin[8] = { 299,53,38,38 };
	}
	if (!image_tile[FLAG].loadTextureFromFile("image/flag.png", 1, 1, 1))
	{
		std::cout << "Error Load flag" << std::endl;
		return false;
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			cut_image_flag[i] = new SDL_Rect;
		}
		*cut_image_flag[0] = { 334,5,118,300 };
		*cut_image_flag[1] = { 497,5,118,300 };
		*cut_image_flag[2] = { 652,5,118,300 };
		*cut_image_flag[3] = { 815,5,118,300 };
		*cut_image_flag[4] = { 972,5,118,300 };
		*cut_image_flag[5] = { 1131,5,118,300 };
	}
	if (!image_tile[WATER].loadTextureFromFile("image/water.png", 1, 1, 1))
	{
		std::cout << "Error Load water" << std::endl;
		return false;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			cut_image_water[i] = new SDL_Rect;
		}
		*cut_image_water[0] = { 15,5,23,26 };
		*cut_image_water[1] = { 46,5,23,26 };
		*cut_image_water[2] = { 77,5,23,26 };
		*cut_image_water[3] = { 109,5,23,26 };
		*cut_image_water[4] = { 139,5,23,26 };
		*cut_image_water[5] = { 170,5,23,26 };
		*cut_image_water[6] = { 202,5,23,26 };
		*cut_image_water[7] = { 233,5,23,26 };
		*cut_image_water[8] = { 234,16,20,13 };
	}

	// ANH BACKGROUND
	if (!image_background[BG_1].loadTextureFromFile("image/bg_1.png",1,1,1))
	{
		std::cout << "Error: load backGround_1" << std::endl;
		return false;
	}
	if (!image_background[BG_NIGHT].loadTextureFromFile("image/BG_night.png", 1, 1, 1))
	{
		std::cout << "Error: load BG_night" << std::endl;
		return false;
	}
	if (!image_background[BG_SUN_SET].loadTextureFromFile("image/sun_set.png", 1, 1, 1))
	{
		std::cout << "Error: load Sun_set" << std::endl;
		return false;
	}
	if (!image_background[BG_CLOUDS2].loadTextureFromFile("image/BG_clouds.png", 1, 1, 1))
	{
		std::cout << "Error: load BG_CLOUDS2" << std::endl;
		return false;
	}
	if (!image_background[TREE_1].loadTextureFromFile("image/tree_1.png", 1, 1, 1))
	{
		std::cout << "Error: load TREE_1" << std::endl;
		return false;
	}
	if (!image_background[TREE_3].loadTextureFromFile("image/tree_3.png", 1, 1, 1))
	{
		std::cout << "Error: load TREE_3" << std::endl;
		return false;
	}
	if (!image_background[HOURSE_TREE].loadTextureFromFile("image/hourse_tree.png", 1, 1, 1))
	{
		std::cout << "Error: load HOURSE_TREE" << std::endl;
		return false;
	}

	if (!image_background[BG_RIP].loadTextureFromFile("image/rip.png", 1, 1, 1))
	{
		std::cout << "Error: load image rip" << std::endl;
		return false;
	}
	if (!image_background[BG_2].loadTextureFromFile("image/BG_2.png", 1, 1, 1))
	{
		std::cout << "Error: load image BG_boss_1" << std::endl;
		return false;
	}
	if (!image_background[BG_3].loadTextureFromFile("image/BG_3.png", 1, 1, 1))
	{
		std::cout << "Error: load image BG_boss_2" << std::endl;
		return false;
	}
	if (!image_tile[HEART].loadTextureFromFile("image/heart.png", 1, 1, 1))
	{
		std::cout << "Error: load image heart" << std::endl;
		return false;
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			cut_image_heart[i] = new SDL_Rect;
		}
		*cut_image_heart[0] = { 29,29,191,166 };
		*cut_image_heart[1] = { 279,29,191,166 };
		*cut_image_heart[2] = { 531,29, 191,166 };
		*cut_image_heart[3] = { 782,29,191,166 };
		*cut_image_heart[4] = { 29,263, 191,166 };
		*cut_image_heart[5] = { 279,263,191,166 };
		*cut_image_heart[6] = { 531,263,191,166 };
		*cut_image_heart[7] = { 782,263,191,166 };
		*cut_image_heart[8] = { 29,503, 191,166 };
		*cut_image_heart[9] = { 279,503, 191,166 };
		*cut_image_heart[10] = { 531,503,191,166 };
		*cut_image_heart[11] = { 782,503,191,166 };
	}
	if (!image_background[BOAT].loadTextureFromFile("image/boat.png", 1, 1, 1))
	{
		std::cout << "Error: load image boat" << std::endl;
		return false;
	}

	// MENU
	if (!image_menu[BG_].loadTextureFromFile("image/bgmenu.png", 1, 1, 1))
	{
		std::cout << "Error: load menu_bg" << std::endl;
		return false;
	}
	if (!image_menu[BG_CLOUDS].loadTextureFromFile("image/menu_clouds.png", 1, 1, 1))
	{
		std::cout << "Error: load menu_clouds" << std::endl;
		return false;
	}
	if (!image_menu[BG_GAME_OVER].loadTextureFromFile("image/gameover.png", 1, 1, 1))
	{
		std::cout << "Error: load bg game over" << std::endl;
		return false;
	}
	if (!image_menu[OPTION].loadTextureFromFile("image/option.png", 1, 1, 1))
	{
		std::cout << "Error: load option" << std::endl;
		return false;
	}
	if (!image_menu[SELECTED_TUTORIAL].loadTextureFromFile("image/tutorial.png", 1, 1, 1))
	{
		std::cout << "Error: load tutorial" << std::endl;
		return false;
	}
	if (!image_menu[SURVIVAL].loadTextureFromFile("image/survival.png", 1, 1, 1))
	{
		std::cout << "Error: load survival" << std::endl;
		return false;
	}
	if (!image_menu[WIN].loadTextureFromFile("image/win.png", 1, 1, 1))
	{
		std::cout << "Error: load congratulations" << std::endl;
		return false;
	}
			// font
	font = TTF_OpenFont("font/windsorb.ttf", 50);
	if (font == NULL)
	{
		std::cout << "Error: load font" <<TTF_GetError() << std::endl;
		return false;
	}
	temp_font = TTF_OpenFont("font/VHCENTBI.ttf", 30);
	if (temp_font == NULL) 
	{
		std::cout << "Error: load temp_font"<<TTF_GetError() << std::endl;
		return false;
	}
	font_count_down = TTF_OpenFont("font/VHVOGU.ttf", 250);
	if (font_count_down == NULL)
	{
		std::cout << "Error: load temp_font_2" << TTF_GetError() << std::endl;
		return false;
	}
	// SET MAP
	if (!setTiles(tile))
	{
		std::cout << "Error: set Map" << std::endl;
		return false;
	}

	// LOAD  MUSIC
	music_intro = Mix_LoadMUS("Music/intro.wav");
	if (music_intro == NULL)
	{
		std::cout << "Error: load music_intro" << std::endl;
		return false;
	}
	music_background_forest = Mix_LoadMUS("Music/music_background_forest.wav");
	if (music_background_forest == NULL)
	{
		std::cout << "Error: load music_background_forest" << Mix_GetError() << std::endl;
		return false;
	}
	music_background_wind = Mix_LoadMUS("Music/music_background_wind.wav");
	if (music_background_wind == NULL)
	{
		std::cout << "Error: load music_background_wind" << Mix_GetError() << std::endl;
		return false;
	}
	music_background_dragon = Mix_LoadMUS("Music/dragon.wav");
	if (music_background_dragon == NULL)
	{
		std::cout << "Error: load music_background_dragon" << Mix_GetError() << std::endl;
		return false;
	}

	sound_effects[MUSIC_JUMP] = Mix_LoadWAV("Music/jump.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_JUMP], 30);
	if (sound_effects[MUSIC_JUMP] == NULL)
	{
		std::cout << "Error: load MUSIC_JUMP"<<Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_GAIN_COIN] = Mix_LoadWAV("Music/gain_coin.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_GAIN_COIN], 30);
	if (sound_effects[MUSIC_GAIN_COIN] == NULL)
	{
		std::cout << "Error: load MUSIC_COIN" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_GAIN_HEART] = Mix_LoadWAV("Music/gain_heart.wav");
	if (sound_effects[MUSIC_GAIN_HEART] == NULL)
	{
		std::cout << "Error: load MUSIC_HEART" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_MOUSE_MOTION] = Mix_LoadWAV("Music/mousemotion.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_MOUSE_MOTION], 70);
	if (sound_effects[MUSIC_MOUSE_MOTION] == NULL)
	{
		std::cout << "Error: load MUSIC_MOUSE_MOTION" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_MOUSE_SELECTED] = Mix_LoadWAV("Music/selected.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_MOUSE_SELECTED],  30);
	if (sound_effects[MUSIC_MOUSE_SELECTED] == NULL)
	{
		std::cout << "Error: load MUSIC_MOUSE_SELECTED" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_WATER] = Mix_LoadWAV("Music/water.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_WATER], 35);
	if (sound_effects[MUSIC_WATER] == NULL)
	{
		std::cout << "Error: load MUSIC_WATER" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_LOSE_LIFE] = Mix_LoadWAV("Music/lose_life.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_LOSE_LIFE], 15);
	if (sound_effects[MUSIC_LOSE_LIFE] == NULL)
	{
		std::cout << "Error: load MUSIC_LOSE_LIFE" << Mix_GetError() << std::endl;
		return false;
	}

	sound_effects[MUSIC_FOOTSTEP] = Mix_LoadWAV("Music/footstep.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_FOOTSTEP], 25);
	if (sound_effects[MUSIC_FOOTSTEP] == NULL)
	{
		std::cout << "Error: load MUSIC_FOOTSTEP" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_FOOTSTEP2] = Mix_LoadWAV("Music/footstep2.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_FOOTSTEP2], 25);
	if (sound_effects[MUSIC_FOOTSTEP2] == NULL)
	{
		std::cout << "Error: load MUSIC_FOOTSTEP2" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_FOOTSTEP3] = Mix_LoadWAV("Music/footstep3.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_FOOTSTEP3], 40);
	if (sound_effects[MUSIC_FOOTSTEP3] == NULL)
	{
		std::cout << "Error: load MUSIC_FOOTSTEP3" << Mix_GetError() << std::endl;
		return false;
	}
	sound_effects[MUSIC_FOOTSTEP4] = Mix_LoadWAV("Music/footstep4.wav");
	Mix_VolumeChunk(sound_effects[MUSIC_FOOTSTEP4], 30);
	if (sound_effects[MUSIC_FOOTSTEP4] == NULL)
	{
		std::cout << "Error: load MUSIC_FOOTSTEP4" << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

bool setTiles(Tile* tile[TOTAL_TILE_HEIGHT][TOTAL_TILE_WIDTH])
{
	std::ifstream map;
	map.open("input.txt");
	if (map.fail())
	{
		std::cout << "Unable to open map" << std::endl;
		return false;
	}
	else
	{
		int x = 0;
		int y = 0;
		for (int i = 0; i < TOTAL_TILE_HEIGHT; i++)
		{
			for (int j = 0; j < TOTAL_TILE_WIDTH; j++)
			{
				int type ;
				map >> type;
				if (type >= TILE_BLACK)
				{
					tile[i][j] = new Tile(x, y, type);
					if (type == -1) total_coin++;
				}
				x += TILE_WIDTH;
				if (x >= MAP_WIDTH)
				{
					x = 0;
					y += TILE_HEIGHT;
				}
			}
		}
		return true;
	}
}

bool checkMouseMotion(int& x, int& y,  SDL_Rect a)
{
	if (x < a.x) return false;
	if (x > a.x + a.w) return false;
	if (y < a.y) return false;
	if (y > a.y + a.h) return false;
	return true;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	if (a.x + a.w <= b.x) return false;
	if (a.x >= b.x + b.w) return false;
	if (a.y + a.h <= b.y) return false;
	if (a.y >= b.y + b.h) return false;
	return true;
}

void setMusic()
{
	if (!menu.is_selected_play_game() || menu.is_game_over() || person.isWon())
	{
		if ((play_music_background_forest || play_music_background_wind || play_music_background_dragon) && Mix_PlayingMusic() == 1)
		{
			Mix_HaltMusic();
		}
		play_music_intro = true;
		play_music_background_forest = false;
		play_music_background_wind = false;
		play_music_background_dragon = false;
	}
	else
	{
		if (menu.is_selected_tutorial())
		{
			if ((play_music_background_forest || play_music_background_wind || play_music_background_dragon) && Mix_PlayingMusic() == 1)
			{
				Mix_HaltMusic();
			}
			play_music_intro = true;
			play_music_background_forest = false;
			play_music_background_wind = false;
			play_music_background_dragon = false;
		}
		else
		{
			if (play_music_intro && Mix_PlayingMusic() == 1)
			{
				Mix_HaltMusic();
				play_music_intro = false;
			}
			if (person.getX() > 0 && person.getX() <= 2950)
			{
				if ((play_music_background_wind || play_music_background_dragon) && Mix_PlayingMusic() == 1)
				{
					Mix_HaltMusic();
					play_music_background_wind = false;
					play_music_background_dragon = false;
				}
				play_music_background_forest = true;
			}
			else if (person.getX() > 2950 && person.getX() <= 4950)
			{
				if ((play_music_background_forest || play_music_background_dragon) && Mix_PlayingMusic() == 1)
				{
					Mix_HaltMusic();
					play_music_background_forest = false;
					play_music_background_dragon = false;
				}
				play_music_background_wind = true;
			}
			else if (person.getX() > 4950)
			{
				if (Mix_PlayingMusic() == 1 && (play_music_background_forest || play_music_background_wind || play_music_background_dragon && !person.is_started_surviving()))
				{
					Mix_HaltMusic();
					play_music_background_forest = false;
					play_music_background_wind = false;
				}
				if (person.is_started_surviving() && menu.is_selected_ok() && !person.isWon())
				{
					play_music_background_dragon = true;
				}
				else
				{
					play_music_background_dragon = false;
				}
			}
		}
	}
	// phat music
	if (play_music_intro && Mix_PlayingMusic() == 0)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME);
		Mix_PlayMusic(music_intro, -1);
	}
	else if (!play_music_intro)
	{
		if (play_music_background_forest && Mix_PlayingMusic() == 0)
		{
			Mix_VolumeMusic(30);
			Mix_PlayMusic(music_background_forest, -1);
		}
		else if (play_music_background_wind && Mix_PlayingMusic() == 0)
		{
			Mix_VolumeMusic(25);
			Mix_PlayMusic(music_background_wind, -1);
		}
		else if (play_music_background_dragon && Mix_PlayingMusic() == 0)
		{
			Mix_VolumeMusic(30);
			Mix_PlayMusic(music_background_dragon, -1);
		}
	}
}

void pauseOrUnpauseMusic()
{
	if (menu.is_selected_play_game())
	{
		if (play_music_background_forest || play_music_background_wind||play_music_background_dragon )
		{
			if (Mix_PlayingMusic() == 1)
			{
				if (Mix_PausedMusic() == 1)
				{
					Mix_ResumeMusic();
				}
				else
				{
					Mix_PauseMusic();
				}
			}
			else
			{
				if (play_music_background_forest)
				{
					Mix_VolumeMusic(30);
					Mix_PlayMusic(music_background_forest, -1);
				}
				else if (play_music_background_wind)
				{
					Mix_VolumeMusic(25);
					Mix_PlayMusic(music_background_wind, -1);
				}
				else if (play_music_background_dragon)
				{
					Mix_VolumeMusic(30);
					Mix_PlayMusic(music_background_dragon, -1);
				}
			}
		}
	}
}

// them monster
void addMonster(float posX, float posY, int frameFirst, int total_frame,int type_Monster)
{
	Monster* newMonster = new Monster(posX, posY, frameFirst, total_frame, type_Monster);
	ls_Monster.push_back(newMonster);
}

// tong hop them monster
void total_AddMonster()
{
	addMonster(300, 920, YELLOW_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(1730, 1400, YELLOW_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(1700, 1150, YELLOW_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(2700, 2550, YELLOW_BATH_1, 4, IMAGE_TWO_BATH);

	addMonster(200, 370, BLACK_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(1250, 920, BLACK_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(1700, 1950, BLACK_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(1500, 2550, BLACK_BATH_1, 4, IMAGE_TWO_BATH);
	addMonster(5650, 1800, BLACK_BATH_1, 4, IMAGE_TWO_BATH);

	addMonster(1650, 220, SLIME_1_1, 3, IMAGE_SLIME_1);
	addMonster(270, 2630, SLIME_1_1, 3, IMAGE_SLIME_1);

	addMonster(1720, 1610, SLIME_2_1, 4, IMAGE_SLIME_2);
	addMonster(620, 2080, SLIME_2_1, 4, IMAGE_SLIME_2);

	addMonster(660, 1150, DINOSAURS_1, 6, IMAGE_DINOSAURS);
	addMonster(2710, 1230, DINOSAURS_1, 6, IMAGE_DINOSAURS);
	addMonster(2465, 990, DINOSAURS_1, 6, IMAGE_DINOSAURS);
	addMonster(2470, 470, DINOSAURS_1, 6, IMAGE_DINOSAURS);

	addMonster(1690, 2631, ZOMBIE_1, 16, IMAGE_ZOMBIE);


	addMonster(6000, 2000, DRAGON_BOSS_1, 4, IMAGE_DRAGON_BOSS);
}

void render_map(SDL_Rect& camera)
{
	//VE BACKGROUND
	if (!pause) run_--;
	if (run_ <=- 1950)
	{
		run_ = 0;
	}
	SDL_Rect sky_rect = {3000 -camera.x + run_ ,-camera.y,4950-3000,MAP_HEIGHT };
	SDL_RenderCopy(renderer, image_background[BG_CLOUDS2].getTexture(), NULL, &sky_rect);
	sky_rect.x = 4950 - camera.x + run_;
	SDL_RenderCopy(renderer, image_background[BG_CLOUDS2].getTexture(), NULL, &sky_rect);

	SDL_Rect BG_1_rect = { 50-camera.x,-camera.y,2050,1700 };
	SDL_RenderCopy(renderer, image_background[BG_1].getTexture(), NULL, &BG_1_rect);
	SDL_Rect BG_night_rect = { -camera.x,1700 - camera.y,3000,1100 };
	SDL_RenderCopy(renderer, image_background[BG_NIGHT].getTexture(), NULL, &BG_night_rect);
	SDL_Rect BG_sun_set_rect = { 2300 - camera.x,-camera.y,650,1700 };
	SDL_RenderCopy(renderer, image_background[BG_SUN_SET].getTexture(), NULL, &BG_sun_set_rect);
	SDL_Rect BG_boss_1_rect = { 4950 - camera.x,50 - camera.y,1550,1700 };
	SDL_RenderCopy(renderer, image_background[BG_2].getTexture(), NULL, &BG_boss_1_rect);
	SDL_Rect BG_boss_2_rect = { 5000 - camera.x,1750 - camera.y,1500,1050 };
	SDL_RenderCopy(renderer, image_background[BG_3].getTexture(), NULL, &BG_boss_2_rect);

	// tree
	SDL_Rect tree_1_rect = { 300 - camera.x,2450 - camera.y,300,250 };
	SDL_RenderCopy(renderer, image_background[TREE_1].getTexture(), NULL, &tree_1_rect);
	tree_1_rect.x = 1500 - camera.x;
	SDL_RenderCopy(renderer, image_background[TREE_1].getTexture(), NULL, &tree_1_rect);
	SDL_Rect tree_3_rect = { 2350 - camera.x,350 - camera.y,200,210 };
	SDL_RenderCopy(renderer, image_background[TREE_3].getTexture(), NULL, &tree_3_rect);
	SDL_Rect hourse_tree_rect = { 2750 - camera.x,90 - camera.y,200,250 };
	SDL_RenderCopy(renderer, image_background[HOURSE_TREE].getTexture(), NULL, &hourse_tree_rect);
	// rip
	SDL_Rect rip_rect = { 1690 - camera.x,2630 - camera.y,62,71 };
	SDL_RenderCopy(renderer, image_background[BG_RIP].getTexture(), NULL, &rip_rect);
	// boat
	SDL_Rect boat_rect = { 5400 - camera.x,2415 - camera.y,200,240 };
	SDL_RenderCopy(renderer, image_background[BOAT].getTexture(), NULL, &boat_rect);
	//VE MAP
	for (int i = 0; i < TOTAL_TILE_HEIGHT; i++)
	{
		for (int j = 0; j < TOTAL_TILE_WIDTH; j++)
		{
			if (checkCollision(tile[i][j]->getBox(), camera) && tile[i][j]->getType() != 0)
			{
				if (tile[i][j]->getType() == TILE_TOP_LEFT)     //---------------------------- 1
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[TOP_LEFT]);
				}
				else if (tile[i][j]->getType() == TILE_TOP_CENTER)      //---------------------------- 2
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[TOP_CENTER]);
				}
				else if (tile[i][j]->getType() == TILE_TOP_RIGHT)       //---------------------------- 3
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[TOP_RIGHT]);
				}
				else if (tile[i][j]->getType() == TILE_MIDDLE_CENTER)     //---------------------------- 4
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[MIDDLE_CENTER]);
				}
				else if (tile[i][j]->getType() == TILE_BOTTOM_LEFT)       //---------------------------- 5
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[BOTTOM_LEFT]);
				}
				else if (tile[i][j]->getType() == TILE_BOTTOM_CENTER)      //---------------------------- 6
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[BOTTOM_CENTER]);
				}
				else if (tile[i][j]->getType() == TILE_BOTTOM_RIGHT)       //---------------------------- 7
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[BOTTOM_RIGHT]);
				}
				else if (tile[i][j]->getType() == TILE_TREE)          //---------------------------- 8
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[TREE]);
				}
				else if (tile[i][j]->getType() == TILE_ROCK)        //---------------------------- 9
				{
					tile[i][j]->renderTile(camera, ROCK, NULL);
				}
				else if (tile[i][j]->getType() == TILE_ROCK_2)      //---------------------------- 99
				{
					tile[i][j]->renderTile(camera, ROCK_2, NULL);
				}
				else if (tile[i][j]->getType() == TILE_TOP_TUBE)     //---------------------------- 10
				{
					tile[i][j]->renderTile(camera, TOP_TUBE, NULL);
				}
				else if (tile[i][j]->getType() == TILE_BOTTOM_TUBE)       //----------------------------11
				{
					tile[i][j]->renderTile(camera, BOTTOM_TUBE, NULL);
				}
				else if (tile[i][j]->getType() == TILE_LEFT_)        //---------------------------- 12
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[LEFT_]);
				}
				else if (tile[i][j]->getType() == TILE_CENTER_)      //---------------------------- 13
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[CENTER_]);
				}
				else if (tile[i][j]->getType() == TILE_RIGHT_)       //---------------------------- 14
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[RIGHT_]);
				}
				else if (tile[i][j]->getType() == TILE_BOX)       //---------------------------- 15
				{
					tile[i][j]->renderTile(camera, BOX, NULL);
				}
				else if (tile[i][j]->getType() == TILE_MIDDLE_LEFT)     //---------------------------- 16
				{
					tile[i][j]->renderTile(camera, LAND,cut_image_LAND[MIDDLE_LEFT]);
				}
				else if (tile[i][j]->getType() == TILE_MIDDLE_RIGHT)        //---------------------------- 17
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[MIDDLE_RIGHT]);
				}
				else if (tile[i][j]->getType() == TILE_TOP_)      //------------------------------- 18
				{
					tile[i][j]->renderTile(camera, LAND, cut_image_LAND[TOP_]);
				}
				else if (tile[i][j]->getType() == TILE_COIN)      //------------------------------- -1
				{
					tile[i][j]->renderTile(camera, COIN, 0, 9, cut_image_coin);
				}
				else if (tile[i][j]->getType() == TILE_BLACK)    //------------------------------- -9
				{
					SDL_Rect black = { tile[i][j]->getBox().x - camera.x,tile[i][j]->getBox().y - camera.y,50,50 };
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderFillRect(renderer, &black);   
				}
				else if (tile[i][j]->getType() == TILE_FLAG)      //------------------------------- -2
				{
					tile[i][j]->renderTile(camera, FLAG, 0, 6, cut_image_flag);
				}
				else if (tile[i][j]->getType() == TILE_WATER)      //------------------------------- -5
				{
					tile[i][j]->renderTile(camera, WATER, 0, 8, cut_image_water);
				}
				else if (tile[i][j]->getType() == TILE_STATIC_WATER)      //------------------------------- -5
				{
					tile[i][j]->renderTile(camera, WATER, cut_image_water[8]);
				}
				else if (tile[i][j]->getType() == TILE_HEART)      //------------------------------- -6
				{
				tile[i][j]->renderTile(camera, HEART, 0, 12, cut_image_heart);
				}
				// set save
				if (checkCollision(person.getBox(), tile[i][j]->getBox()) && tile[i][j]->getType() == -2)
				{
					person.setPositionSave({ tile[i][j]->getBox().x,tile[i][j]->getBox().y });
				}
			}
		}
	}
}

void render_player_and_monsters(SDL_Rect& camera)
{
	// VE MONSTER
	for (int i = 0; i < ls_Monster.size()-1; i++)
	{
		ls_Monster.at(i)->renderMonster(camera, image_monster[ls_Monster[i]->getTypeMonster()].getTexture());
		if (checkCollision(person.getBox(), ls_Monster.at(i)->getBox()))
		{
			person.setIsDead(true);
			if(!pause) Mix_PlayChannel(1, sound_effects[MUSIC_LOSE_LIFE], 0);
		}
	}

	//VE BOSS: DRAGON
	if (person.is_started_surviving() && menu.is_selected_ok())
	{
		ls_Monster[ls_Monster.size() - 1]->renderDragon(camera);
		if (checkCollision(person.getBox(), ls_Monster.at(ls_Monster.size() - 1)->getBox_Dragon()))
		{
			person.setIsDead(true);
			if (!pause) Mix_PlayChannel(-1, sound_effects[MUSIC_LOSE_LIFE], 0);
		}
	}
	// VE NHAN VAT
	person.renderPlayer(camera);
}

void resetValue()
{
	if (pause)
	{
		pause = false;
	}
	person.setX(51);
	person.setY(0);
	person.setVelX(0);
	person.setVelY(0);
	person.setOnGround(false);
	person.setJump(false);
	person.setIsDead(false);
	person.setCountCoin(0);
	person.setHeart(total_heart);
	person.setWin(false);
	menu.setGameOver(false);
	menu.set_is_selected_ok(false);
	for (int i = 0; i < ls_Monster.size(); i++)
	{
		if (ls_Monster.at(i)->getTypeMonster() == IMAGE_ZOMBIE)
		{
			ls_Monster.at(i)->setRise(false);
		}
	}
	total_coin = 0;
	setTiles(tile);
}

void count_down(SDL_Rect& camera)
{
	std::stringstream count_down_;
	count_down_.str("");
	if (!timer_count_down.isStarted() && is_start_count_down && !person.isDead())
	{
		timer_count_down.start();
	}
	if (timer_count_down.isStarted())
	{
		if (pause)
		{
			timer_count_down.pause();
		}
		else
		{
			timer_count_down.unPause();
		}
	}
	if (is_start_count_down && timer_count_down.isStarted())
	{
		if (MAX_TIME_COUNT_DOWN <= timer_count_down.getTime() / 1000 || person.isDead())
		{
			timer_count_down.stop();
			is_start_count_down = false;
			person.setSurvival(false);
			menu.set_is_selected_ok(false);
			// loi ra khi win
			tile[44][107]->setType(0);
			tile[45][107]->setType(0);
		}
		else
		{
			int minute = (MAX_TIME_COUNT_DOWN - timer_count_down.getTime() / 1000) / 60;
			int second = (MAX_TIME_COUNT_DOWN - timer_count_down.getTime() / 1000) - minute * 60;
			count_down_ << 0 << minute << ":";
			if (second >= 10)
			{
				count_down_ << second;
			}
			else
			{
				count_down_ << 0 << second;
			}
		}
	}
	else
	{
		count_down_ << "00:00";
	}
	if (!menu.is_selected_tutorial() && menu.is_selected_play_game() && is_start_count_down && timer_count_down.isStarted())
	{
		if (countDown.loadFromText(count_down_.str().c_str(), font_count_down, { 120,0,120 }));
		{
			countDown.renderTexture(5600 - camera.x, 2000 - camera.y, NULL);
		}
	}
}

// ham ve chinh
void render_main(SDL_Rect& camera)
{
	// menu chinh
	menu.showMenu();
	if (menu.is_selected_play_game() )
	{
		if (!menu.is_selected_tutorial())
		{
		// ve map
		render_map(camera);
		}

		// dem nguoc
		count_down(camera);

		if (!menu.is_selected_tutorial())
		{
		// ve player va quai vat
		render_player_and_monsters(camera);
		// chi so sinh mang va vang
		menu.renderTheNumberOfHeartAndCoin();
		// nut option
		menu.renderOption();
		// bat dau sinh ton
		menu.renderSurvival();
		// congratulations
		menu.renderCongratulations();
		}
	}
	setMusic();
}

void close()
{
	// delete cut anh
	for (int i = 0; i < TOTAL_CUT_IMAGE_LAND; i++)
	{
		delete cut_image_LAND[i];
		cut_image_LAND[i] = NULL;
	}
	for (int i = 0; i < TOTAL_CUT_IMAGE_MONSTER; i++)
	{
		delete cut_image_MONSTER[i];
		cut_image_MONSTER[i] = NULL;
	}
	for (int i = 0; i < 9; i++)
	{
		delete cut_image_coin[i];
		cut_image_coin[i] = NULL;
	}
	for (int i = 0; i < 6; i++)
	{
		delete cut_image_flag[i];
		cut_image_flag[i] = NULL;
	}
	for (int i = 0; i < 9; i++)
	{
		delete cut_image_water[i];
		cut_image_water[i] = NULL;
	}
	for (int i = 0; i < 12; i++)
	{
		delete cut_image_heart[i];
		cut_image_heart[i] = NULL;
	}
	// delete tile
	for (int i = 0; i < TOTAL_TILE_HEIGHT; i++)
	{
		for (int j = 0; j < TOTAL_TILE_WIDTH; j++)
		{
			delete tile[i][j];
			tile[i][j] = NULL;
		}
	}
	// delete monster
	for (int i = 0; i < ls_Monster.size(); i++)
	{
		delete ls_Monster.at(i);
		ls_Monster.at(i) = NULL;
	}
	// delete music
	for (int i = MUSIC_JUMP; i < TOTAL_SOUND_EFFECTS; i++)
	{
		Mix_FreeChunk(sound_effects[i]);
		sound_effects[i] = NULL;
	}
	Mix_FreeMusic(music_intro);
	music_intro = NULL;
	Mix_FreeMusic(music_background_forest);
	music_background_forest = NULL;
	Mix_FreeMusic(music_background_wind);
	music_background_wind = NULL;
	Mix_FreeMusic(music_background_dragon);
	music_background_dragon = NULL;
	// delete font
	TTF_CloseFont(font);
	font = NULL;
	TTF_CloseFont(temp_font);
	temp_font = NULL;
	TTF_CloseFont(font_count_down);
	font_count_down = NULL;
	SDL_DestroyRenderer(renderer);

	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
