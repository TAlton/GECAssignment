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

	virtual void Update(float dt) = 0;

	const Vec2 GetPosition() const { return this->m_v2Pos; }
	const Vec2 GetLastPosition() const { return this->m_v2LastPos; }
	const std::string GetAlias() const { return this->m_strAlias; }
	const std::shared_ptr<Rectangle>& GetRectangle() const { return this->m_pRectangle; }
	const std::shared_ptr<Texture>& GetTexture() const { return this->m_pTexture; }

	void SetPosition(short x, short y) { this->m_v2LastPos = this->m_v2Pos; this->m_v2Pos.x = x; this->m_v2Pos.y = y; }
	void SetPosition(Vec2 v) { this->m_v2LastPos = this->m_v2Pos; this->m_v2Pos.x = v.x; this->m_v2Pos.y = v.y; }

protected:

	Vec2 m_v2Pos{ 0,0 },
		m_v2LastPos{ 0,0 };

	std::string m_strAlias{ "default" };

	std::shared_ptr<Texture> m_pTexture = nullptr;
	std::shared_ptr<Rectangle> m_pRectangle = nullptr;
};

