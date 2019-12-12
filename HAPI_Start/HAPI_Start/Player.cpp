#include "Player.h"

Player::~Player()
{



}

void Player::Update(float dt) {

	switch (m_nState) {

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

	if (true == m_bJumping && true == m_bCollided) {

		Jump(dt);

	}

	HAPI.RenderText(0, 0, HAPI_TColour::GREEN, std::to_string(this->GetPosition().x));
	HAPI.RenderText(0, 10, HAPI_TColour::GREEN, std::to_string(this->GetPosition().y));

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

	if (true == b) {

		this->m_v2Pos = this->m_v2LastPos;

		m_fVelocity = -3.0f;
		m_bJumping = false;
		m_bFalling = true;

	}

	m_bFalling = true;
	this->m_bCollided = b;

}

void Player::Jump(float dt) {

	m_bFalling = false;

	this->SetPosition(m_v2Pos.x,
		static_cast<int>(PHYSICS->Lerp(this->m_v2Pos.y,
			this->m_v2Pos.y + m_fVelocity, 1.0f)));

	if (m_fVelocity < 0) {
		m_fVelocity += dt / 100;
	}
	else {
		m_bJumping = false;
		m_bFalling = true;
	}

}

void Player::Fall(float dt) {

	if (m_fVelocity < m_fMaxVelocity) {
		m_fVelocity -= dt / 100;
	}

	this->SetPosition(m_v2Pos.x,
		static_cast<int>(PHYSICS->Lerp(this->m_v2Pos.y,
			this->m_v2Pos.y - m_fVelocity, 1.0f)));

}
