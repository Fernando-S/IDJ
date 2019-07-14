#include <Game.h>


Sprite::Sprite(GameObject &associated) : Component(associated) {
	texture = nullptr;
}

Sprite::Sprite(GameObject &associated, const char* file) : Component(associated) {		// mudei para const char*
	Sprite(this->associated);
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
	Render((int)this->associated.box.x, (int)this->associated.box.y);	// evitando duplicacao de codigo organizado como solicitado em roteiro
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

void Sprite::Render(int x, int y) {
	SDL_Rect dstRect{x, y, clipRect.w, clipRect.h};

	if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0) {
		std::cerr << " SDL_RenderCopy returned error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}