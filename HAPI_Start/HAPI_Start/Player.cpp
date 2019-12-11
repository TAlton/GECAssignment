#include "Player.h"

Player::~Player()
{



}

void Player::Update(float dt) {

	switch (m_nState) {

	case FALLING:
		this->Move(0, 1);
		break;
	case JUMPING:
		this->Move(0, -5);
		break;
	case MOVELEFT:
		this->Move(-dt, 0);
		break;
	case MOVERIGHT:
		this->Move(dt, 0);
		break;
	case IDLE:
		break;
	default:
		break;

	}

}

void Player::Move(int x, int y) {

	m_v2LastPos = m_v2Pos;

	this->m_v2Pos.x += x;
	this->m_v2Pos.y += y;

}

void Player::Move(Vec2 v) {

	m_v2LastPos = m_v2Pos;

	this->m_v2Pos.x += v.x;
	this->m_v2Pos.y += v.y;

}

void Player::Collided(bool b) {

	if (true==b) this->m_v2Pos = this->m_v2LastPos;
	this->m_bCollided = b;

}
