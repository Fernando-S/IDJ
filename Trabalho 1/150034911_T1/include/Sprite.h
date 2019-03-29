#pragma once

#ifndef Sprite_h
#define Sprite_h
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
//#include "SDL_image.h"
#include <string>

class Sprite {
public:
	Sprite();
	Sprite(const char*  file);
	~Sprite();
	void Open(const char* path);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y);
	int GetWidth();
	int GetHeight();
	bool IsOpen();

private:
	SDL_Texture* texture;
	int width, height;
	SDL_Rect clipRect;
};

#endif
