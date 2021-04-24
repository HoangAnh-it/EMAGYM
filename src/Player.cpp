#include"Function.hpp"

float MAX_HIGHT = 150;

Player::Player(float x, float y)
{
	posX = x;
	posY = y;
	velX = velY = 0;
	onGround = false;
	player_move = false;
	jumping = true;
	dead = false;
	count_coin = 0;
	heart = total_heart;
	start_surviving = false;
	position_save.x = 51;
	position_save.y = 0;
	win = false;
}

Player::~Player()
{
	std::cout << "Destroyed" << std::endl;
}

float Player::distanceFromCursor_left(SDL_Rect camera)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return sqrt(pow(posX - x - camera.x, 2) + pow(posY - y - camera.y, 2));
}

float Player::distanceFromCursor_right(SDL_Rect camera)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return sqrt(pow(posX + PLAYER_WIDTH - x - camera.x, 2) + pow(posY + PLAYER_WIDTH - y - camera.y, 2));
};

float Player::distanceFromCursor_bottom(SDL_Rect camera)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return sqrt(pow(posX + PLAYER_WIDTH / 2 - x - camera.x, 2) + pow(posY + PLAYER_HEIGHT - y - camera.y, 2));
}

void Player::setX(float x)
{
	this->posX = x;
}

void Player::setY(float y)
{
	this->posY = y;
}

void Player::setOnGround(bool onGround)
{
	this->onGround = onGround;
}

void Player::setHeart(int heart)
{
	this->heart = heart;
}

void Player::setPositionSave(SDL_Point pos_save)
{
	this->position_save.x = pos_save.x;
	this->position_save.y = pos_save.y;
}

void Player::setCamera(SDL_Rect& camera)
{
	camera.x = (posX + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (posY + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > MAP_WIDTH - SCREEN_WIDTH)
	{
		camera.x = MAP_WIDTH - SCREEN_WIDTH;
	}
	if(camera.y > MAP_HEIGHT - SCREEN_HEIGHT)
	{
		camera.y = MAP_HEIGHT - SCREEN_HEIGHT;
	}
}

void Player::jump(SDL_Rect &camera)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (distanceFromCursor_bottom(camera) >= 1 && distanceFromCursor_bottom(camera) <= 70 && y + camera.y >= posY + PLAYER_HEIGHT && x + camera.x >= posX && x + camera.x <= posX + PLAYER_WIDTH - 5 && onGround)
	{
		velY -= 1 + 9 / distanceFromCursor_bottom(camera);
		onGround = false;
		jumping = true;
		Mix_PlayChannel(-1, sound_effects[MUSIC_JUMP], 0);
	}
	if (jumping)
	{
		MAX_HIGHT += velY;
		if (MAX_HIGHT <= 0)
		{
			jumping = false;
			MAX_HIGHT = 150;
		}
	}
	else
	{
		MAX_HIGHT = 150;
	}
	if (distanceFromCursor_bottom(camera) >= 70 || y + camera.y < posY + PLAYER_HEIGHT - 5)
	{
		jumping = false;
	}
}

void Player::move(SDL_Rect& camera)
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);

	// set X
	if (distanceFromCursor_left(camera) >= 1 && distanceFromCursor_left(camera) <= 90 && x + camera.x <= posX + 3 && y + camera.y < posY + PLAYER_HEIGHT && !jumping)
	{
		velX += 1 / distanceFromCursor_left(camera) * 90;
		player_move = true;
	}
	else if (distanceFromCursor_right(camera) >= 1 && distanceFromCursor_right(camera) <= 90 && x + camera.x >= posX + PLAYER_WIDTH - 3 && y + camera.y < posY + PLAYER_HEIGHT && !jumping)
	{
		velX += -1 / distanceFromCursor_right(camera) * 90;
		player_move = true;
	}
	else
	{
		velX = 0;
		player_move = false;
	}

	if (velX >= MAX_VELX)
	{
		velX = MAX_VELX;
	}
	else if (velX <= -MAX_VELX)
	{
		velX = -MAX_VELX;
	}
	//set Y
	if (!onGround && !jumping)
	{
		velY += GRAVITY_PLAYER;
	}
	else
	{
		jump(camera);
	}
}

