#pragma once

#include "Entity.h"

class WorldEntity : 
	public Entity{

public:

	WorldEntity(const std::string alias, Vec2 pos, int side, short health);
	~WorldEntity();

private:

	int m_nSide{ 0 };
	short m_shHealth{ 0 };

};

