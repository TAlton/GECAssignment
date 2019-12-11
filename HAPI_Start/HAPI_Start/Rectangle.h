#pragma once

#include "Vec2.h"

class Rectangle {

public:

	Rectangle(short width, short height) : m_shRight(width), m_shBottom(height) {}

	short m_shLeft{ 0 },
		m_shRight{ 0 },
		m_shTop{ 0 },
		m_shBottom{ 0 };

	Rectangle() = default;
	~Rectangle();

	void ClipTo(const Rectangle& other);
	void Translate(Vec2 v);
	void Translate(short x, short y);

	bool Contains(const Rectangle& other);
	bool Outside(const Rectangle& other);
	bool Overlap(const Rectangle& other);

	short GetWidth() { return this->m_shRight; }
	short GetHeight() { return this->m_shBottom; }
	short GetLeft() { return this->m_shLeft; }
	short GetRight() { return this->m_shRight; }
	short GetTop() { return this->m_shTop; }
	short GetBottom() { return this->m_shBottom; }


};

