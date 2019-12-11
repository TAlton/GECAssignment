#include "Rectangle.h"



Rectangle::~Rectangle()
{
}

void Rectangle::ClipTo(const Rectangle& other) {

	if (this->m_shTop < other.m_shTop) this->m_shTop = other.m_shTop;
	if (this->m_shLeft < other.m_shLeft) this->m_shLeft = other.m_shLeft;
	if (this->m_shBottom > other.m_shBottom) this->m_shBottom = other.m_shBottom;
	if (this->m_shRight > other.m_shRight) this->m_shRight = other.m_shRight;

	if (this->m_shTop > other.m_shBottom) this->m_shTop = other.m_shBottom;
	if (this->m_shLeft > other.m_shRight) this->m_shLeft = other.m_shRight;
	if (this->m_shBottom < other.m_shTop) this->m_shBottom = other.m_shTop;
	if (this->m_shRight < other.m_shLeft) this->m_shRight = other.m_shLeft;

}

void Rectangle::Translate(Vec2 v) {

	this->m_shLeft += v.x;
	this->m_shRight += v.x;
	this->m_shTop += v.y;
	this->m_shBottom += v.y;

}
/*
@param x 
*/
void Rectangle::Translate(short x, short y) {

	this->m_shLeft += x;
	this->m_shRight += x;
	this->m_shTop += y;
	this->m_shBottom += y;

}

bool Rectangle::Contains(const Rectangle& other) {

	if (this->m_shTop > other.m_shBottom) return false;
	if (this->m_shBottom < other.m_shTop) return false;
	if (this->m_shRight < other.m_shLeft) return false;
	if (this->m_shLeft > other.m_shRight) return false;

	return true;

}

bool Rectangle::Outside(const Rectangle& other) {

	if (this->m_shTop > other.m_shBottom) return true;
	if (this->m_shBottom < other.m_shTop) return true;
	if (this->m_shRight < other.m_shLeft) return true;
	if (this->m_shLeft > other.m_shRight) return true;

	return false;
}


bool Rectangle::Overlap(const Rectangle& other) {

	if (this->m_shLeft < other.m_shRight && this->m_shRight > other.m_shLeft &&
		this->m_shTop > other.m_shBottom && this->m_shBottom < other.m_shTop) return true;

	return false;

}
