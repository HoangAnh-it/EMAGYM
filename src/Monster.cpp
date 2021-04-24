#include "Function.hpp"


Monster::Monster(float posX, float posY, int frameFirst, int total_frame, int TYPE_MONSTER)
{
	this->posX = posX;
	this->posY = posY;
	this->total_frame = total_frame;
	velX = velY = 0;
	frame_run = frameFirst * FRAME_MONSTER;
	this->frameFirst = frameFirst;
	this->TYPE_MONSTER = TYPE_MONSTER;
	this->onGround = false;
	rise = false;
	turn_left = true;
	turn_right = false;
	if (this->TYPE_MONSTER == IMAGE_TWO_BATH)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
	flip = SDL_FLIP_NONE;
	}
}

Monster::~Monster()
{
	posX = posY = velX = velY = total_frame = frameFirst=frame_run = 0;
	std::cout << "Destroyed Monster" << std::endl;
}

void Monster::renderMonster(SDL_Rect& camera, SDL_Texture* image)
{
		if ((TYPE_MONSTER == IMAGE_ZOMBIE && rise) || TYPE_MONSTER != IMAGE_ZOMBIE)
		{
			move();
			SDL_Rect dscrect = { posX - camera.x,posY - camera.y,MONSTER_WIDTH,MONSTER_HEIGHT };
			SDL_RenderCopyEx(renderer, image, cut_image_MONSTER[frame_run / FRAME_MONSTER], &dscrect, 0, NULL, flip);
			if (!pause)
			{
				frame_run++;
			}
			if (frame_run / FRAME_MONSTER >= total_frame + frameFirst)
			{
				if (TYPE_MONSTER == IMAGE_ZOMBIE)
				{
					frame_run = ZOMBIE_8 * FRAME_MONSTER;
				}
				else
				{
					frame_run = frameFirst * FRAME_MONSTER;
				}
			}
		}
}

void Monster::move()
{
	if (!pause)
	{
		int x1 = 0;
		int x2 = 0;
		int y1 = 0;
		int y2 = 0;

		// set position X
		if (turn_left)
		{
			if ((TYPE_MONSTER == IMAGE_ZOMBIE && frame_run == ZOMBIE_8 * FRAME_MONSTER) || TYPE_MONSTER != IMAGE_ZOMBIE)
				velX = -VEL_MONSTER_;
		}
		else if (turn_right)
		{
			velX = VEL_MONSTER_;
		}

		x1 = (posX + velX + 1) / TILE_WIDTH;
		x2 = (posX + velX + MONSTER_WIDTH - 1) / TILE_WIDTH;
		y1 = (posY + 1) / TILE_HEIGHT;
		y2 = (posY + MONSTER_HEIGHT - 1) / TILE_HEIGHT;

		if (x1 >= 0 && x2 < TOTAL_TILE_WIDTH && y1 >= 0 && y2 < TOTAL_TILE_HEIGHT - 1)
		{
			if (velX > 0)
			{
				if (tile[y1][x2]->getType() >= 1 || tile[y2][x2]->getType() >= 1|| tile[y2+1][x2]->getType() ==-5 || (tile[y2 + 1][x2]->getType() == 0 && TYPE_MONSTER != IMAGE_TWO_BATH))
				{
					turn_right = false;
					turn_left = true;
					velX = 0;
					if (TYPE_MONSTER == IMAGE_TWO_BATH)
					{
						flip = SDL_FLIP_HORIZONTAL;
					}
					else
					{
						flip = SDL_FLIP_NONE;
					}
				}
			}
			else if (velX < 0)
			{
				if (tile[y1][x1]->getType() >= 1 || tile[y2][x1]->getType() >= 1|| tile[y2+1][x1]->getType() ==-5 || (tile[y2 + 1][x1]->getType() == 0 && TYPE_MONSTER != IMAGE_TWO_BATH))
				{
					turn_left = false;
					turn_right = true;
					velX = 0;
					if (TYPE_MONSTER == IMAGE_TWO_BATH)
					{
						flip = SDL_FLIP_NONE;
					}
					else
					{
						flip = SDL_FLIP_HORIZONTAL;
					}
				}
			}
		}

		// set position Y
		if (!onGround && TYPE_MONSTER != IMAGE_TWO_BATH)
		{
			velY += GRAVITY_MONSTER;
		}

		x1 = (posX + 1) / TILE_WIDTH;
		x2 = (posX + MONSTER_WIDTH - 1) / TILE_WIDTH;
		y1 = (posY + velY + 1) / TILE_HEIGHT;
		y2 = (posY + velY + MONSTER_HEIGHT - 1) / TILE_HEIGHT;

		if (x1 >= 0 && x2 < TOTAL_TILE_WIDTH && y1 >= 0 && y2 < TOTAL_TILE_HEIGHT)
		{
			if (velY > 0)
			{
				if (tile[y2][x1]->getType() >= 1 || tile[y2][x2]->getType() >= 1)
				{
					posY = y2 * TILE_HEIGHT;
					posY -= MONSTER_HEIGHT;
					velY = 0;
					onGround = true;
				}
			}
		}

		// setX,Y
		setPosX(posX + velX);
		setPosY(posY + velY);
	}
}

