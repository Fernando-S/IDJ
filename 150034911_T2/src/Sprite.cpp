#include <Game.h>


Sprite::Sprite(GameObject &associated) : Component(associated) {
	texture = nullptr;
}

Sprite::Sprite(GameObject &associated, const char* file) : Component(associated) {		// mudei para const char*
	texture = nullptr;
	Open(file);
}

Sprite::~Sprite() {
	if (texture)
		SDL_DestroyTexture(texture);
}

void Sprite::Open(const char* file) {								// mudei para const char*
	if (texture)
		SDL_DestroyTexture(texture);

	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file);

	if (!texture) {
		std::cerr << "IMG_LoadTexture  returned ERROR: " << SDL_GetError() << std::endl;
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
	SDL_Rect onScreenRect = { (int)this->associated.box.x, (int)this->associated.box.y, clipRect.w, clipRect.h };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &onScreenRect);

	if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &onScreenRect) != 0) {
		std::cerr << "SDL_RenderCopy  returned ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
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
	return width;
}

int Sprite::GetHeight() {
	return  height;
}

bool Sprite::IsOpen() {
	if (texture != nullptr)
		return true;
	else
		return false;
}