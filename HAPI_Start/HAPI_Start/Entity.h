#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include "Vec2.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Entity {

	enum eSide : int { NEUTRAL = 0, PLAYER, ENEMY };

public:

	Entity() = default;
	Entity(Vec2 v, std::string alias, Texture* pTex, Rectangle* pRect) : m_v2Pos(v), m_strAlias(alias), m_pTex(pTex), m_pRectangle(pRect) {}
	~Entity();

	virtual void Update(float dt) = 0;

	const Vec2 GetPosition() const { return this->m_v2Pos; }
	const Vec2 GetLastPosition() const { return this->m_v2LastPos; }
	const std::string GetAlias() const { return this->m_strAlias; }
	const Rectangle* GetRectangle() const { return this->m_pRectangle; }
	const Texture* GetTexture() const { return this->m_pTex; }

	void SetPosition(short x, short y) { this->m_v2LastPos = this->m_v2Pos; this->m_v2Pos.x = x; this->m_v2Pos.y = y; }
	void SetPosition(Vec2 v) { this->m_v2LastPos = this->m_v2Pos; this->m_v2Pos.x = v.x; this->m_v2Pos.y = v.y; }
	void SetHeight(int h) { this->m_nHeight = h; }
	void SetWidth(int w) { this->m_nWidth = w; }
	void SetTexture(Texture& tex) {

		m_pTex = &tex;
		SetWidth(m_pTex->GetWidth());
		SetHeight(m_pTex->GetHeight());
		m_pRectangle = new Rectangle(m_nWidth, m_nHeight);

	};

protected:

	Vec2 m_v2Pos{ 0,0 },
		m_v2LastPos{ 0,0 };

	int m_ESide = NEUTRAL,
		m_nWidth{ 0 },
		m_nHeight{ 0 };

	std::string m_strAlias{ "default" };

	Texture* m_pTex = nullptr;
	
	Rectangle* m_pRectangle = nullptr;
};

