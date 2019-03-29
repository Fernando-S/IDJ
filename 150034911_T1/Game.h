#pragma once

/************************************
*				Game				*
************************************/

#ifndef Game_h
#define Game_h
#include "State.h"
#include "SDL_include.h"
#define INDLUDE_SDL

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
