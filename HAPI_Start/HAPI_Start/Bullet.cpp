#include "Bullet.h"



Bullet::Bullet()
{
}

void Bullet::Update(long dt) {

	if(this->m_bDirection == LEFT) this->SetPosition(this->m_v2Pos.x - dt, this->m_v2Pos.y);
	if (this->m_bDirection == RIGHT) this->SetPosition(this->m_v2Pos.x + dt, this->m_v2Pos.y);

}


Bullet::~Bullet()
{
}
