#pragma once
#include<SDL.h>

const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;
const int TOTAL_TILE_WIDTH = 130;
const int TOTAL_TILE_HEIGHT = 56;

const int FRAME_TILE = 6;

class Tile
{
private:
	int type_map; // chi so trong Map
	SDL_Rect box;
	int frame_run;  // danh rieng cho coin
	int frameFirst;
	int total_frame;
public:
	Tile(int x, int y, int type_map);
	~Tile();

	// static tile
	void renderTile(SDL_Rect& camera,int TYPE_TILE,SDL_Rect *scrrect);
	//dynamic tile
	void renderTile(SDL_Rect& camera, int TYPE_TILE, int frameFirst, int total_frame, SDL_Rect* srcrect[]);

	void setFrameFirst(int frameFirst);
	void setTotalFrame(int totalFrame);
	void setType(int type);
	int getType();
	SDL_Rect getBox();
	int getFrameFirst();
	int getTotalFrame();
};
