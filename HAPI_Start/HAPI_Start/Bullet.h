#pragma once
#include "Entity.h"
#include "Vec2.h"
class Bullet :
	public Entity {

public:

	Bullet();

	void Update(float dt);

	void SetActive(bool b) { this->m_bActive = b; }

	bool IsActive() const { return this->m_bActive; }
	short GetDamage() const { return this->m_shDamage; }

	~Bullet();

private:

	short m_shDamage{ 10 };

	bool m_bActive{ false };

};

