#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include "Vec2.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Entity {

public:

	Entity() = default;
	Entity(Vec2 v, std::string alias, std::shared_ptr<Texture> pTex, std::shared_ptr<Rectangle> pRect) : m_v2Pos(v), m_strAlias(alias), m_pTexture(pTex), m_pRectangle(pRect) {}
	~Entity();

	virtual void Update() = 0;

protected:

	Vec2 m_v2Pos{ 0,0 },
		m_v2LastPos{ 0,0 };

	std::string m_strAlias{ "default" };

	std::shared_ptr<Texture> m_pTexture = nullptr;
	std::shared_ptr<Rectangle> m_pRectangle = nullptr;
};

