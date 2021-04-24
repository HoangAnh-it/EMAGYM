#include"Function.hpp"

Menu::Menu()
{
	selected_play_game = false;
	selected_tutorial = false;
	selected_quit = false;
	selected_ok = false;
	game_over = false;
	selected_ok = false;
	selected_option = false;
	run = 0;
}

Menu::~Menu()
{

}

void Menu::showMenu()
{
	if (game_over == false)
	{

		if (!is_selected_quit())
		{
			if (!is_selected_play_game() || (is_selected_play_game() && is_selected_tutorial()))
			{
				// BG MENU
				SDL_Rect dscrect_1 = { run,0,SCREEN_WIDTH,SCREEN_HEIGHT };
				SDL_RenderCopy(renderer, image_menu[BG_CLOUDS].getTexture(), NULL, &dscrect_1);
				dscrect_1.x = run + SCREEN_WIDTH;
				SDL_RenderCopy(renderer, image_menu[BG_CLOUDS].getTexture(), NULL, &dscrect_1);
				SDL_Rect dscrect_2 = { -1,-1,SCREEN_WIDTH + 1,SCREEN_HEIGHT + 1 };
				SDL_RenderCopy(renderer, image_menu[BG_].getTexture(), NULL, &dscrect_2);
				SDL_Rect camera_ = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
				run -= 3;
				if (run <= -SCREEN_WIDTH)
				{
					run = 0;
				}

			}

			// Menu chinh
			if (!is_selected_tutorial() && !is_selected_play_game())
			{
				image_menu[PLAY_GAME].renderTexture(SCREEN_WIDTH / 2 - image_menu[PLAY_GAME].getWidth() / 2, SCREEN_HEIGHT - 220, NULL);
				image_menu[TUTORIAL].renderTexture(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT - 220, NULL);
				image_menu[QUIT].renderTexture(SCREEN_WIDTH / 2 - 600, SCREEN_HEIGHT - 220, NULL);
			}
			// huong dan
			if (is_selected_tutorial())
			{
				SDL_Rect tutorial_rect = { SCREEN_WIDTH / 8,SCREEN_HEIGHT / 3,SCREEN_WIDTH * 3 / 4,SCREEN_HEIGHT * 2 / 3 - 110 };
				SDL_RenderCopy(renderer, image_menu[SELECTED_TUTORIAL].getTexture(), NULL, &tutorial_rect);
				image_menu[BACK].renderTexture(SCREEN_WIDTH / 2 - image_menu[BACK].getWidth() / 2, SCREEN_HEIGHT - 100, NULL);		// nut Back
			}
		}
		else
		{
			if (Mix_PlayingMusic() == 1)
			{
			Mix_HaltMusic();
			}
		}
	}
	else    // game over = true
	{
		SDL_Rect gameover_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, image_menu[BG_GAME_OVER].getTexture(), NULL, &gameover_rect);

		SDL_Rect person_rect = { SCREEN_WIDTH / 2 - image_player[HEAD_AND_BODY].getWidth() / 2,SCREEN_HEIGHT / 2 - 10 ,image_player[HEAD_AND_BODY].getWidth(),image_player[HEAD_AND_BODY].getHeight() };
		SDL_RenderCopy(renderer, image_player[HEAD_AND_BODY].getTexture(), NULL, &person_rect);
		SDL_RenderCopy(renderer, image_player[RIGHT_LEG].getTexture(), NULL, &person_rect);
		SDL_RenderCopy(renderer, image_player[LEFT_LEG].getTexture(), NULL, &person_rect);
		person.setEyes(gameover_rect, SCREEN_WIDTH / 2 - image_player[EYES].getWidth() / 2, SCREEN_HEIGHT / 2 - 10);

		image_menu[YES].renderTexture(SCREEN_WIDTH / 2 - image_menu[YES].getWidth()*2, SCREEN_HEIGHT / 2, NULL);
		image_menu[NO].renderTexture(SCREEN_WIDTH /2 + image_menu[YES].getWidth(), SCREEN_HEIGHT / 2, NULL);
	}
}