void Player::comeBack()
{
	if (!win) heart--;
	if (heart >= 1)
	{
		posX = position_save.x;
		posY = position_save.y - 50;
		onGround = false;
		dead = false;
		if (menu.is_selected_ok() && person.is_started_surviving())
		{
			menu.set_is_selected_ok(false);
			start_surviving = false;
			tile[33][113]->setType(0);
		}
	}
	else
	{
		menu.setGameOver(true);
		image_player[HEAD_AND_BODY].setAlpha(255);
		image_player[LEFT_LEG].setAlpha(255);
		image_player[RIGHT_LEG].setAlpha(255);
		menu.set_is_selected_play_game(false);
	}
	// loi vao boss
	if (tile[33][113]->getType() == 99)
	{
		tile[33][113]->setType(0);
	}
}

void Player::update(SDL_Rect &camera)
{
	if (!pause)
	{
		move(camera);

		// check map
		int x1 = 0;
		int x2 = 0;
		int y1 = 0;
		int y2 = 0;

		float height_min = PLAYER_HEIGHT > TILE_HEIGHT ? PLAYER_HEIGHT * 5 / 6 : PLAYER_HEIGHT;
		x1 = (posX + velX + 8 + 1) / TILE_WIDTH;
		x2 = (posX + velX + PLAYER_WIDTH - 1 - 8) / TILE_WIDTH;
		y1 = (posY + 1) / TILE_HEIGHT;
		y2 = (posY + height_min + 1) / TILE_HEIGHT;
		if (x1 >= 0 && x2 < TOTAL_TILE_WIDTH && y1 >= 0 && y2 < TOTAL_TILE_HEIGHT)
		{
			if (velX > 0)
			{
				if (tile[y1][x2]->getType() >= 1 || tile[y2][x2]->getType() >= 1)
				{
					posX = x2 * TILE_WIDTH + 8;
					posX -= PLAYER_WIDTH;
					velX = 0;
				}
				else if (tile[y1][x2]->getType() == -1 && posY <= tile[y1][x2]->getBox().y + 30 && posX + velX + PLAYER_WIDTH >= tile[y1][x2]->getBox().x + 15)
				{
					tile[y1][x2]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y2][x2]->getType() == -1 && posX + velX + PLAYER_WIDTH - 8 >= tile[y1][x2]->getBox().x + 15)
				{
					tile[y2][x2]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y1][x2]->getType() == -6 )
				{
					heart++;
					tile[y1][x2]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
				else if (tile[y2][x2]->getType() == -6)
				{
					heart++;
					tile[y2][x2]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
			}
			else if (velX < 0)
			{
				if (tile[y1][x1]->getType() >= 1 || tile[y2][x1]->getType() >= 1)
				{
					posX = (x1 + 1) * TILE_WIDTH - 8;
					velX = 0;
				}
				else if (tile[y1][x1]->getType() == -1 && posY <= tile[y1][x1]->getBox().y + 30 && posX + velX <= tile[y1][x1]->getBox().x + 30 + 15)
				{
					tile[y1][x1]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y2][x1]->getType() == -1 && posX + velX + 8 <= tile[y2][x1]->getBox().x + 30 + 15)
				{
					tile[y2][x1]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y1][x1]->getType() == -6)
				{
					heart++;
					tile[y1][x1]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
				else if (tile[y2][x1]->getType() == -6)
				{
					heart++;
					tile[y2][x1]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
			}
		}

		float width_min = PLAYER_WIDTH < TILE_WIDTH ? PLAYER_WIDTH : PLAYER_WIDTH * 5 / 6;
		x1 = (posX + 8 + 1) / TILE_WIDTH;
		x2 = (posX + width_min - 1 - 8) / TILE_WIDTH;
		y1 = (posY + velY + 1) / TILE_HEIGHT;
		y2 = (posY + velY + PLAYER_HEIGHT + 1) / TILE_HEIGHT;

		if (x1 >= 0 && x2 < TOTAL_TILE_WIDTH && y1 >= 0 && y2 < TOTAL_TILE_HEIGHT)
		{
			if (velY > 0)
			{

				if (tile[y2][x1]->getType() >= 1 || tile[y2][x2]->getType() >= 1)
				{
					posY = y2 * TILE_HEIGHT;
					posY -= PLAYER_HEIGHT;
					velY = 0;
					onGround = true;
				}
				// gain coin
				else if (tile[y2][x1]->getType() == -1)
				{
					tile[y2][x1]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y2][x2]->getType() == -1)
				{
					tile[y2][x2]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				// gain life
				else if (tile[y2][x1]->getType() == -6  )
				{
					heart++;
					tile[y2][x1]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
				else if (tile[y2][x2]->getType() == -6)
				{
					heart++;
					tile[y2][x2]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
				// roi xuong nuoc
				if (tile[y2][x1]->getType() == -5 || tile[y2][x2]->getType() == -5 || tile[y2][x1]->getType() == -4 || tile[y2][x2]->getType() == -4)
				{
					if (!play_music_2)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_WATER], 0); 
						play_music_2 = true;
					}
				}
				else
				{
						play_music_2 = false;
				}
				// roi xuong dat
				if (tile[y2][x1]->getType() >= 1 && tile[y2][x1]->getType() <= 7 || tile[y2][x1]->getType() >= 12 && tile[y2][x1]->getType() <= 18 && tile[y2][x1]->getType() != 15
				 ||	tile[y2][x2]->getType() >= 1 && tile[y2][x2]->getType() <= 7 || tile[y2][x2]->getType() >= 12 && tile[y2][x2]->getType() <= 18 && tile[y2][x2]->getType() != 15)
				{
					if (!play_music_1)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_FOOTSTEP], 0);
						play_music_1 = true;
					}
				}
				else
				{
					play_music_1 = false;
				}
				// roi xuong Box
				if (tile[y2][x1]->getType() == 15 || tile[y2][x2]->getType() == 15)
				{
					if (!play_music_1)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_FOOTSTEP2], 0);
						play_music_1 = true;
					}
				}
				else
				{
					play_music_1 = false;
				}
				// roi xuong rock
				if (tile[y2][x1]->getType() == 9 || tile[y2][x1]->getType() == 99
					|| tile[y2][x2]->getType() == 9 || tile[y2][x2]->getType() == 99)
				{
					if (!play_music_1)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_FOOTSTEP3], 0);
						play_music_1 = true;
					}
				}
				else
				{
					play_music_1 = false;
				}
				// roi xuong ong
				if (tile[y2][x1]->getType() == 11 || tile[y2][x2]->getType() == 11)
				{
					if (!play_music_1)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_FOOTSTEP4], 0);
						play_music_1 = true;
					}
				}
				else
				{
					play_music_1 = false;
				}
			}
			else if (velY < 0)
			{
				if (tile[y1][x1]->getType() >= 1 || tile[y1][x2]->getType() >= 1)
				{
					posY = (y1 + 1) * TILE_HEIGHT;
					jumping = false;
					velY = 0;
				}
				else if (tile[y1][x1]->getType() == -1 && posY + velY <= tile[y1][x1]->getBox().y + 30)
				{
					tile[y1][x1]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y1][x2]->getType() == -1 && posY + velY <= tile[y1][x2]->getBox().y + 30)
				{
					tile[y1][x2]->setType(0);
					count_coin++;
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_COIN], 0);
				}
				else if (tile[y1][x1]->getType() == -6 )
				{
					heart++;
					tile[y1][x1]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
				else if (tile[y1][x2]->getType() == -6)
				{
					heart++;
					tile[y1][x2]->setType(0);
					Mix_PlayChannel(-1, sound_effects[MUSIC_GAIN_HEART], 0);
				}
			}
			else   // velY = 0
			{
				if (tile[y2][x1]->getType() <= 0 && tile[y2][x2]->getType() <= 0)
				{
					onGround = false;
				}
			}
		}

		// set X,Y
		if (posX + velX < 0)
		{
			posX = 1;
			velX = 0;
		}
		else if (posX + velX + PLAYER_WIDTH > MAP_WIDTH)
		{
			posX = MAP_WIDTH - PLAYER_WIDTH;
			velX = 0;
		}
		if (posY + velY > MAP_HEIGHT)
		{
			dead = true;
		}
		setX(posX + velX);
		setY(posY + velY);
		setCamera(camera);
	}

	// zombie rises
	if (posX >= 1400 && posY >= 2250)
	{
		ls_Monster.at(ls_Monster.size() - 2)->setRise(true);
	}
	//start surviving
	if (checkCollision(getBox(), { 5600,1800,100,50 }) && !menu.is_selected_ok())
	{
		start_surviving = true;
		pause = true;
	}

	if (checkCollision(getBox(), tile[51][106]->getBox()))
	{
		win = true;
	}

	if (count_coin == 81)
	{
		tile[34][39]->setType(0);
		tile[34][40]->setType(0);
	}
	else if (count_coin == 172)
	{
		tile[2][59]->setType(0);
		tile[3][59]->setType(0);
		tile[4][59]->setType(0);
	}
	else if (count_coin == total_coin)
	{
		tile[15][127]->setType(0);
		tile[15][128]->setType(0);
	}
}

