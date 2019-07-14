#pragma once

/************************************
*				Game				*
************************************/

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "State.h"
#include "InputManager.h"
//#include "SDL.h"							// Comentar e usar SDL_include.h para enviar
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
	float GetDeltaTime();
	int GetWidth();
	int GetHeight();
	
private:
	Game(const char* title, int width, int height);
	void CalculateDeltaTime();
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	int frameStart;
	float dt;
	int width, height;
	
};









/*
class Game {
public:
	~Game();
	void Run();
	float GetDeltaTime();

	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
	int GetWidth();
	int GetHeight();

private:
	Game(std::string title, int width, int height);

	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;

	int frameStart;
	float dt;
	int width;
	int height;

	void CalculateDeltaTime();
};
*/


#endif // GAME_H