#pragma once
#include "Entity.h"
class Player :
	public Entity {

	enum eState : int { IDLE = 0, MOVELEFT, MOVERIGHT, JUMPING, COLLIDING, SHOOTING, RELOADING };

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

private:

	short m_shHealth{ 0 },
		m_shAmmo{ 10 };
	int m_CurrentState{ IDLE };

};

