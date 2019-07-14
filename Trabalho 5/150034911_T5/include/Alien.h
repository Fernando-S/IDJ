#pragma once

#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Minion.h"
#include "Camera.h"
#include "InputManager.h"
#include <vector>
#include <queue>


#define ALIEN_SPEED 300					// em pixels/s
#define ALIEN__ANGULAR_SPEED -20		// em angleDeg
#define ALIEN_MAX_HP 30

class Alien : public Component{
public:
	Alien(GameObject& associated, int nMinions);
	~Alien();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;

private:
	class Action {
	public:
		enum ActionType {MOVE, SHOOT};
		Action(ActionType type, float x, float y);

		ActionType type;
		float x;
		Vec2 pos;	
	};
	Vec2 speed;
	int hp;
	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject>> minionArray;
	int Minions;
};

#endif	//ALIEN_H