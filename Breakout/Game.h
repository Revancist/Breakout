#pragma once
#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include <vector>

class Game
{
public:

	bool init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();
	void draw();

	// Accessor for private running variable
	bool getRunning() { return running; }

	// Accessor for stateMachine
	GameStateMachine* getStateMachine() { return pGameStateMachine; }

	// Accessor for renderer
	SDL_Renderer* getRenderer() const { return pRenderer; }

	// Accessors for window width and height
	int getWinWidth() { return winWidth; }
	int getWinHeight() { return winHeight; }

	// Vector list containing created GameObjects
	std::vector<GameObject*> gameObjectList;

	static Game* Instance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new Game();
			return pInstance;
		}

		return pInstance;
	}

private:

	// Constructors
	Game() {}
	~Game() {}

	// Variable containing instance of Game class
	static Game* pInstance;

	// Variable containing the renderer
	SDL_Renderer* pRenderer = nullptr;

	// Variable for the window
	SDL_Window* pWindow = nullptr;

	// Variable for checking if the game is running
	bool running = false;

	// Variable containing the GameStateMachine
	GameStateMachine* pGameStateMachine = nullptr;

	// Variables storing window width and height
	int winHeight = 0;
	int winWidth = 0;
};
#endif