#pragma once

#ifndef STATE_H
#define STATE_H

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

#define PI 3.14159265

class State{
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
	~State();
	void Start();
	std::weak_ptr<GameObject> AddObject(GameObject* go);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

private:
	Music music;
	bool quitRequested;
	std::vector<std::shared_ptr<GameObject>> objectArray;
	bool started;
};

#endif	//STATE_H
