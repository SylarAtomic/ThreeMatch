#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{

	//SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_Window* window = SDL_CreateWindow("Match Three", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 720, SDL_WINDOW_SHOWN);
	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	//SDL_RenderClear(renderer);

	//SDL_RenderPresent(renderer);

	//SDL_Delay(3000);

	// limite the FPS
	const int targetFrameRate = 60;
	const int frameDelay = 1000 / targetFrameRate;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Match Three", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);

	while (game->isRunning()) {

		frameStart = SDL_GetTicks();
		
		// game functions
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		// Check if we need to delay before the next frame starts
		// My PC was running at 1000+ frames per second.
		// Can also use this for a delta time since we know each frame is 1/60s
		// Sadly, this will only be on a high frame rate pc. Would optimise this if we had more time
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	// clean up the game when no longer running
	game->clean();

	return 0;
}