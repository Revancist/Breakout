#include "Player.h"
#include "InputHandler.h"
#include "Game.h"

Player::Player(const LoaderParams& pParams) : SDLGameObject(pParams)
{
	m_currentFrame = 0;
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	// Set player velocity and get mouse position
	m_velocity.setX(0);
	int xTarget = InputHandler::Instance()->getMousePosition().getX();

	// Have player slowly follow the mouse
	m_velocity.setX((xTarget - m_position.getX()) / 25);

	// Stop sprite at the edge of the window
	if (m_position.getX() > (Game::Instance()->getWinWidth() - m_width))
	{
		m_position.setX(Game::Instance()->getWinWidth() - m_width);
	}

	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::onCollision(SDLGameObject* other)
{
}
