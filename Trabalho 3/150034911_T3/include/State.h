#pragma once

#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"

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
	void Input();
	void AddObject(int mouseX, int mouseY);
	std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif	//STATE_H