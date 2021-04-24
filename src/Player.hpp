#pragma once
#include<SDL.h>

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;

const float GRAVITY_PLAYER = 0.1;
const float MAX_VELX = 5.0;

const float R_EYES = 3.5;
extern float MAX_HIGHT;
const int total_heart = 3;

class Player
{
private:
	int heart ;
	float posX, posY;
	float velX, velY;
	bool onGround;
	bool jumping;
	bool player_move;
	bool dead; 
	bool start_surviving;
	int count_coin;
	SDL_Point  position_save;
	bool win;
public:
	Player(float x, float y);
	~Player();

	float distanceFromCursor_left(SDL_Rect camera);
	float distanceFromCursor_right(SDL_Rect camera);
	float distanceFromCursor_bottom(SDL_Rect camera);
	void jump(SDL_Rect &camera);
	void move(SDL_Rect& camera);
	void update(SDL_Rect& camera);
	void renderPlayer(SDL_Rect& camera);
	void setCamera(SDL_Rect& camera);
	void setEyes(SDL_Rect& camera, float posX, float posY);
	void comeBack();

	void setX(float x);
	void setY(float y);
	void setVelX(float velX);
	void setVelY(float velY);
	void setJump(bool jump);
	void setCountCoin(int coin);
	void setOnGround(bool onGround); 
	void setIsMoving(bool move);
	void setHeart(int heart);
	void setIsDead(bool dead);
	void setSurvival(bool is_start_surviving);
	void setPositionSave(SDL_Point pos_save);
	void setWin(bool win);
	float getX();
	float getY();
	bool isOnGround();
	bool isDead();
	bool isMoving();
	bool is_started_surviving();
	SDL_Rect getBox();
	int getCoin();
	int getHeart();
	SDL_Point getPositionSave();
	bool isWon();
};