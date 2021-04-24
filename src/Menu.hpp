#pragma once
#include<SDL.h>

class Menu
{
private:
	bool selected_play_game;
	bool selected_tutorial;
	bool selected_quit;
	bool selected_option;
	bool selected_ok;
	bool game_over;
	int run;
public:
	Menu();
	~Menu();
	void handleEventMenu(SDL_Event* e);
	void renderTheNumberOfHeartAndCoin();
	void showMenu();
	void renderOption();
	void renderSurvival();
	void renderCongratulations();
	
	void setGameOver(bool game_over);
	void set_is_selected_play_game(bool selected_play_game);
	void set_is_selected_ok(bool ok);
	bool is_selected_play_game();
	bool is_selected_tutorial();
	bool is_selected_quit();
	bool is_game_over();
	bool is_selected_option();
	bool is_selected_ok();
};