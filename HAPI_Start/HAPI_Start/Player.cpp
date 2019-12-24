#include "Player.h"

Player::~Player()
{



}

void Player::Update(long dt)
{

	m_nAttackSpeedIterator += dt; //updates timer on when the player can shoot next

}

void Player::UpdateX(long dt) {

	Update(dt);

	switch (m_nState) {

	case MOVELEFT:
		this->Move(-dt, 0);
		m_nFrameIterator += dt;
		if (m_nFrameIterator >= m_cnFrameChange) { //changes frame every 300 milliseconds of movement
			m_nFrameIterator = 0;
			this->GetTexture()->SetCurrentFrame();
		}
		m_bDirection = LEFT;
		break;

	case MOVERIGHT:
		this->Move(dt, 0);
		m_nFrameIterator += dt;
		if (m_nFrameIterator >= m_cnFrameChange) {
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

}

void Player::UpdateY(long dt) {

	if (true == this->m_bJumping) { //player can either jump or fall in Y nothing else

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
		m_bCollided = false;
		m_bFalling = true;

		return;

	}

	this->m_bCollided = b;

}

void Player::Jump(long dt) {

	m_bFalling = false;

	if (m_fVelocity < m_fMaxVelocity * 2) { //slowly decelerate velocity -- has to be velocity *2 to make up for speed up on the way down

		m_fVelocity += static_cast<float>(dt) / 100;
		this->Move(0, m_fVelocity * dt); //multiplying themovement by delta time allows for it to work in all framerates

	}
	else {

		m_bJumping = false;
		m_bFalling = true;
		return;
	}

}

void Player::Fall(long dt) {

	m_bJumping = false;

	if (m_fVelocity < m_fMaxVelocity) {
		m_fVelocity -= static_cast<float>(dt) / 100;
		this->Move(0, static_cast<int>(-(m_fVelocity * dt)));
	}
	else {
		m_bFalling = false;
	}

}

bool Player::Shoot(long dt) {

	if (m_nAttackSpeedIterator >= m_cnAttackSpeed) {

		m_nAttackSpeedIterator = 0;
		
		return true;

	}

	return false;

}