// option
void Menu::renderOption()
{
	SDL_Rect option = { SCREEN_WIDTH - 50 ,0,50,50 };
	SDL_RenderCopy(renderer, image_menu[OPTION].getTexture(), NULL, &option);
	if (selected_option && is_selected_play_game())
	{
		image_menu[OPTION_RESTART].renderTexture(SCREEN_WIDTH - image_menu[OPTION_TUTORIAL].getWidth(), 50, NULL);
		image_menu[OPTION_PAUSE].renderTexture(SCREEN_WIDTH - image_menu[OPTION_TUTORIAL].getWidth(), 76, NULL);
		image_menu[OPTION_TUTORIAL].renderTexture(SCREEN_WIDTH - image_menu[OPTION_TUTORIAL].getWidth(), 102, NULL);
		image_menu[OPTION_EXIT].renderTexture(SCREEN_WIDTH - image_menu[OPTION_TUTORIAL].getWidth(), 128, NULL);
	}
}

void Menu::renderSurvival()
{
	// menu survival
	if (is_selected_play_game() && person.is_started_surviving() && !is_selected_ok())
	{
		SDL_Rect ok_rect = { SCREEN_WIDTH / 2 - image_menu[SURVIVAL].getWidth() / 2,SCREEN_HEIGHT / 2 - image_menu[SURVIVAL].getHeight() / 2,image_menu[SURVIVAL].getWidth(),image_menu[SURVIVAL].getHeight() };
		SDL_RenderCopy(renderer, image_menu[SURVIVAL].getTexture(), NULL, &ok_rect);
		// nut Ok
		image_menu[OK].renderTexture(SCREEN_WIDTH / 2 - image_menu[OK].getWidth() / 2, SCREEN_HEIGHT / 2 + 60, NULL);
	}
}

void Menu::renderCongratulations()
{
	if (person.isWon()   )
	{
		SDL_Rect dscrect_congratulations = { SCREEN_WIDTH / 2 - image_menu[WIN].getWidth() / 2 + 100,20,image_menu[WIN].getWidth() - 200,image_menu[WIN].getHeight() };
		SDL_RenderCopy(renderer, image_menu[WIN].getTexture(), NULL, &dscrect_congratulations);
		// nut Ok
		image_menu[OK].renderTexture(SCREEN_WIDTH / 2 - image_menu[OK].getWidth() / 2, SCREEN_HEIGHT / 2 , NULL);
	}
}

void Menu::renderTheNumberOfHeartAndCoin()
{
	SDL_Rect _rect = { 50,32,28,28 };
	SDL_RenderCopy(renderer, image_tile[HEART].getTexture(), cut_image_heart[0], &_rect);
	_rect.y = 0;
	SDL_RenderCopy(renderer, image_tile[COIN].getTexture(), cut_image_coin[0], &_rect);
	std::stringstream os;
	os.str("");
	os << person.getCoin() << "/" << total_coin;
	if (theNumberOfHeart.loadFromText(os.str().c_str(), temp_font, { 0,255,0 }))
	{
		theNumberOfHeart.renderTexture(86, 0, NULL);
	}
	os.str("");
	os << person.getHeart();
	if (theNumberOfHeart.loadFromText(os.str().c_str(), temp_font, { 0,255,0 }))
	{
		theNumberOfHeart.renderTexture(86, 32, NULL);
	}
}

