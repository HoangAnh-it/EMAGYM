#include "Function.hpp"

Tile::Tile(int x, int y, int  type_map)
{
	box.x = x;
	box.y = y;
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;
	this->type_map = type_map;
	frame_run = 0;
}

Tile::~Tile()
{
	box.x = box.y = box.w = box.h = 0;
	std::cout << "Destroyed Tile" << std::endl;
}

void Tile::renderTile(SDL_Rect& camera, int TYPE_TILE, SDL_Rect* srcrect)  // TYPE_TILE: chi so trong mang image_tile[]
{
		SDL_Rect dscrect = { box.x - camera.x,box.y - camera.y,TILE_WIDTH,TILE_HEIGHT };
		SDL_RenderCopy(renderer, image_tile[TYPE_TILE].getTexture(), srcrect, &dscrect);
}

void Tile::renderTile(SDL_Rect& camera, int TYPE_TILE, int frameFirst, int total_frame, SDL_Rect* srcrect[])  // TYPE_TILE: chi so trong mang image_tile[]
{ 
	setFrameFirst(frameFirst);
	setTotalFrame(total_frame);
	SDL_Rect dscrect = { box.x - camera.x,box.y - camera.y,TILE_WIDTH,TILE_HEIGHT };
	if (TYPE_TILE == COIN)
	{
		dscrect = { box.x - camera.x + 15,box.y - camera.y,30,30 };
	}
	SDL_RenderCopy(renderer, image_tile[TYPE_TILE].getTexture(), srcrect[frame_run / FRAME_TILE], &dscrect);
	if (!pause)
	{
		frame_run++;
	}
	if (frame_run / FRAME_TILE >= frameFirst + total_frame)
	{
		frame_run = frameFirst * FRAME_TILE;
	}
}

SDL_Rect Tile::getBox()
{
	return box;
}

int Tile::getType()
{
	return type_map;
}

int Tile::getFrameFirst()
{
	return frameFirst;
}

int Tile::getTotalFrame()
{
	return total_frame;
}

void Tile::setType(int type)
{
	this->type_map = type;
}

void Tile::setFrameFirst(int frameFirst)
{
	this->frameFirst = frameFirst;
}

void Tile::setTotalFrame(int totalFrame)
{
	this->total_frame = totalFrame;
}