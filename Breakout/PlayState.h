#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>

class GameObject;

class PlayState : public GameState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

	bool checkCollision(SDLGameObject* player, SDLGameObject* ball);

private:

	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;

	// Number of brick rows to create.
	int rowNum = 3;

	Player* pPlayer = nullptr;
	Ball* pBall = nullptr;
};