void Menu::handleEventMenu(SDL_Event* e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	// di chuyen chuot
		if (!game_over)
		{
			// menu chinh
			if (!is_selected_play_game() && !is_selected_tutorial())
			{
				if (checkMouseMotion(x, y, image_menu[PLAY_GAME].getBox()))
				{
					image_menu[PLAY_GAME].loadFromText("PLAY GAME", font, { 0, 255, 0 });
					if (!play_music_1)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_1 = true;
					}
				}
				else
				{
					image_menu[PLAY_GAME].loadFromText("PLAY GAME", font, { 0,0,0 });
					play_music_1 = false;
				}

				if (checkMouseMotion(x, y, image_menu[TUTORIAL].getBox()))
				{
					image_menu[TUTORIAL].loadFromText("TUTORIAL", font, { 0, 255, 0 });
					if (!play_music_2)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_2 = true;
					}
				}
				else
				{
					image_menu[TUTORIAL].loadFromText("TUTORIAL", font, { 0,0,0 });
					play_music_2 = false;
				}

				if (checkMouseMotion(x, y, image_menu[QUIT].getBox()))
				{
					image_menu[QUIT].loadFromText("QUIT", font, { 255,0,0 });
					if (!play_music_3)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_3 = true;
					}
				}
				else
				{
					image_menu[QUIT].loadFromText("QUIT", font, { 0,0,0 });
					play_music_3 = false;
				}
			}
			// huong dan
			if (is_selected_tutorial())
			{
				if (checkMouseMotion(x, y, image_menu[BACK].getBox()))
				{
					image_menu[BACK].loadFromText("BACK", font, { 0,255,0 });
					if (!play_music_1)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_1 = true;
					}
				}
				else
				{
					image_menu[BACK].loadFromText("BACK", font, { 0,0,0 });
					play_music_1 = false;
				}
			}
			// nut OK trong survival va win
			if (is_selected_play_game() && ((person.is_started_surviving() && !is_selected_ok()) || person.isWon()))
			{
				if (checkMouseMotion(x, y, image_menu[OK].getBox()))
				{
					image_menu[OK].loadFromText("OK", font, { 0,255,0 });
					if (!play_music_1  )
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_1 = true;
					}
				}
				else
				{
					image_menu[OK].loadFromText("OK", font, { 255,0,0 });
					play_music_1 = false;
				}
			}
			// option
			if (is_selected_play_game() && is_selected_option() )
			{
				if (!checkMouseMotion(x, y, { SCREEN_WIDTH - image_menu[OPTION_RESTART].getWidth(),0,image_menu[OPTION_RESTART].getWidth(),image_menu[OPTION_EXIT].getBox().y + image_menu[OPTION_EXIT].getHeight() }))
				{
					selected_option = false;
				}
				if (checkMouseMotion(x, y, image_menu[OPTION_RESTART].getBox()))
				{
					image_menu[OPTION_RESTART].loadFromText("Restart (R)", temp_font, { 0,255,0 });
					if (!play_music_1 && selected_option )
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_1 = true;
					}
				}
				else
				{
					image_menu[OPTION_RESTART].loadFromText("Restart (R)", temp_font, { 200,0,0 });
					play_music_1 = false;
				}

				if (checkMouseMotion(x, y, image_menu[OPTION_PAUSE].getBox()))
				{
					image_menu[OPTION_PAUSE].loadFromText("Pause (P)", temp_font, { 0,255,0 });
					if (!play_music_2 && selected_option)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_2 = true;
					}
				}
				else
				{
					image_menu[OPTION_PAUSE].loadFromText("Pause (P)", temp_font, { 200,0,0 });
					play_music_2 = false;
				}

				if (checkMouseMotion(x, y, image_menu[OPTION_TUTORIAL].getBox()))
				{
					image_menu[OPTION_TUTORIAL].loadFromText("Tutorial(T)", temp_font, { 0,255,0 });
					if (!play_music_3 && selected_option)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_3 = true;
					}
				}
				else
				{
					image_menu[OPTION_TUTORIAL].loadFromText("Tutorial(T)", temp_font, { 200,0,0 });
					play_music_3 = false;
				}
				if (checkMouseMotion(x, y, image_menu[OPTION_EXIT].getBox()))
				{
					image_menu[OPTION_EXIT].loadFromText("Exit (ESC)", temp_font, { 0,255,0 });
					if (!play_music_4 && selected_option)
					{
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
						play_music_4 = true;
					}
				}
				else
				{
					image_menu[OPTION_EXIT].loadFromText("Exit (ESC)", temp_font, { 200,0,0 });
					play_music_4 = false;
				}
				
			}
		}
		else
		{
			// game over
			if (checkMouseMotion(x, y, image_menu[YES].getBox()))
			{
				image_menu[YES].loadFromText("YES", font, { 0,255,0 });
				if (!play_music_1)
				{
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
					play_music_1 = true;
				}
			}
			else
			{
				image_menu[YES].loadFromText("YES", font, { 0,0,0 });
				play_music_1 = false;
			}

			if (checkMouseMotion(x, y, image_menu[NO].getBox()))
			{
				image_menu[NO].loadFromText("NO", font, { 255,0,0 });
				if (!play_music_2)
				{
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_MOTION], 0);
					play_music_2 = true;
				}
			}
			else
			{
				image_menu[NO].loadFromText("NO", font, { 0,0,0 });
				play_music_2 = false;
			}
		}

