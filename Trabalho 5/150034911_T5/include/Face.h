#pragma once

#ifndef FACE_H
#define FACE_H

#include "Component.h"
#include "Sound.h"
#include "Camera.h"

class Face : public Component {
public:
	Face(GameObject& associated);
	void Damage(int damage);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	bool DeadAlready();

private:
	int hitpoints, x, y;
	Sound* soundComponent;
};

#endif //FACE_H