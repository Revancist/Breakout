#pragma once
#include "SDLGameObject.h"

class Ball : public SDLGameObject
{
public:

	Ball(const LoaderParams& pParams);

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void onCollision(SDLGameObject* other) override;

private:

	int speedMult = 1;
};

