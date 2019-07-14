#pragma once

#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
public:
	float x, y, w, h;
	Rect(float x, float y, float w, float h);
	Rect();
	bool Contains(Vec2 vector);
	Vec2 Center();
	
};

#endif	//RECT_H