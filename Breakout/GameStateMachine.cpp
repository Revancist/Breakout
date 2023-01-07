#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState)
{
	// If any game states are initialized
	if (!m_gameStates.empty())
	{
		// If last game state is same as new game state
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			// Do nothing
			return;
		}

		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}

	// Push back our new state
	m_gameStates.push_back(pState);

	// Initialize new state
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	// Check if GameStates is empty
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}
