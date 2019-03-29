#pragma once

/************************************
*				Game				*
************************************/

#ifndef Game_h
#define Game_h
#include "State.h"
#include <iostream>
#define INDLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"


class Game {
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();

private:
	Game(const char* title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;

};

#endif // Game.h
