#include "Player.h"

Player::~Player()
{



}

void Player::Update(float dt) {

	switch (m_CurrentState) { //state machine for player states

	case IDLE:
		break;
	case MOVELEFT:
		//move left
		break;
	case MOVERIGHT:
		//move right
		break;
	case JUMPING:
		//jump
		break;
	case COLLIDING:
		//collide
		break;
	case SHOOTING:
		//shoot
		break;
	case RELOADING:
		//reload
		break;
	default:
		break;
		
	}

}
