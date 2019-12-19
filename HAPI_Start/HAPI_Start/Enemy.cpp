#include "Enemy.h"



Enemy::Enemy() {

	this->m_v2Pos = this->m_v2LastPos = Vec2(0, 0);
	this->m_strAlias = "Enemy";
	this->m_ESide = ENEMY;
	this->m_pRectAI = &Rectangle(this->m_nWidth << 2, this->m_nHeight);
	m_pRectAI->SetTop(-(this->m_nHeight)); //move to minus space so that it translates with the entity in the center
	m_pRectAI->SetLeft(-(this->m_nWidth << 1));

}

Enemy::Enemy(Vec2 v = Vec2(0,0)) {

	this->m_v2Pos = this->m_v2LastPos = v;
	this->m_strAlias = "Enemy";
	this->m_ESide = ENEMY;
	this->m_pRectAI = &Rectangle(this->m_nWidth << 2, this->m_nHeight);
	m_pRectAI->SetTop(-(this->m_nHeight)); //move to minus space so that it translates with the entity in the center
	m_pRectAI->SetLeft(-(this->m_nWidth << 1));

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