void Player::renderPlayer(SDL_Rect& camera)
{
	// hieu ung nhap nhay khi player chet
	if (dead && !pause)
	{
		if (!timer.isStarted())
		{
			timer.start();
		}
		if (timer.getTime() <= 500)
		{
			image_player[HEAD_AND_BODY].setAlpha(image_player[HEAD_AND_BODY].getAlpha() - 32);
			image_player[LEFT_LEG].setAlpha(image_player[LEFT_LEG].getAlpha() - 32);
			image_player[RIGHT_LEG].setAlpha(image_player[RIGHT_LEG].getAlpha() - 32);
		}
		else if (timer.getTime() > 700 && timer.getTime() <= 1000)
		{
			image_player[HEAD_AND_BODY].setAlpha(image_player[HEAD_AND_BODY].getAlpha() + 32);
			image_player[LEFT_LEG].setAlpha(image_player[LEFT_LEG].getAlpha() + 32);
			image_player[RIGHT_LEG].setAlpha(image_player[RIGHT_LEG].getAlpha() + 32);
		}
		else
		{
			timer.stop();
			comeBack();
		}
	}
	else
	{
		image_player[HEAD_AND_BODY].setAlpha(255);
		image_player[LEFT_LEG].setAlpha(255);
		image_player[RIGHT_LEG].setAlpha(255);
	}

	// render player
	update(camera);
	image_player[HEAD_AND_BODY].renderTexture(posX - camera.x, posY - camera.y, NULL);
	if (player_move)
	{
		if ((SDL_GetTicks() / 100) % 3 == 0)
		{
			image_player[LEFT_LEG].renderTexture(posX - camera.x, posY - camera.y - 6, NULL);
			image_player[RIGHT_LEG].renderTexture(posX - camera.x, posY - camera.y , NULL);
		}
		else 
		{
			image_player[LEFT_LEG].renderTexture(posX - camera.x, posY - camera.y , NULL);
			image_player[RIGHT_LEG].renderTexture(posX - camera.x, posY - camera.y - 6, NULL);
		}

	}
	else if (jumping)
	{
		image_player[LEFT_LEG].renderTexture(posX - camera.x, posY - camera.y - 5, NULL);
		image_player[RIGHT_LEG].renderTexture(posX - camera.x, posY - camera.y - 5, NULL);
	}
	else
	{
		image_player[LEFT_LEG].renderTexture(posX - camera.x, posY - camera.y, NULL);
		image_player[RIGHT_LEG].renderTexture(posX - camera.x, posY - camera.y, NULL);
	}
	setEyes(camera,this->posX,this->posY);
}

