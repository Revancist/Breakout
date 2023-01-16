#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:

	SDLGameObject(const LoaderParams& pParams);

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void onCollision(SDLGameObject* other);
	bool getEnabled() override { return enabled; }

	Vector2D& getVelocity() { return m_velocity; }
	Vector2D& getPosition() { return m_position; }
	Vector2D& getAcceleration() { return m_acceleration; }

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width = 0;
	int m_height = 0;

	int m_currentRow = 0;
	int m_currentFrame = 0;

	bool enabled = true;

	std::string m_textureID = "";
};

