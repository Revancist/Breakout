#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:

	// Add new state without removing the previous states
	void pushState(GameState* pState);
	// Remove previous state before adding a new state
	void changeState(GameState* pState);
	// Remove current state
	void popState();

	void update();
	void render();

private:

	std::vector<GameState*> m_gameStates;
};