// AN CHUOT TRAI
	 if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
	{
		if (!is_game_over())
		{
			if (!is_selected_play_game() && !is_selected_tutorial() && !is_selected_quit())
			{
				if (checkMouseMotion(x, y, image_menu[PLAY_GAME].getBox()))
				{
					resetValue(); //
					selected_play_game = true;
					selected_tutorial = false;
					selected_quit = false;
					selected_option = false;
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
				}
				else if (checkMouseMotion(x, y, image_menu[TUTORIAL].getBox()))
				{
					selected_play_game = false;
					selected_tutorial = true;
					selected_quit = false;
					selected_option = false;
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
				}
				else if (checkMouseMotion(x, y, image_menu[QUIT].getBox()))
				{
					selected_quit = true;
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
				}
			}

			if (is_selected_play_game())
			{
				if (checkMouseMotion(x, y, { SCREEN_WIDTH - 50,0,50,50 }))
				{
					if (selected_option) selected_option = false;
					else selected_option = true;
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
				}
				if (selected_option)
				{
					if (checkMouseMotion(x, y, image_menu[OPTION_RESTART].getBox()))
					{
						resetValue();
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
						selected_option = false;
					}
					else if (checkMouseMotion(x, y, image_menu[OPTION_TUTORIAL].getBox()))
					{
						selected_tutorial = true;
						selected_option = false;
						pause = true;
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
					}
					else if (checkMouseMotion(x, y, image_menu[OPTION_EXIT].getBox()))
					{
						pause = false;
						selected_play_game = false;
						selected_tutorial = false;
						selected_quit = false;
						selected_option = false;
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
					}
					else if (checkMouseMotion(x, y, image_menu[OPTION_PAUSE].getBox()))
					{
						if(!pause) pause=true;
						else pause=false;
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
						pauseOrUnpauseMusic();
					}
				}
				// nut Ok
				if (person.is_started_surviving() && !is_selected_ok())
				{
					if (checkMouseMotion(x, y, image_menu[OK].getBox()))
					{
						selected_ok = true;
						if (pause) pause = false;
						is_start_count_down = true;
						tile[33][113]->setType(99);
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
					}
				}
				else if (person.isWon())
				{
					if (checkMouseMotion(x, y, image_menu[OK].getBox()))
					{
						selected_ok = true;
						pause = false;
						selected_play_game = false;
						selected_tutorial = false;
						selected_quit = false;
						selected_option = false;
						Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
					}
				}
			}
			// nut BACK
			if (is_selected_tutorial())
			{
				if (checkMouseMotion(x, y, image_menu[BACK].getBox()))
				{
					Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
					if (is_selected_play_game())
					{
						selected_tutorial = false;
						pause = false;
					}
					else
					{
						selected_play_game = false;
						selected_tutorial = false;
						selected_quit = false;
						selected_option = false;
					}
				}
			}

		}
		else
		{
		if (checkMouseMotion(x, y, image_menu[YES].getBox()))
		{
			resetValue();
			selected_play_game = true;
			Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
		}
		else if (checkMouseMotion(x, y, image_menu[NO].getBox()))
		{
			resetValue();
			selected_play_game = false;
			pause = false;
			selected_play_game = false;
			selected_tutorial = false;
			selected_quit = false;
			selected_option = false;
			Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
		}
		}
	}
	else if (e->type == SDL_KEYDOWN)
	{
	switch (e->key.keysym.sym)
	{
	case SDLK_p:
		if (is_selected_play_game())
		{
			if (!pause)
				pause = true;
			else pause = false;
		Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
		}
		pauseOrUnpauseMusic();
		break;
	case SDLK_r:
		if (is_selected_play_game())
		{
			resetValue();
			selected_option = false;
			Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
		}
		break;
	case SDLK_t:
		if (is_selected_play_game())
		{
			pause = true;
		}
		selected_tutorial = true;
		selected_option = false;
		Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
		break;
	case SDLK_ESCAPE:
		pause = false;
		selected_play_game = false;
		selected_tutorial = false;
		selected_quit = false;
		selected_option = false;
		Mix_PlayChannel(-1, sound_effects[MUSIC_MOUSE_SELECTED], 0);
		break;
	default:break;
	}
	}
}


bool Menu::is_selected_play_game()
{
	return selected_play_game;
}

bool Menu::is_selected_tutorial()
{
	return selected_tutorial;
}

bool Menu::is_selected_quit()
{
	return selected_quit;
}

bool Menu::is_game_over()
{
	return game_over;
}

bool Menu::is_selected_option()
{
	return selected_option;
}

bool Menu::is_selected_ok()
{
	return selected_ok;
}

void Menu::setGameOver(bool game_over)
{
	this->game_over = game_over;	
}

void Menu::set_is_selected_play_game(bool selected_play_game)
{
	this->selected_play_game = selected_play_game;
}

void Menu::set_is_selected_ok(bool ok)
{
	this->selected_ok = ok;
}