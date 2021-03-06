#include "Text.h"
#include "Game.h"


Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated) {
	texture = nullptr;
	this->text = text;
	this->style = style;
	this->fontFile = fontFile;
	this->fontSize = fontSize;
	this->color = color;

	// todo - fazer uma logica para piscar
	intermittenceCount = 0;
	this->intermittenceSeconds = intermittenceSeconds;
	RemakeTexture();
}

Text::~Text() {
	if (texture)
		SDL_DestroyTexture(texture);
}

void Text::Update(float dt) {
	if (intermittenceSeconds > 0) {
		intermittenceCount.Update(dt);

		float currentTime = intermittenceCount.Get();
		float twiceIntermittenceSeconds = 2 * intermittenceSeconds;

		if (currentTime > twiceIntermittenceSeconds)
			intermittenceCount.Set(currentTime - twiceIntermittenceSeconds);
	}
}

void Text::Render() {
	// renderiza quando 0 < tempo do timer< intermittenceSeconds para piscar
	// todo - fazer piscar e/ou mudar de cor
//	if (intermittenceCount.Get() < intermittenceSeconds) {
		SDL_Rect dstRect{ (int)(associated.box.x - Camera::pos.x),
						  (int)(associated.box.y - Camera::pos.y),
						  (int) associated.box.w,
						  (int) associated.box.h };

		SDL_Rect clipRect{ 0, 0, (int) associated.box.w, (int) associated.box.h} ;

		if (SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0) {
			std::cerr << "SDL_RenderCopy returned ERROR: " << SDL_GetError() << std::endl;
			exit(1);
		}
//	}
}

bool Text::Is(std::string type) {
	if (type == "Text")
		return true;
	else
		return false;
}

void Text::SetText(std::string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
	this->fontFile = fontFile;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture() {
	if (texture)
		SDL_DestroyTexture(texture);

	font = Resources::GetFont(fontFile, fontSize);

	if (!font) {
		std::cerr << "This font could not be opened. Aborting...\n";
		exit(1);
	}

	SDL_Surface* surface = nullptr;

	switch (style) {
	case SOLID:
		surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
		break;
	case BLENDED:
		surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
		break;
	default:
		surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, GetSDLColor(255, 0, 0, 0));
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

	if (!font) {
		std::cerr << "This texture could not be loaded from the surface. Aborting..." << std::endl;
		exit(1);
	}

	associated.box.w = surface->w;
	associated.box.h = surface->h;

	SDL_FreeSurface(surface);
}

SDL_Color Text::GetSDLColor(Uint8 a, Uint8 r, Uint8 g, Uint8 b) {
	return { r, g, b, a };
}

