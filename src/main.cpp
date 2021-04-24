#include "Function.hpp"

int main(int argc, char* argv[])
{
	if (!Init())
		std::cout << "Error INIT" << std::endl;
	else
	{
		if (!loadMedia(tile))
			std::cout << "Error LOAD MEDIA" << std::endl;
		else
		{
			bool quit = false;
			SDL_Event e;
			SDL_Rect camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
			total_AddMonster();
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT || menu.is_selected_quit()) quit = true;
					menu.handleEventMenu(&e);
				}
				SDL_SetRenderDrawColor(renderer, 102, 204, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				render_main(camera);
				SDL_RenderPresent(renderer);
			}
		}
	}
	close();	
	return 0;
}