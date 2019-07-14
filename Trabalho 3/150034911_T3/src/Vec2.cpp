#include "Vec2.h"

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2::Vec2(){						// Vec2 nulo
	this->x = 0.0;
	this->y = 0.0;
}

Vec2 Vec2::GetRotated(float radians) {
	return { this->x*std::cos(radians) - this->y*std::sin(radians), this->y*std::cos(radians) + this->x*std::sin(radians) };
}

Vec2 Vec2::operator+(Vec2 vector2) {
	return { this->x + vector2.x, this->y + vector2.y };
}