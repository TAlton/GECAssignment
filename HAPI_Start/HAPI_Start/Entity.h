#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include "Vec2.h"
#include "Physics.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

enum eSide : int { NEUTRAL = 0, PLAYER, ENEMY, NOCOLLIDE };

class Entity {

public:

	Entity() = default;
	Entity(short h, Vec2 P, const char* id, int side) : m_nHealth(h), m_v2Pos(P), m_strAlias(id), m_ESide(side) {}
	Entity(short h, short x, short y, std::string id, int side) : m_nHealth(h), m_strAlias(id), m_ESide(side) { SetPosition(x, y); }
	Entity(const Entity& e) : m_nHealth(e.GetHealth()), m_v2Pos(e.GetPosition()), m_strAlias(e.GetAlias()) {}
	~Entity();

	virtual void Update(float dt) = 0;

	Vec2 GetPosition() const { return this->m_v2Pos; }
	Vec2 GetLastPosition() const { return this->m_v2LastPos; }
	std::string GetAlias() const { return this->m_strAlias; }
	Rectangle* GetRectangle() const { return this->m_pRectangle; }
	Texture* GetTexture() const { return this->m_pTex; }
	int GetWidth() const { return this->m_nWidth; }
	int GetHeight() const { return this->m_nHeight; }
	int GetHealth() const { return this->m_nHealth; }
	unsigned char* GetTexturePointer() const { return this->m_pTex->GetPointer(); }

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
		m_nHeight{ 0 },
		m_nHealth{ 0 };

	std::string m_strAlias{ "default" };

	Texture* m_pTex = nullptr;
	
	Rectangle* m_pRectangle = nullptr;
};

