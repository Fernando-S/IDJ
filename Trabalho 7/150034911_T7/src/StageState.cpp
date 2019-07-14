#include "StageState.h"
#include "Game.h"
#include "GameData.h"


StageState::StageState() {
}

void StageState::LoadAssets() {
	int i;

	// Carrega a Musica e aperta o play
	backgroundMusic = *new Music("./assets/audio/stageState.ogg");
	backgroundMusic.Play();



	// Carrega o Background
	auto bgGO = new GameObject();
	bgGO->box.x = 0;
	bgGO->box.y = 0;
	auto bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
	bg->background = true;
	//	auto bgCameraFollower = new CameraFollower(*bgGO);	
	bgGO->AddComponent(bg);
	//	bgGO->AddComponent(bgCameraFollower);
	objectArray.emplace_back(bgGO);


	// Carrega o Mapa
	auto mapGO = new GameObject();
	mapGO->box.x = 0;
	mapGO->box.y = 0;
	auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
	auto tileMap = new TileMap(*mapGO, ".assets/map/tileMap.txt", tileSet);

	auto mapCameraFollower = new CameraFollower(*mapGO);
	mapGO->AddComponent(mapCameraFollower);

	mapGO->AddComponent(tileMap);
	objectArray.emplace_back(mapGO);

	for (i = 0; i < ALIEN_NUMBER; i++) {
		auto alienGO = new GameObject();

		auto alien = new Alien(*alienGO, 3, (std::rand() % (ALIEN_RESTING_TIME * 100)) / 100.f);

		alienGO->AddComponent(alien);
		alienGO->box.PlaceCenter({ float(std::rand() % 1408),float(std::rand() % 1280) });

		objectArray.emplace_back(alienGO);
	}
	
	
	// Carrega o Penguin
	auto penguinGO = new GameObject();
	auto penguin = new PenguinBody(*penguinGO);

	penguinGO->AddComponent(penguin);
	penguinGO->box.PlaceCenter(Vec2(704, 640));
	objectArray.emplace_back(penguinGO);

	Camera::Follow(penguinGO);			// Coloca a camera para seguir o Penguin

}

void StageState::Update(float dt){
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();
	
	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

	quitRequested = inputManager.QuitRequested();			// Seta o quitRequested ao fechar o jogo
	
	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
		backgroundMusic.Stop();
	}

	UpdateArray(dt);										// Faz o update de cada GameObject no objectArray

	std::vector<Collider*> colliders(objectArray.size(), nullptr);
	bool collidersArrayFilled = false;

	// Checa colisoes entre os Colliders dos GameObjects
	for (i = 0; i < objectArray.size() - 1; i++) {
		if (!collidersArrayFilled)
			colliders[i] = (Collider*)objectArray[i]->GetComponent("Collider");

		if (colliders[i]) {
			for (j = i + 1; j < objectArray.size(); j++) {
				if (!collidersArrayFilled)
					colliders[j] = (Collider*)objectArray[j]->GetComponent("Collider");

				if (colliders[j] && Collision::IsColliding(colliders[i]->box, colliders[j]->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg)) {
					// Notifica ambos os GameObjects que houve colisao
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
			collidersArrayFilled = true;
		}
	}

	// Checa se houve a morte de algum objeto
	for (i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;					// Ajuste da posicao  no index do vetor de objetos
		}
	}

	// Impede o movimento dos penguins
//	if (!(1408 - mapGO->box.x > penguinGO->box.x > 0 + mapGO->box.x))

		



	
	// Tela de GAME OVER
	if (!PenguinBody::player) {
		GameData::playerVictory = false;
		popRequested = true;

		// todo - pensar melhor em como mudar de tela apenas apos o termino da animacao de explosao
//		TimeToEndPlayerAnimation.Update(dt);
//		if (PenguinBody::secondsToSelfDestruction/*, selfDestructCount.Get() > secondsToSelfDestruct*/)
//		if (TimeToEndPlayerAnimation.Get() > secondsToEndPlayerAnimation)
			Game::GetInstance().Push(new EndState());
	}	// Tela de WIN
	else if (Alien::alienCount == 0) {
		GameData::playerVictory = true;
		popRequested = true;

		// todo - pensar melhor em como mudar de tela apenas apos o termino da animacao de explosao
//		TimeToEndAlienAnimation.Update(dt);
//		if(TimeToEndAlienAnimation.Get() > secondsToEndAlienAnimation)
			Game::GetInstance().Push(new EndState());
	}

}

StageState::~StageState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void StageState::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void StageState::Start() {
	LoadAssets();
	StartArray();					// Da Start em cada GameObject no objectArray
}

void StageState::Pause() {

}

void StageState::Resume() {

}
