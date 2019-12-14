#pragma once

#include "WorldEntity.h"
#include "Vec2.h"

class Bullet :
	public Entity {

public:

	Bullet();
	Bullet(int h, int x, int y, std::string id, int side) : Entity(h, x, y, id, side) { }

	void Update(float dt) override;

	void SetActive(bool b) { this->m_bActive = b; }

	bool IsActive() const { return this->m_bActive; }
	short GetDamage() const { return this->m_shDamage; }

	~Bullet();

private:

	short m_shDamage{ 10 };

	bool m_bActive{ false };

};

