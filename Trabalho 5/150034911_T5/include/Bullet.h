#pragma once

#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"

class Bullet : public Component{
public:
	Bullet(GameObject& associated , float angle, float speed, int damage, float maxDistance, const char* sprite);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	int GetDamage();
		
private:
	Vec2 speed;
	float distanceLeft;
	int damage;
	float speedMagnitude;

};

#endif	//BULLET_H