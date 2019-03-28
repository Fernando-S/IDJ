#include "State.h"
#include "Sprite.h"
#include "Game.h"

State::State() : bg("./Recursos/img/ocean.jpg"), music("./Recursos/audio/stageState.ogg") {
	quitRequested = false;
	music.Play();
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::LoadAssets() {					// TODO - ver o q tem q colocar aqui

}

void State::Update(float){
	if (SDL_QuitRequested())
		Game::GetInstance().GetState().quitRequested = true;
}

void State::Render() {
	bg.Render(0,0);
}