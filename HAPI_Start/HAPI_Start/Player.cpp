#include "Player.h"

Player::~Player()
{



}

void Player::Update(float dt)
{

	m_nAttackSpeedIterator += dt;

}

void Player::UpdateX(float dt) {

	Update(dt);

	switch (m_nState) {

	case MOVELEFT:
		this->Move(-dt, 0);
		m_nFrameIterator += dt;
		if (m_nFrameIterator >= 100) { //changes frame every 100 milliseconds
			m_nFrameIterator = 0;
			this->GetTexture()->SetCurrentFrame();
		}
		break;
	case MOVERIGHT:
		this->Move(dt, 0);
		m_nFrameIterator += dt;
		if (m_nFrameIterator >= 100) {
			m_nFrameIterator = 0;
			this->GetTexture()->SetCurrentFrame();
		}
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

void Player::UpdateY(float dt) {

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

void Player::Jump(float dt) {

	m_bFalling = false;

	if (m_fVelocity < m_fMaxVelocity * 2) { //slowly decelerate velocity -- has to be velocity *2 to make up for speed up on the way down

		m_fVelocity += dt / 100;

	}
	else {

		m_bJumping = false;
		m_bFalling = true;
		return;
	}

	this->SetPosition(m_v2Pos.x,
		static_cast<int>(PHYSICS->Lerp(this->m_v2Pos.y,
			this->m_v2Pos.y + m_fVelocity, 1.0f)));  //issue passing in t


}

void Player::Fall(float dt) {

	m_bJumping = false;

	if (m_fVelocity < m_fMaxVelocity) {
		m_fVelocity -= dt / 100;
	}
	else {
		m_bFalling = false;
	}


	this->SetPosition(m_v2Pos.x,
		static_cast<int>(PHYSICS->Lerp(this->m_v2Pos.y,
			this->m_v2Pos.y - m_fVelocity, 1.0f)));

}

bool Player::Shoot(float dt) {

	if (m_nAttackSpeedIterator >= m_nAttackSpeed) {

		m_nAttackSpeedIterator = 0;
		
		return true;

	}

	return false;

}
