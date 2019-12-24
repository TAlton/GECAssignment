#pragma once
#include "Entity.h"

enum eState : int { IDLE = 0, MOVELEFT, MOVERIGHT, JUMPING, COLLIDING, SHOOTING, RELOADING, FALLING };

class Player :
	public Entity {

public:

	Player() {

		this->m_nHealth = 100;
		this->m_v2Pos = this->m_v2LastPos = Vec2(0,0);
		this->m_strAlias = "testPlayer";
		this->m_ESide = PLAYER;

	}
	
	Player(Vec2 v) {

		this->m_nHealth = 100;
		this->m_v2Pos = this->m_v2LastPos = v;
		this->m_strAlias = "testPlayer";
		this->m_ESide = PLAYER;

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
	void Damage(int dmg) { this->m_nHealth -= dmg; }
	bool Shoot(long dt);
	bool IsDead() const { return m_bDead; }

	int GetState() const { return this->m_nState; }
	bool GetJump() const { return this->m_bJumping; }
	bool GetDirection() const { return this->m_bDirection; }
	bool GetCollided() const { return this->m_bCollided; }
	bool GetFalling() const { return this->m_bFalling; }
	bool CanJump() const {

		if (m_bCollided && m_bFalling) return true;

		return false;

	}

	void SetState(int state) { this->m_nState = state; }
	void SetJump(bool b) { this->m_bJumping = b;  }
	/*
	
	@Param b : false = dead, true = alive

	*/
	void SetAliveState(bool b) { this->m_bDead = !b; }

	bool m_bCanJump = false;
	
protected:

	int m_nState{ 0 },
		m_nCurrentState{ IDLE },
		m_nFrameIterator{ 0 },
		m_nAttackSpeedIterator{ 0 };
	const int m_cnAttackSpeed{ 333 };

	float m_fMaxVelocity{ 2.5f },
		m_fVelocity{ -m_fMaxVelocity };

	bool m_bCollided{ true },
		m_bJumping{ false },
		m_bFalling{ true },
		m_bDead{ false },
		m_bDirection{ LEFT };

	const int m_cnFrameChange{ 300 };

};

