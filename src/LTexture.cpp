#include "Function.hpp"

LTexture::LTexture()
{
	this->width = this->height = 0;
	this->image = NULL;
	alpha = 255;

}

LTexture::~LTexture()
{
	free();
	std::cout << "Destroyed image" << std::endl;
}

bool LTexture::loadTextureFromFile(std::string path, Uint8 r, Uint8 g, Uint8 b)
{
	bool kt = true;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		std::cout << "Error: load surface in loadTextureFromFile - " << IMG_GetError() << std::endl;
		kt = false;
	}
	else
	{
		SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, r, g, b));
		image = SDL_CreateTextureFromSurface(renderer, surface);
		if (image == NULL)
		{
			std::cout << "Error: new image" <<SDL_GetError()<< std::endl;
			kt = false;
		}
		else
		{
			width = surface->w;
			height = surface->h;
		}
	}
	SDL_FreeSurface(surface);
	return kt;
}

bool LTexture::loadFromText(std::string text, TTF_Font* type_font, SDL_Color color)
{
	free();
	bool kt = true;
	SDL_Surface* surface = TTF_RenderText_Solid(type_font, text.c_str(), color);
	 image = SDL_CreateTextureFromSurface(renderer, surface);
	if (image == NULL)
	{
		std::cout << "Error: new image - " << SDL_GetError() << std::endl;
		kt = false;
	}
	else
	{
		width = surface->w;
		height = surface->h;
	}
	SDL_FreeSurface(surface);
	return kt;
}

void LTexture::free()
{
	if (image != NULL)
	{
		SDL_DestroyTexture(image);
		image = NULL;
		width = 0;
		height = 0;
	}
}

void LTexture::renderTexture(float x, float y, SDL_Rect* cut)
{
	setAlpha();
	box = { (int)x,(int)y,width,height };
	if (cut != NULL)
	{
		box.w = cut->w;
		box.h = cut->h;
	}
	SDL_RenderCopy(renderer, image, cut, &box);
}

int LTexture::getHeight()
{
	return height;
}

int LTexture::getWidth()
{
	return width;
}

Uint8 LTexture::getAlpha()
{
	return alpha;
}

SDL_Texture* LTexture::getTexture()
{
	return image;
}

SDL_Rect LTexture::getBox()
{
	return box;
}

void LTexture::setAlpha()
{
	SDL_SetTextureAlphaMod(image, alpha);
}

void LTexture::setAlpha(Uint8 alpha)
{
	this->alpha = alpha;
}