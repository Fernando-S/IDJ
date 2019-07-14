#pragma once

#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "Camera.h"

#define PI 3.14159265

class State{
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
	~State();

private:
	Music music;
	bool quitRequested;
	void AddObject(int mouseX, int mouseY);
	std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif	//STATE_H