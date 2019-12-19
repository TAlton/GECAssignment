#pragma once
#include "Entity.h"

enum eState : int { IDLE = 0, MOVELEFT, MOVERIGHT, JUMPING, COLLIDING, SHOOTING, RELOADING, FALLING };

class Player :
	public Entity {

public:

	Player() {

		m_v2Pos = m_v2LastPos = Vec2(0,0);
		this->m_strAlias = "testPlayer";

	}
	Player(Vec2 v) {

			m_v2Pos = m_v2LastPos = v;
			this->m_strAlias = "testPlayer";

	}

	~Player();

	void Update(long dt) override;
	void UpdateX(long dt);
	void UpdateY(long dt);
	void Move(int x, int y);
	void Move(Vec2 v);
	void Collided(bool b);
	void Fall(long dt);
	void Jump(long dt);
	void Damage(int dmg) { this->m_shHealth -= dmg; }
	bool Shoot(long dt);

	int GetState() const { return this->m_nState; }
	bool GetJump() const { return this->m_bJumping; }
	bool GetDirection() const { return this->m_bDirection; }

	void SetState(int state) { this->m_nState = state; }
	void SetJump(bool b) { this->m_bJumping = b;  }
	
private:

	short m_shHealth{ 100 };

	int m_nState{ 0 },
		m_nCurrentState{ IDLE },
		m_nFrameIterator{ 0 },
		m_nAttackSpeedIterator{ 0 },
		m_nAttackSpeed{ 333 };

	float m_fMaxVelocity{ 2.5f },
		m_fVelocity{ -m_fMaxVelocity };

	bool m_bCollided{ true },
		m_bJumping{ false },
		m_bFalling{ true },
		m_bDead{ false },
		m_bDirection{ LEFT };

	const int m_cnFrameChange{ 300 };

};

