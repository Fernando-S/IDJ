#pragma once

#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "State.h"
#include "EndState.h"

#define PI 3.14159265
#define ALIEN_NUMBER 3

class StageState : public State{
public:	
	StageState();
	~StageState() override;
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	

private:	
	TileSet* tileSet;
	Music backgroundMusic;
	
	// todo - mexer melhor nisso para mudar de tela apenas apos o fim das animacoes de explosao
	Timer TimeToEndPlayerAnimation, TimeToEndAlienAnimation;
	float secondsToEndPlayerAnimation = 1.5, secondsToEndAlienAnimation = 1.2;
	
};

#endif	//STAGESTATE_H
