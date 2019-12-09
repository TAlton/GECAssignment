#pragma once
class Vec2 {
public:

	short x{ 0 },
		y{ 0 };

	Vec2(short x, short y) : x(x), y(y) {}
	~Vec2();

	Vec2 operator+(const Vec2& v) {
		this->x += v.x;
		this->y += v.y;
	}

	Vec2 operator*(const int& x) {

		this->x *= static_cast<short>(x);
		this->y *= static_cast<short>(y);

	}

	Vec2 operator-(const Vec2& v) {

		this->x -= v.x;
		this->y -= v.y;

	}

};

