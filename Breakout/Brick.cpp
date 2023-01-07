#include "Brick.h"
#include "Game.h"

Brick::Brick(const LoaderParams& pParams) : SDLGameObject(pParams)
{
	m_currentFrame = 0;
}

void Brick::draw()
{
	SDLGameObject::draw();
}

void Brick::update()
{
}

void Brick::clean()
{
	SDLGameObject::clean();
}

void Brick::onCollision(SDLGameObject* other, bool direction)
{
	enabled = false;/*
	m_position.setX(Game::Instance()->getWinWidth() + 1);
	m_position.setY(Game::Instance()->getWinHeight() + 1);
	m_width = 0;
	m_height = 0;*/
}
