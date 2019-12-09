#pragma once

#include "Entity.h"

class WorldEntity : 
	public Entity{

public:

	WorldEntity() = default;
	WorldEntity(const std::string alias, Vec2 pos, int side, short health);
	~WorldEntity();

	void Update() override;

private:

	int m_nSide{ 0 };
	short m_shHealth{ 0 };

};