void Player::setEyes(SDL_Rect& camera,float posX,float posY)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	float distanceTwoEyes = PLAYER_WIDTH - 20;
	float distanceFromMouseToEyes = sqrt(pow(posX + 10 + distanceTwoEyes / 2 - x - camera.x, 2) + pow(posY + 15 - y - camera.y, 2));
	float dau_X_ = 1;
	float dau_Y_ = 1;
	// vi tri X thay doi
	float X_ = 0;
	// vi tri Y thay doi
	float Y_ = 0;

	float sin_angle = 0;
	float cos_angle = 0;
	float dau_posY_15_ = 1;
	float dau_y_camY_ = 1;
	float dau_posX_W2_ = 1;
	float dau_X_camX_ = 1;

	// goc phan tu thu I
	if (x + camera.x >= posX + PLAYER_WIDTH / 2 && y + camera.y < posY + 15)
	{
		dau_posY_15_ = 1;
		dau_y_camY_ = -1;
		dau_posX_W2_ = -1;
		dau_X_camX_ = 1;
		dau_X_ = 1;
		dau_Y_ = -1;
	}
	// goc phan tu thu II
	else if (x + camera.x < posX + PLAYER_WIDTH / 2 && y + camera.y < posY + 15)
	{
		dau_posY_15_ = 1;
		dau_y_camY_ = -1;
		dau_posX_W2_ = 1;
		dau_X_camX_ = -1;
		dau_X_ = -1;
		dau_Y_ = -1;
	}
	// goc phan tu thu III
	else if (x + camera.x < posX + PLAYER_WIDTH / 2 && y + camera.y >= posY + 15)
	{
		dau_posY_15_ = -1;
		dau_y_camY_ = 1;
		dau_posX_W2_ = 1;
		dau_X_camX_ = -1;
		dau_X_ = -1;
		dau_Y_ = 1;
	}
	// goc phan tu thu IV
	else if (x + camera.x >= posX + PLAYER_WIDTH / 2 && y + camera.y >= posY + 15)
	{
		dau_posY_15_ = -1;
		dau_y_camY_ = 1;
		dau_posX_W2_ = -1;
		dau_X_camX_ = 1;
		dau_X_ = 1;
		dau_Y_ = 1;
	}

	sin_angle = (dau_posY_15_ * (posY + 15) + dau_y_camY_ * (y + camera.y)) / distanceFromMouseToEyes;
	cos_angle = (dau_X_camX_ * (x + camera.x) + dau_posX_W2_ * (posX + PLAYER_WIDTH / 2)) / distanceFromMouseToEyes;

	X_ = cos_angle * R_EYES;
	Y_ = sin_angle * R_EYES;

	image_player[EYES].renderTexture(posX - camera.x + dau_X_ * X_, posY - camera.y + dau_Y_ * Y_, NULL);
}

