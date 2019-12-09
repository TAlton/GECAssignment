#pragma once
#include "Entity.h"
class Player :
	public Entity {

	enum eState : int { IDLE = 0, MOVELEFT, MOVERIGHT, JUMPING, COLLIDING, SHOOTING, RELOADING };

public:

	Player(Vec2 v, std::string alias, std::shared_ptr<Texture> pTex, std::shared_ptr<Rectangle> pRect) {

		m_v2Pos = v;
		m_strAlias = alias;
		m_pTexture = pTex;
		m_pRectangle = pRect;

	}

	~Player();

	void Update(float dt);

private:

	short m_shHealth{ 0 },
		m_shAmmo{ 10 };
	int m_CurrentState{ IDLE };
};

