#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	// Load texture for the play button
	if (!TextureManager::Instance()->load("assets/PlayButton.png", "playbutton", Game::Instance()->getRenderer()))
	{
		return false;
	}

	// Load texture for the exit button
	if (!TextureManager::Instance()->load("assets/ExitButton.png", "exitbutton", Game::Instance()->getRenderer()))
	{
		return false;
	}

	// Create game objects from textures
	GameObject* buttonPlay = new MenuButton(LoaderParams(Game::Instance()->getWinWidth() / 2 - 200, Game::Instance()->getWinHeight() / 2 - 100, 400, 100, "playbutton"), s_menuToPlay);
	GameObject* buttonExit = new MenuButton(LoaderParams(Game::Instance()->getWinWidth() / 2 - 200, Game::Instance()->getWinHeight() / 2 + 100, 400, 100, "exitbutton"), s_exitFromMenu);

	// Add objects to the gameObject list
	m_gameObjects.push_back(buttonPlay);
	m_gameObjects.push_back(buttonExit);

	return true;
}

bool MenuState::onExit()
{
	// Clean all drawn objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}

	m_gameObjects.clear();

	// Clear buttons from texture map
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");

	return true;
}

void MenuState::s_menuToPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	Game::Instance()->clean();
}
