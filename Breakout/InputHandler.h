#pragma once
#include "SDL.h"
#include "Vector2D.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new InputHandler();
			return pInstance;
		}
		return pInstance;
	}

	void update();
	void clean();

	// Joystick
	void initialiseJoysticks();
	bool joysticksInitialised() { return bJoysticksInitialised; }
	bool getButtonState(int joyID, int buttonNumber) { return buttonStates[joyID][buttonNumber]; }
	int xValue(int joyID, int stick);
	int yValue(int joyID, int stick);

	// Mouse
	bool getMouseButtonState(int buttonNumber) { return mouseButtonStates[buttonNumber]; }
	Vector2D getMousePosition() { return mousePosition; }

	// Keyboard
	bool isKeyDown(SDL_Scancode key);

private:

	// Constructors
	InputHandler()
	{
		// Initialize mouse buttons
		for (int i = 0; i < 3; i++)
		{
			mouseButtonStates.push_back(false);
		}
	}
	~InputHandler() {}

	// Instance
	static InputHandler* pInstance;

	// List of joysticks
	std::vector<SDL_Joystick*> joysticks;
	bool bJoysticksInitialised = false;

	// Input values
	std::vector<std::pair<Vector2D*, Vector2D*>> joystickValues;
	std::vector<std::vector<bool>> buttonStates;
	std::vector<bool> mouseButtonStates;

	// Keyboard state
	const Uint8* keyStates = nullptr;

	// Mouse motion
	Vector2D mousePosition;

	// Joystick deadzone
	const int joystickDeadZone = 10000;

	// Handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// Handle joystick events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);
};

