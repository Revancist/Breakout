#include "Ball.h"
#include "Game.h"

Ball::Ball(const LoaderParams& pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(2);
	m_velocity.setY(0.5);

	m_acceleration.setX(0.01);
	m_acceleration.setY(0.01);

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
		m_acceleration.setX(m_acceleration.getX() * -1);
	}

	if (m_position.getY() <= 0)
	{
		m_velocity.setY(m_velocity.getY() * -1);
		m_acceleration.setY(m_acceleration.getY() * -1);
	}

	// Cap velocity
	if (m_velocity.getX() > 10)
	{
		m_velocity.setX(10);
	}
	else if (m_velocity.getX() < -10)
	{
		m_velocity.setX(-10);
	}

	if (m_velocity.getY() > 10)
	{
		m_velocity.setY(10);
	}
	else if (m_velocity.getY() < -10)
	{
		m_velocity.setY(-10);
	}

	SDLGameObject::update();
}

void Ball::clean()
{
	SDLGameObject::clean();
}

void Ball::onCollision(SDLGameObject* other, bool direction)
{
	if (direction)
	{
		m_velocity.setX(m_velocity.getX() * -1);
		m_acceleration.setX(m_acceleration.getX() * -1);
	}
	else
	{
		m_velocity.setY(m_velocity.getY() * -1);
		m_acceleration.setY(m_acceleration.getY() * -1);
	}
}
