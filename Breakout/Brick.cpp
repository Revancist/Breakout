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

void Brick::onCollision(SDLGameObject* other)
{
	// Disable the brick
	enabled = false;
}
