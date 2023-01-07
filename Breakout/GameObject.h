#pragma once
#include "SDL.h"
#include "LoaderParams.h"

class GameObject
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual bool getEnabled() = 0;

	virtual ~GameObject() {}

protected:

	// Constructors
	GameObject (const LoaderParams& pParams) {}
};