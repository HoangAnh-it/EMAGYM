#pragma once
#include<SDL.h>
#include<vector>
#include"LTexture.hpp"

const int MONSTER_WIDTH = 50;
const int MONSTER_HEIGHT = 50;

const int FRAME_MONSTER = 10;
const float GRAVITY_MONSTER = 2;
const float VEL_MONSTER_ = 1.5;
const float VEL_DRAGON_ = 1.5;

const int DRAGON_WIDTH = 100;
const int DRAGON_HEIGHT = 100;

class Monster
{
private:
	float posX, posY;
	float velX, velY;
	int frame_run,frameFirst, total_frame;
	int TYPE_MONSTER;
	bool onGround;
	bool rise; // rieng cho zoombie
	bool turn_left;
	bool turn_right;
	SDL_RendererFlip flip;
public:
	Monster(float posX, float posY,int frameFirst, int total_frame,int TYPE_MONSTER);
	~Monster();
	void move();
	void renderMonster(SDL_Rect& camera, SDL_Texture* image);
	void dragon_move();
	void renderDragon(SDL_Rect& camera);

	void setPosX(float posX);
	void setPosY(float posY);
	void setRise(bool rise);
	float getPosX();
	float getPosY();
	int getTypeMonster();
	SDL_Rect getBox();
	SDL_Rect getBox_Dragon();
};