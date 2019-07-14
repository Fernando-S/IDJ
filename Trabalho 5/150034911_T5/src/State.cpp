#include "State.h"


State::State() {
	// Carrega a Musica e aperta o play
	music = *new Music("./assets/audio/stageState.ogg");
	music.Play();

	started = false;
	quitRequested = false;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::LoadAssets() {
	
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

	// Em roteiro, foi pedido para se carregar o Alien no costrutor da State,
	// mas nao vejo sentido nisso, pois temos LoadAssets()
	// Carrega o Alien
	auto alienGO = new GameObject();

	auto alien = new Alien(*alienGO, 3);
	alienGO->box = {512, 300};
	alienGO->box.Centralize();

	alienGO->AddComponent(alien);

	objectArray.emplace_back(alienGO);
	
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

	// Faz o update de cada objeto no vetor
	for (unsigned i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	// Checa se houve a morte de algum objeto
	for ( unsigned i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;					// Ajuste da posicao do vetor de objetos
		}
	}
}

void State::Render() {
	for (auto &gameObjects : objectArray) {
		gameObjects->Render();					// Renderiza cada gameObject
	}
}

State::~State() {
	objectArray.clear();
}

void State::Start() {
	LoadAssets();							// Carrega os assets

	for (auto &gameObjects : objectArray) {
		gameObjects->Start();				// Chama Start de cada gameObject carregado
	}

	started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
	
	std::shared_ptr<GameObject> sharedGO(go);

	objectArray.push_back(sharedGO);

	if (started)
		go->Start();				// Chama Start do gameObject adicionado se started = true 

	return std::weak_ptr<GameObject>(sharedGO);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
	for (auto& it : objectArray) {
		if (it.get() == go)
			return std::weak_ptr<GameObject>(it);		// Retorna o ponteiro para o gameObject se o encontrar
	}

	return std::weak_ptr<GameObject>();		// Retorna um ponteiro vazio caso nao encontre o gameObject
}