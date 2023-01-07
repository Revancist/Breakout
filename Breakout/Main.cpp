#include "SDL.h"
#include "Game.h"

// Fixed frames per second
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;

	// Game initialization
	if (Game::Instance()->init("DX Ball", 100, 100, 1024, 768, false))
	{
		// Initialization success, loop while running the game
		while (Game::Instance()->getRunning())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		// Game initialization faliure
		return -1;
	}

	// Closing the game
	Game::Instance()->clean();
	return 0;
}