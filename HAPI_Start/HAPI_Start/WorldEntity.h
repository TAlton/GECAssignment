#pragma once

#include "Entity.h"

class WorldEntity : 
	public Entity{

public:

	WorldEntity(short h, Vec2 P, const char* id, int side) : Entity(h, P, id, side) {}
	WorldEntity(int h, int x, int y, std::string id, int side) : Entity(h, x, y, id, side) { SetPosition(x, y); }
	WorldEntity(const Entity& e) : Entity(e) {}
	~WorldEntity();

	void Update(long dt) override;

private:

	int m_nSide{ 0 };
	short m_shHealth{ 0 }; //health is added due to potential for breakable objects

};

