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
	// Get mouse position and clamp it so the bar dosen't go over the screen
	float MousePos = InputHandler::Instance()->getMousePosition().getX() - (m_width / 2);

	MousePos = SDL_clamp(MousePos, 0, Game::Instance()->getWinWidth() - m_width);

	// Set player position to mouse position
	m_position.setX(MousePos);

	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::onCollision(SDLGameObject* other)
{
}
