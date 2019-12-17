#include "Player.h"

Player::~Player()
{



}

void Player::Update(long dt)
{

	m_nAttackSpeedIterator += dt;

}

void Player::UpdateX(long dt) {

	Update(dt);

	switch (m_nState) {

	case MOVELEFT:
		this->Move(-dt, 0);
		m_nFrameIterator += dt;
		if (m_nFrameIterator >= 300) { //changes frame every 100 milliseconds
			m_nFrameIterator = 0;
			this->GetTexture()->SetCurrentFrame();
		}
		m_bDirection = LEFT;
		break;
	case MOVERIGHT:
		this->Move(dt, 0);
		m_nFrameIterator += dt;
		if (m_nFrameIterator >= 300) {
			m_nFrameIterator = 0;
			this->GetTexture()->SetCurrentFrame();
		}
		m_bDirection = RIGHT;
		break;
	case IDLE:
		this->GetTexture()->SetCurrentFrame(IDLE);
		break;
	default:
		break;

	}

	HAPI.RenderText(0, 10, HAPI_TColour::GREEN, std::to_string(this->GetPosition().x));
	HAPI.RenderText(0, 20, HAPI_TColour::GREEN, std::to_string(this->GetPosition().y));

}

void Player::UpdateY(long dt) {

	if (true == this->m_bJumping) {

		Jump(dt);

	}
	else {

		Fall(dt);

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

	if (true == b) {

		this->m_v2Pos = this->m_v2LastPos;

		m_fVelocity = -3.0f;
		m_bJumping = false;
		m_bFalling = true;

	}

	this->m_bCollided = b;

}

void Player::Jump(long dt) {

	m_bFalling = false;

	if (m_fVelocity < m_fMaxVelocity * 2) { //slowly decelerate velocity -- has to be velocity *2 to make up for speed up on the way down

		m_fVelocity += static_cast<float>(dt) / 100;

	}
	else {

		m_bJumping = false;
		m_bFalling = true;
		return;
	}

	this->SetPosition(m_v2Pos.x, m_v2Pos.y + static_cast<short>(m_fVelocity));


}

void Player::Fall(long dt) {

	m_bJumping = false;

	if (m_fVelocity < m_fMaxVelocity) {
		m_fVelocity -= static_cast<float>(dt) / 100;
	}
	else {
		m_bFalling = false;
	}


	this->SetPosition(m_v2Pos.x, this->m_v2Pos.y - static_cast<short>(m_fVelocity));

}

bool Player::Shoot(long dt) {

	if (m_nAttackSpeedIterator >= m_nAttackSpeed) {

		m_nAttackSpeedIterator = 0;
		
		return true;

	}

	return false;

}