float Player::getX()
{
	return posX;
}

float Player::getY()
{
	return posY;
}

bool Player::isOnGround()
{
	return onGround;
}



bool Player::isDead()
{
	return dead;
}

SDL_Rect Player::getBox()
{
	SDL_Rect box = { posX + 8,posY,PLAYER_WIDTH - 16,PLAYER_HEIGHT };
	return box;
}

int Player::getCoin()
{
	return count_coin;
}

int Player::getHeart()
{
	return heart;
}

SDL_Point Player::getPositionSave()
{
	return position_save;
}

bool Player::is_started_surviving()
{
	return start_surviving;
}

bool Player::isWon()
{
	return win;
}

void Player::setIsDead(bool dead)
{
	this->dead = dead;
}

void Player::setJump(bool jump)
{
	this->jumping = jump;
}

void Player::setCountCoin(int coin)
{
	this->count_coin = coin;
}

void Player::setSurvival(bool is_start_surviving)
{
	this->start_surviving = is_start_surviving;
}

void Player::setWin(bool win)
{
	this->win = win;
}

void Player::setIsMoving(bool move)
{
	this->player_move = move;
}

void Player::setVelX(float velX)
{
	this -> velX = velX;
}

void Player::setVelY(float velY)
{
	this->velY = velY;
}