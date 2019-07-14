#include "State.h"


State::State() {
	started = false;
	quitRequested = false;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::LoadAssets() {

	// Carrega a Musica e aperta o play
	music = *new Music("./assets/audio/stageState.ogg");
	music.Play();


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


	// Carrega o Alien com 3 minions
	auto alienGO = new GameObject();

	auto alien = new Alien(*alienGO, 3);
	alienGO->box = {512, 300};
	alienGO->box.Centralize();

	alienGO->AddComponent(alien);
	objectArray.emplace_back(alienGO);
	
	
	// Carrega o Penguin
	// Novamente, foi pedido para fazer isso no construtor de State() e continuo nao vendo sentido,
	// uma vez que temos LoadAssets
	auto penguinGO = new GameObject();
	auto penguin = new PenguinBody(*penguinGO);

	penguinGO->AddComponent(penguin);
	penguinGO->box.PlaceCenter(Vec2(704, 640));
	objectArray.emplace_back(penguinGO);

	Camera::Follow(penguinGO);			// Coloca a camera para seguir o Penguin

}

void State::Update(float dt){
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();
	
	// Faz o update na camera e na box do mapa
	Camera::Update(dt);
	
	// Checa se foi solicitada a saida do jogo
	if (inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested())
		quitRequested = true;
	else
		quitRequested = false;
	
	// Faz o update de cada GameObject
	for (i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

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
	unsigned i;
	LoadAssets();							// Carrega os assets

	for (i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get())
			objectArray[i]->Start();				// Chama Start de cada gameObject carregado se existirem
		else
			std::cout << "ERROR: No GameObject inside objectArray" << std::endl;	// Mostra uma msg de erro caso nao existam
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