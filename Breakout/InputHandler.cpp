#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::pInstance = nullptr;

void InputHandler::initialiseJoysticks()
{
	// Check if joystick subsystem was initialized; if false then initialize
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	// Check if any joysticks are available and open each one
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (SDL_JoystickOpen(i))
			{
				joysticks.push_back(joy);

				// Add the axis
				joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));

				// Initialize joystick buttons
				std::vector<bool> tempButtons;

				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}

				buttonStates.push_back(tempButtons);
			}
			else
			{
				SDL_GetError();
			}
		}

		// Enable event listening for joystick
		SDL_JoystickEventState(SDL_ENABLE);
		bJoysticksInitialised = true;
	}
	else
	{
		bJoysticksInitialised = false;
	}
}

void InputHandler::update()
{
	SDL_Event event;
	keyStates = SDL_GetKeyboardState(0);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::Instance()->clean();
			break;

		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;

		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		default:
			break;
		}
	}
}

void InputHandler::clean()
{
	if (bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(joysticks[i]);
		}
	}
}

int InputHandler::xValue(int joyID, int stick)
{
	if (joystickValues.size() > 0)
	{
		// Check if left stick
		if (stick == 1)
		{
			return joystickValues[joyID].first->getX();
		}
		// Check if right stick
		else if (stick == 2)
		{
			return joystickValues[joyID].second->getX();
		}
	}
	return 0;
}

int InputHandler::yValue(int joyID, int stick)
{
	if (joystickValues.size() > 0)
	{
		// Check if left stick
		if (stick == 1)
		{
			return joystickValues[joyID].first->getX();
		}
		// Check if right stick
		else if (stick == 2)
		{
			return joystickValues[joyID].second->getY();
		}
	}
	return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (keyStates != 0)
	{
		if (keyStates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void InputHandler::onMouseMove(SDL_Event& event)
{
	mousePosition.setX(event.motion.x);
	mousePosition.setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
	int whichOne = event.jaxis.which;

	// Left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			joystickValues[whichOne].first->setX(0);
		}
	}

	// Left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			joystickValues[whichOne].first->setY(0);
		}
	}

	// Right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichOne].second->setX(1);
		}
		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichOne].second->setX(-1);
		}
		else
		{
			joystickValues[whichOne].second->setX(0);
		}
	}

	// Right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichOne].second->setY(1);
		}
		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichOne].second->setY(-1);
		}
		else
		{
			joystickValues[whichOne].second->setY(0);
		}
	}
}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
	int whichOne = event.jaxis.which;

	buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
	int whichOne = event.jaxis.which;

	buttonStates[whichOne][event.jbutton.button] = false;
}
