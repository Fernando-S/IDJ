#pragma once

#ifndef State_h
#define State_h
//#include "SDL.h"
#include "Sprite.h"
#include "Music.h"

class State{
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();

private:
	Sprite bg;
	Music music;
	bool quitRequested;
};

#endif