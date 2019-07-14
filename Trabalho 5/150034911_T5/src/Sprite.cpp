#include <Game.h>
#include "Sprite.h"


Sprite::Sprite(GameObject &associated) : Component(associated) {
	texture = nullptr;
	width = 0;
	height = 0;
	scale = {1, 1};
}

Sprite::Sprite(GameObject &associated, const char* file) : Component(associated) {		// mudei para const char*
	Sprite(this->associated);
	texture = nullptr;
	width = 0;
	height = 0;
	scale = {1, 1};
	Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(const char* file) {								// mudei para const char*
	if (texture)
		SDL_DestroyTexture(texture);

	texture = Resources::GetImage(file);

	if (!texture) {
		std::cerr << " IMG_LoadTexture  returned ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);									// seta o clip para textura inteira

	// Passa as dimensoes
	this->associated.box.w = width;
	this->associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect = { x, y, w, h };
}

void Sprite::Render() {
	if (background)					// renderiza na posicao da camera se for background
		Render((int)this->associated.box.x, (int)this->associated.box.y);
	else							// renderiza na posicao no mundo se nao for
		Render((int)(this->associated.box.x - Camera::pos.x), (int)(this->associated.box.y - Camera::pos.y));
}

void Sprite::Update(float dt) {

}

bool Sprite::Is(std::string type) {
	if (type == "Sprite")
		return true;
	else
		return false;
}

int Sprite::GetWidth() {
	return (int)(width*scale.x);
}

int Sprite::GetHeight() {
	return  (int)(height*scale.y);
}

bool Sprite::IsOpen() {
	if (texture != nullptr)
		return true;
	else
		return false;
}

void Sprite::Render(int x, int y) {

	SDL_Rect dstRect{x, y, (int)clipRect.w*scale.x, (int)clipRect.h*scale.y };

	if (SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0) {
		std::cerr << "SDL_RenderCopy RETURNED ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}	  
}

void Sprite::SetScale(float scaleX, float scaleY) {
	scale.x = (scaleX) ? scaleX : scale.x;
	scale.y = (scaleY) ? scaleY : scale.y;

	auto lastCenter = associated.box.Center();

	associated.box.w = GetWidth();
	associated.box.h = GetHeight();

	associated.box += (lastCenter - associated.box.Center());
}

Vec2 Sprite::GetScale() {
	return scale;
}
