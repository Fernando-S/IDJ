#pragma once

#ifndef MINION_H
#define MINION_H

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Bullet.h"


#define ANGULAR_SPEED (PI/2)				// em rad/s
#define RADIUS 150							// em pixels
#define BULLET_SPEED 1000
#define BULLET_MAX_DAMAGE 20
#define BULLET_MAX_DISTANCE 1000

class Minion : public Component{
public:
	Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void Shoot(Vec2 target);
		
		
private:
//	GameObject& alienCenter;
	std::weak_ptr<GameObject> alienCenter;	// mudei para poder usar waek_ptr
	float arc;

};

#endif	//MINION_H