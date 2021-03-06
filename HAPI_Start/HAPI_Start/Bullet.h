#pragma once

#include "WorldEntity.h"
#include "Vec2.h"

class Bullet :
	public Entity {

public:

	Bullet();
	Bullet(int h, int x, int y, std::string id, int side) : Entity(h, x, y, id, side) { }

	void Update(long dt) override;

	void SetActive(bool b) { this->m_bActive = b; }
	void SetDirection(bool b) { this->m_bDirection = b; }

	bool IsActive() const { return this->m_bActive; }
	short GetDamage() const { return this->m_shDamage; }

	~Bullet();

private:

	const short m_shDamage{ 10 },
		m_shSpeed{ 2 };

	bool m_bActive{ false },
		m_bDirection{ LEFT };

};

