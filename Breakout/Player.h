#pragma once
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:

	Player(const LoaderParams& pParams);

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void onCollision(SDLGameObject* other, bool direction) override;
};

