#include "Bullet.h"



Bullet::Bullet()
{
}

void Bullet::Update(float dt) {

	this->SetPosition(this->m_v2Pos.x + dt, this->m_v2Pos.y);

}


Bullet::~Bullet()
{
}
