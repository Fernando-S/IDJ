#pragma once

#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "CameraFollower.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "Text.h"
#include "Camera.h"
#include "TitleState.h"

class TitleState : public State{
public:
	TitleState();
	~TitleState();
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	
};

#endif	//TITLESTATE_H
