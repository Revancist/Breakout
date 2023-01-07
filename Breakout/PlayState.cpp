#include "PlayState.h"
#include "InputHandler.h"
#include "Game.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "GameOverState.h"

const std::string PlayState::s_menuID = "PLAY";

void PlayState::update()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
		return;
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	// Since only the ball is moving, only the ball collision is important
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (pBall == m_gameObjects[i] || m_gameObjects[i]->getEnabled() == false)
		{
			continue;
		}

		checkCollision(pBall, dynamic_cast<SDLGameObject*>(m_gameObjects[i]));
	}	

	if (pBall->getPosition().getY() >= Game::Instance()->getWinHeight())
	{
		Game::Instance()->getStateMachine()->pushState(new GameOverState());
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i]->getEnabled())
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool PlayState::onEnter()
{
	if (!TextureManager::Instance()->load("assets/PlayButton.png", "playerbar", Game::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("assets/MainMenuButton.png", "ball", Game::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("assets/RestartButton.png", "brick", Game::Instance()->getRenderer()))
	{
		return false;
	}

	pPlayer = new Player(LoaderParams(Game::Instance()->getWinWidth() / 2, Game::Instance()->getWinHeight() - 20, 256, 10, "playerbar"));
	pBall = new Ball(LoaderParams(Game::Instance()->getWinWidth() / 2, Game::Instance()->getWinHeight() / 2, 10, 10, "ball"));

	m_gameObjects.push_back(pPlayer);
	m_gameObjects.push_back(pBall);

	//#TODO: make another for loop for number of rows

	for (int i = 0; i < Game::Instance()->getWinWidth() / 100; i++)
	{
		m_gameObjects.push_back(new Brick(LoaderParams(i * 100, 0, 100, 20, "brick")));
	}

	for (int i = 0; i < Game::Instance()->getWinWidth() / 100; i++)
	{
		m_gameObjects.push_back(new Brick(LoaderParams(i * 100, 20, 100, 20, "brick")));
	}

	for (int i = 0; i < Game::Instance()->getWinWidth() / 100; i++)
	{
		m_gameObjects.push_back(new Brick(LoaderParams(i * 100, 40, 100, 20, "brick")));
	}

	return true;
}

bool PlayState::onExit()
{
	// This clears the pointers, the actual object is in m_gameObjects which is deleted in the for loop below
	pPlayer = nullptr;
	pBall = nullptr;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();

	TextureManager::Instance()->clearFromTextureMap("player");
	TextureManager::Instance()->clearFromTextureMap("ball");

	return true;
}

bool PlayState::checkCollision(SDLGameObject* pA, SDLGameObject* pB)
{
	
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate sides of rectangle A
	leftA = pA->getPosition().getX();
	rightA = pA->getPosition().getX() + pA->getWidth();
	topA = pA->getPosition().getY();
	bottomA = pA->getPosition().getY() + pA->getHeight();

	// Calculate sides of rectangle B
	leftB = pB->getPosition().getX();
	rightB = pB->getPosition().getX() + pB->getWidth();
	topB = pB->getPosition().getY();
	bottomB = pB->getPosition().getY() + pB->getHeight();

	// Check if A and B are collided
	if ((leftB <= rightA) && (rightB >= leftA) && (bottomB >= topA) && (topB <= bottomA))
	{
		// Direction of collision: True = horizontal, False = vertical
		bool direction = false;
		
		if ((pA->getPosition().getX() < pB->getPosition().getX()) || ((pA->getPosition().getX() + pA->getWidth()) > pB->getPosition().getX() + (pB->getWidth())))
		{
			direction = true;
		}
		
		//#TODO: move above logic into onCollision().

		//int direction = (pA->getPosition().getX() + pA->getWidth() / 2) - (pB->getPosition().getX() + pB->getWidth() / 2)

		pA->onCollision(pB, direction);
		pB->onCollision(pA, direction);

		return true;
	}

	return false;
}
