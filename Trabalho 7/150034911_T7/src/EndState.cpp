#include "EndState.h"
#include "Game.h"


EndState::EndState() {
	auto bgGO = new GameObject();
	bgGO->box = { 0,0 };
	Sprite* bg = nullptr;

	if (GameData::playerVictory) {
		backgroundMusic = Music("./assets/audio/endStateWin.ogg");
		backgroundMusic.Play();

		bg = new Sprite(*bgGO, "./assets/img/win.jpg");
	}
	else {
		backgroundMusic = Music("./assets/audio/endStateLose.ogg");
		backgroundMusic.Play();

		bg = new Sprite(*bgGO, "./assets/img/lose.jpg");
	}

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);
	
	// Texto "Press to Play Again"
	auto textGO = new GameObject();
	SDL_Color textColor = { 120, 120, 255, 255 };		// R, G, B, A
	// todo - colocar ultimo parametro para ser o tempo de pisca pisca
	auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 40, Text::SOLID, "Press SPACE to play again, or ESC to exit", textColor/*, 0.7*/);
	textGO->AddComponent(text);

	// Posiciona o texto dependendo se eh a tela de vitoria ou derrota
	if(GameData::playerVictory)
		textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight() * 5 / 7.0f/* / 2.0f */});
	else
		textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight()/ 7.0f/* / 2.0f */ });
	
	objectArray.emplace_back(textGO);
}

EndState::~EndState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

	if (inputManager.KeyPress(SPACE_KEY))
		popRequested = true;				// Seta o popRequested para retornar a TitleSet ao apertar ESPACO

	UpdateArray(dt);	// executa o update em cada um dos objetos no objectArray
}

void EndState::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void EndState::Start() {
	LoadAssets();
	Camera::pos = { 0,0 };
	StartArray();					// Da Start em cada GameObject no objectArray
}

void EndState::Pause() {

}

void EndState::Resume() {

}
