#pragma once
#include "Entity.h"

enum eState : int { IDLE = 0, MOVELEFT, MOVERIGHT, JUMPING, COLLIDING, SHOOTING, RELOADING, FALLING };

class Player :
	public Entity {

public:



	Player(Vec2 v) {

		try {

			m_v2Pos = v;
			this->m_strAlias = "player";
			//m_pRectangle =  std::make_shared<Rectangle>(pTex->GetWidth(), pTex->GetHeight());

		}
		catch (std::overflow_error& e) {
			throw e;
		}
		catch (std::underflow_error & e) {
			throw e;
		}
		catch (std::invalid_argument & e) {
			throw e;
		}
		catch (...) {
			
		}
	}

	~Player();

	void Update(float dt) override;
	void Move(int x, int y);
	void Move(Vec2 v);

	int GetState() const { return this->m_nState; }

	void SetState(int state) { this->m_nState = state; }

private:

	short m_shHealth{ 0 },
		m_shAmmo{ 10 };

	int m_nState{ 0 };

	int m_CurrentState{ IDLE };

};

