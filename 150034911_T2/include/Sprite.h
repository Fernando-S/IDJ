#pragma once

#ifndef SPRITE_H
#define SPRITE_H

//#define INCLUDE_SDL_IMAGE
//#include "SDL_include.h"
#include "SDL_image.h"							// Comentar e suar SDL_include.h para enviar
#include "Component.h"
#include "GameObject.h"
#include <iostream>

class Sprite: public Component {
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, const char* file);
	~Sprite() override;
	void Open(const char* path);
	void SetClip(int x, int y, int w, int h);
	void Render() override;
	void Update(float dt) override;
	bool Is(std::string type) override;
	int GetWidth();
	int GetHeight();
	bool IsOpen();

private:
	SDL_Texture* texture;
	int width, height;
	SDL_Rect clipRect;

};

#endif	//SPRITE_H
