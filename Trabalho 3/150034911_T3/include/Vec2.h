#pragma once

#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class Vec2{
public:
	float x, y;
	Vec2(float x, float y);
	Vec2();
	Vec2 GetRotated(float radians);
	Vec2 operator+(Vec2 vector2);
};

#endif	//VEC2_H