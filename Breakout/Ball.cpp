#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include <math.h>

Ball::Ball(const LoaderParams& pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(2);
	m_velocity.setY(0.5);

	m_acceleration.setX(baseAccel);
	m_acceleration.setY(baseAccel);

	m_currentFrame = 0;
}

void Ball::draw()
{
	SDLGameObject::draw();
}

void Ball::update()
{
	// Set correct acceleration direction
	//#TODO: find better way to set acceleration
	if (m_velocity.getX() < 0)
	{
		m_acceleration.setX(-1 * baseAccel);
	}
	else if (m_velocity.getX() == 0)
	{
		m_acceleration.setX(0);
	}
	else
	{
		m_acceleration.setX(baseAccel);
	}

	if (m_velocity.getY() < 0)
	{
		m_acceleration.setY(-1 * baseAccel);
	}
	else
	{
		m_acceleration.setY(baseAccel);
	}

	// Check if on edge of window and bounce
	if (m_position.getX() <= 0 || m_position.getX() >= (Game::Instance()->getWinWidth() - m_width))
	{
		m_velocity.setX(m_velocity.getX() * -1);
	}

	if (m_position.getY() <= 0)
	{
		m_velocity.setY(m_velocity.getY() * -1);
	}

	// Clamp ball's velocity
	m_velocity.setX(SDL_clamp(m_velocity.getX(), -10, 10));
	m_velocity.setY(SDL_clamp(m_velocity.getY(), -10, 10));

	SDLGameObject::update();
}

void Ball::clean()
{
	SDLGameObject::clean();
}

void Ball::onCollision(SDLGameObject* other)
{
	// Check if the other collided object is the player's bar
	//#TODO: Not working correctly, needs fixing
	if (dynamic_cast<Player*>(other) != nullptr)
	{
		// Reverse vertical direction
		m_velocity.setY(m_velocity.getY() * -1);
		m_acceleration.setY(m_acceleration.getY() * -1);

		// Get center position of the player's bar, bar's length and ball's X position
		float playerCenter = other->getPosition().getX() + (other->getWidth() / 2);
		float playerLength = other->getWidth();
		float ballPosX = getPosition().getX();

		m_velocity.setX(((ballPosX - playerCenter) / playerLength * M_PI));
	}
	
	// Check direction of collision and bounce horizontally or vertically
	else if ((getPosition().getX() < other->getPosition().getX()) || ((getPosition().getX() + getWidth()) > other->getPosition().getX() + (other->getWidth())))
	{
		m_velocity.setX(m_velocity.getX() * -1);
	}
	else
	{
		m_velocity.setY(m_velocity.getY() * -1);
	}
}
