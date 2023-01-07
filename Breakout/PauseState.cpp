#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "MenuState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TextureManager::Instance()->load("assets/ResumeButton.png", "resumebutton", Game::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("assets/MainMenuButton.png", "menubutton", Game::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* buttonResume = new MenuButton(LoaderParams(200, 100, 200, 80, "resumebutton"), s_resumePlay);
	GameObject* buttonMenu = new MenuButton(LoaderParams(200, 300, 200, 80, "menubutton"), s_pauseToMain);

	m_gameObjects.push_back(buttonResume);
	m_gameObjects.push_back(buttonMenu);

	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}

	m_gameObjects.clear();

	TextureManager::Instance()->clearFromTextureMap("resumebutton");
	TextureManager::Instance()->clearFromTextureMap("menubutton");

	return true;
}

void PauseState::s_pauseToMain()
{
	Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
	Game::Instance()->getStateMachine()->popState();
}
