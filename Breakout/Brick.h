#pragma once
#include "SDLGameObject.h"

class Brick : public SDLGameObject
{
public:

	Brick(const LoaderParams& pParams);

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void onCollision(SDLGameObject* other) override;
};

