#pragma once

#ifndef Sprite_h
#define Sprite_h
#include "SDL_image.h"
#include "SDL_include.h"
#include <string>
#define INDLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

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
