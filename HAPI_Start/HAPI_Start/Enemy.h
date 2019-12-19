#pragma once

#include "Player.h"

class Enemy :
	public Player {

public:

	Enemy();
	Enemy(Vec2 v);
	Enemy(short x, short y);
	~Enemy();

private:

	Rectangle* m_pRectAI = nullptr;

};

