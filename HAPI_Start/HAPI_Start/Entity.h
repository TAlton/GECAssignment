#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include "Vec2.h"

class Entity {

public:
	Entity();
	~Entity();

protected:

	Vec2 m_v2Pos{ 0,0 },
		m_v2LastPos{ 0,0 };

	std::string m_strAlias{ "default" };

	Texture m_Texture;

	Rectangle m_Rectangle;
};

