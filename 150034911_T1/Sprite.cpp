#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite() {
	texture = nullptr;
}

Sprite::Sprite(const char* file) {									// mudei para const char*
	texture = nullptr;
	Open(file);
}

Sprite::~Sprite() {
	if (texture)
		SDL_DestroyTexture(texture);
}

void Sprite::Open(const char* path) {								// mudei para const char*
	if (texture)
		SDL_DestroyTexture(texture);
	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);

	if (!texture) {
		std::cerr << "IMG_LoadTexture  returned ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);									// seta o clip para textura inteira
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y) {
	SDL_Rect onScreenRect = {x, y, clipRect.w, clipRect.h};
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &onScreenRect);

	if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &onScreenRect) != 0) {
		std::cerr << "SDL_RenderCopy  returned ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

bool Sprite::IsOpen() {
	if (texture != nullptr)
		return true;
	else
		return false;
}