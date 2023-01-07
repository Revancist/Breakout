#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::pInstance = nullptr;

bool Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Flag for fullscreen check
		int flag = 0;

		if (fullscreen)
		{
			flag = SDL_WINDOW_FULLSCREEN;
		}

		// Initialize the window
		pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flag);
		if (pWindow != 0)
		{
			// Store window width and height
			winHeight = height;
			winWidth = width;

			// Initialize the renderer
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
			if (pRenderer != 0)
			{
				SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
			}
			else
			{
				// Renderer initialization failed
				return false;
			}
		}
		else
		{
			// Window initialization failed
			return false;
		}
	}
	else
	{
		// SDL initialization failed
		return false;
	}

	// Initialization successfull, game is running, start the main loop
	running = true;

	// Initialize GameStateMachine and set state to main menu
	pGameStateMachine = new GameStateMachine();
	pGameStateMachine->changeState(new MenuState());

	return true;
}

void Game::render()
{
	// Clear the renderer to the draw color
	SDL_RenderClear(pRenderer);
	pGameStateMachine->render();

	// Loop through GameObject list and draw objects
	for (std::vector<GameObject*>::size_type i = 0; i != gameObjectList.size(); i++)
	{
		gameObjectList[i]->draw();
	}

	// Draw to the screen
	SDL_RenderPresent(pRenderer);
}

void Game::update()
{
	pGameStateMachine->update();

	// Loop through GameObject list and draw objects
	for (std::vector<GameObject*>::size_type i = 0; i != gameObjectList.size(); i++)
	{
		gameObjectList[i]->update();
	}
}

void Game::draw()
{
	for (std::vector<GameObject*>::size_type i = 0; i != gameObjectList.size(); i++)
	{
		gameObjectList[i]->draw();
	}
}

void Game::clean()
{
	// Clear input handler
	InputHandler::Instance()->clean();

	// Destroy SDL
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();

	// Game is no longer running
	running = false;
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		pGameStateMachine->changeState(new PlayState());
	}
}