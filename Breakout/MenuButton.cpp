#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams& pParams, void(*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
	// Start at frame 0
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	// Use the base class drawing
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D pMousePos = InputHandler::Instance()->getMousePosition();

	if (pMousePos.getX() < (m_position.getX() + m_width)
		&& pMousePos.getX() > m_position.getX()
		&& pMousePos.getY() < (m_position.getY() + m_height)
		&& pMousePos.getY() > m_position.getY())
	{
		m_currentFrame = MOUSE_OVER;

		if (InputHandler::Instance()->getMouseButtonState(LEFT) && bReleased)
		{
			SDLGameObject::m_currentFrame = CLICKED;

			// Call our callback function
			m_callback();
			bReleased = false;
		}
	}
	else if (!InputHandler::Instance()->getMouseButtonState(LEFT))
	{
		bReleased = true;
		m_currentFrame = MOUSE_OUT;
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::onCollision(SDLGameObject* other, bool direction)
{
}
