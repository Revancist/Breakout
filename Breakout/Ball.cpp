#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include <math.h>

Ball::Ball(const LoaderParams& pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(0);
	m_velocity.setY(2);

	m_currentFrame = 0;
}

void Ball::draw()
{
	SDLGameObject::draw();
}

void Ball::update()
{
	// Check if on edge of window and bounce
	if (m_position.getX() <= 0 || m_position.getX() >= (Game::Instance()->getWinWidth() - m_width))
	{
		m_velocity.setX(m_velocity.getX() * -1);
	}

	if (m_position.getY() <= 0)
	{
		m_velocity.setY(m_velocity.getY() * -1);
	}

	SDLGameObject::update();
}

void Ball::clean()
{
	SDLGameObject::clean();
}

void Ball::onCollision(SDLGameObject* other)
{
	// Check if the other collided object is the player's bar
	if (dynamic_cast<Player*>(other) != nullptr)
	{
		m_velocity.normalize();

		// Get center position of the player's bar, bar's length and ball's X position
		float playerCenter = other->getPosition().getX() + (other->getWidth() / 2);
		float playerLength = other->getWidth();
		float ballPosX = getPosition().getX();

		// Calculate and set ball's new direction
		m_velocity.setX(((ballPosX - playerCenter) / playerLength * M_PI));

		// Incriment speed multiplier after bounce
		if (speedMult < 10)
		{
			speedMult++;
		}

		// Increase ball's speed
		m_velocity *= speedMult;

		// Reverse vertical direction
		m_velocity.setY(m_velocity.getY() * -1);

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
