#pragma once
#include<SDL.h>
#include<string>

class LTexture
{
private:
	int width, height;
	SDL_Rect box;
	SDL_Texture* image;
	Uint8 alpha;
public:
	LTexture();
	~LTexture();
	bool loadTextureFromFile(std::string path, Uint8 r, Uint8 g, Uint8 b);
	bool loadFromText(std::string text, TTF_Font* type_font, SDL_Color color);
	void free();
	void renderTexture(float x, float y, SDL_Rect* cut);
	void setAlpha();
	void setAlpha(Uint8 alpha);
	int getHeight();
	int getWidth();
	SDL_Rect getBox();
	Uint8 getAlpha();
	SDL_Texture* getTexture();
};