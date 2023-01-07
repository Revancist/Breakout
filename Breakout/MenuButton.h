#pragma once
#include "SDLGameObject.h"

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class MenuButton : public SDLGameObject
{
public:

	MenuButton(const LoaderParams& pParams, void (*callback) ());

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void onCollision(SDLGameObject* other, bool direction) override;

	void (*m_callback) ();

	bool bReleased = false;
};

