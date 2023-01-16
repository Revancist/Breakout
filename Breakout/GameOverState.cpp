#include "GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	if (!TextureManager::Instance()->load("assets/MainMenuButton.png", "menubutton", Game::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("assets/RestartButton.png", "restartbutton", Game::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* buttonMenu = new MenuButton( LoaderParams(Game::Instance()->getWinWidth() / 2 - 100, Game::Instance()->getWinHeight() / 2 - 80, 200, 80, "menubutton"), s_gameOverToMain);
	GameObject* buttonRestart = new MenuButton( LoaderParams(Game::Instance()->getWinWidth() / 2 - 100, Game::Instance()->getWinHeight() / 2 + 80, 200, 80, "restartbutton"), s_restartPlay);

	m_gameObjects.push_back(buttonMenu);
	m_gameObjects.push_back(buttonRestart);

	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}

	m_gameObjects.clear();

	TextureManager::Instance()->clearFromTextureMap("menubutton");
	TextureManager::Instance()->clearFromTextureMap("restartbutton");

	return true;
}

void GameOverState::s_gameOverToMain()
{
	Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}
