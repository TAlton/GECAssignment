#include "Enemy.h"



Enemy::Enemy() {

	this->m_v2Pos = this->m_v2LastPos = Vec2(0, 0);
	this->m_strAlias = "Enemy";
	this->m_ESide = ENEMY;

}

Enemy::Enemy(Vec2 v = Vec2(0,0)) {

	this->m_v2Pos = this->m_v2LastPos = v;
	this->m_strAlias = "Enemy";
	this->m_ESide = ENEMY;

}

Enemy::Enemy(short x, short y) {

	this->m_v2Pos.x = this->m_v2LastPos.x = x;
	this->m_v2Pos.y = this->m_v2LastPos.y = y;
	this->m_strAlias = "Enemy";
	this->m_ESide = ENEMY;

}


Enemy::~Enemy()
{
}
