#include "State.h"


State::State() : music("./assets/audio/stageState.ogg") {
	// Background
	auto bgGO = new GameObject();
	bgGO->box.x = 0;
	bgGO->box.y = 0;
	auto bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
//	auto bgCameraFollower = new CameraFollower(*bgGO);	
	bgGO->AddComponent(bg);
//	bgGO->AddComponent(bgCameraFollower);
	objectArray.emplace_back(bgGO);

	// Mapa
	auto mapGO = new GameObject();
	mapGO->box.x = 0;
	mapGO->box.y = 0;
	auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
	auto tileMap = new TileMap(*mapGO, ".assets/map/tileMap.txt", tileSet);

	auto mapCameraFollower = new CameraFollower(*mapGO);
	mapGO->AddComponent(mapCameraFollower);

	mapGO->AddComponent(tileMap);
	objectArray.emplace_back(mapGO);

	quitRequested = false;
	music.Play();
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::LoadAssets() {

}

void State::Update(float dt){
	unsigned i;
	auto inputManager = InputManager::GetInstance();

	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

	// Checa se foi solicitada a saida do jogo
	if (inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested())
		quitRequested = true;
	else
		quitRequested = false;

	// Cria um penguin inimigo ao pressionar espaco
	if (inputManager.KeyPress(SPACE_KEY)) {
		Vec2 objPos = Vec2(200.0, 0.0).GetRotated((float)(-PI + PI * (std::rand() % 1001) / 500.0)) + Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
		AddObject((int)objPos.x, (int)objPos.y);
	}

	// Faz o update de cada objeto no vetor
	for (auto &gameObjects : objectArray) {
		gameObjects->Update(dt);
	}

	// Checa se houve a morte de algum objeto
	for (i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead())
			objectArray.erase(objectArray.begin() + i);
	}
}

void State::Render() {
	for (auto &gameObjects : objectArray) {
		gameObjects->Render();
	}

}

State::~State() {
	objectArray.clear();
}

void State::AddObject(int mouseX, int mouseY) {
	auto gameObject = new GameObject();
	gameObject->box.x = mouseX;
	gameObject->box.y = mouseY;

	auto sprite = new Sprite(*gameObject, "./assets/img/penguinface.png");
	auto sound = new Sound(*gameObject, "./assets/audio/boom.wav");
	auto face = new Face(*gameObject);
	gameObject->AddComponent(sprite);
	gameObject->AddComponent(sound);
	gameObject->AddComponent(face);

	objectArray.emplace_back(gameObject);
}