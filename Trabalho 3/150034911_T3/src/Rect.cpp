#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::Rect() {								// Rect nulo
	this->x = 0.0;
	this->y = 0.0;
	this->w = 0.0;
	this->h = 0.0;
}

bool Rect::Contains(Vec2 vector) {
	if ( (vector.x >= this->x) && ( vector.x <= (this->x + this->w) ) &&
		 (vector.y >= this->y) && ( vector.y <= (this->y + this->h) ) )
		return true;
	else
		return false;
}