void Monster::dragon_move()
{
	if (!pause)
	{
		float dau_dragon_posX = 1;
		float dau_dragon_posY = 1;

		if (posX + DRAGON_WIDTH-10 > person.getX())
		{
			dau_dragon_posX = -1;
			if (posX + DRAGON_WIDTH / 2 >= person.getX() + PLAYER_WIDTH / 2)
			{
				flip = SDL_FLIP_NONE;
			}
		}
		else if (posX + DRAGON_WIDTH -10 < person.getX())
		{
			dau_dragon_posX = 1;
			if (posX + DRAGON_WIDTH / 2 < person.getX() + PLAYER_WIDTH / 2)
			{
				flip = SDL_FLIP_HORIZONTAL;
			}
		}
		if (posY + DRAGON_HEIGHT > person.getY() + PLAYER_HEIGHT / 2)
		{
			dau_dragon_posY = -1;
		}
		else if (posY + DRAGON_HEIGHT < person.getY() + PLAYER_HEIGHT / 2)
		{
			dau_dragon_posY = 1;
		}

		velX = dau_dragon_posX * VEL_DRAGON_;
		velY = dau_dragon_posY * VEL_DRAGON_;

		int x1 = 0;
		int x2 = 0;
		int y1 = 0;
		int y2 = 0;

		// theo chieu ngang
		int height_min = DRAGON_HEIGHT < TILE_HEIGHT ? DRAGON_HEIGHT : DRAGON_HEIGHT * 2 / 3;
		x1 = (posX + velX + 1) / TILE_WIDTH;
		x2 = (posX + velX + DRAGON_WIDTH - 1) / TILE_WIDTH;
		y1 = (posY +30 + 1) / TILE_HEIGHT;
		y2 = (posY + height_min - 1) / TILE_HEIGHT;

		if (velX > 0)
		{
			if (tile[y1][x2]->getType() >= 1)
			{
				posX = x2 * TILE_WIDTH;
				posX -= DRAGON_WIDTH;
				velX = 0;
			
			}
			if (tile[y2][x2]->getType() >= 1)
			{
				posX = x2 * TILE_WIDTH;
				posX -= DRAGON_WIDTH;
				velX = 0;
			}
		}
		else
		{
			if (velX < 0)
			{
				if (tile[y1][x1]->getType() >= 1)
				{
					posX = (x1 + 1) * TILE_WIDTH;
					velX = 0;
				}
				if (tile[y2][x1]->getType() >= 1)
				{
					posX = (x1 + 1) * TILE_WIDTH;
					velX = 0;
					
				}
			}
		}

		// theo chieu doc
		int width_min = DRAGON_WIDTH < TILE_WIDTH ? DRAGON_WIDTH : DRAGON_WIDTH * 2 / 3;
		x1 = (posX+30 + 1) / TILE_WIDTH;
		x2 = (posX + width_min - 1) / TILE_WIDTH;
		y1 = (posY + velY + 1) / TILE_HEIGHT;
		y2 = (posY + velY + DRAGON_HEIGHT - 1) / TILE_HEIGHT;

		if (velY > 0)
		{
			if (tile[y2][x1]->getType() >= 1)
			{
				posY = y2 * TILE_WIDTH;
				posY -= DRAGON_HEIGHT;
				velY = 0;
			
			}
			if (tile[y2][x2]->getType() >= 1)
			{
				posY = y2 * TILE_WIDTH;
				posY -= DRAGON_HEIGHT;
				velY = 0;
			}
		}
		else
		{
			if (velY < 0)
			{
				if (tile[y1][x2]->getType() >= 1)
				{
					posY = (y1 + 1) * TILE_HEIGHT;
					velY = 0;
					
				}
				if (tile[y1][x1]->getType() >= 1)
				{
					posY = (y1 + 1) * TILE_HEIGHT;
					velY = 0;
				}
			}
		}
	setPosX(posX + velX);
	setPosY(posY + velY);
	}
}

void Monster::renderDragon(SDL_Rect& camera)
{
	dragon_move();
	SDL_Rect dscrect_dragon = { posX - camera.x,posY - camera.y,DRAGON_WIDTH,DRAGON_HEIGHT };
	SDL_RenderCopyEx(renderer, image_monster[IMAGE_DRAGON_BOSS].getTexture(), cut_image_MONSTER[frame_run / FRAME_MONSTER], &dscrect_dragon, 0, NULL, flip);
	if (!pause)
	{
		frame_run++;
	}
	if (frame_run / FRAME_MONSTER >= frameFirst + total_frame)
	{
		frame_run = frameFirst * FRAME_MONSTER;
	}
}

void Monster::setRise(bool rise)
{
	this->rise = rise;
}

void Monster::setPosX(float posX)
{
	this->posX = posX;
}

void Monster::setPosY(float posY)
{
	this->posY = posY;
}

float Monster::getPosX()
{
	return posX;
}

float Monster::getPosY()
{
	return posY;
}

int Monster::getTypeMonster()
{
	return TYPE_MONSTER;
}

SDL_Rect Monster::getBox()
{
	SDL_Rect box = { posX,posY,MONSTER_WIDTH,MONSTER_HEIGHT };
	return box;
}

SDL_Rect Monster::getBox_Dragon()
{
	SDL_Rect box = { posX,posY,DRAGON_WIDTH,DRAGON_HEIGHT };
	return box;
}