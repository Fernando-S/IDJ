#include "Alien.h"
#include "Game.h"


Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	speed = {0, 0};
	hp = ALIEN_MAX_HP;
	Minions = nMinions;
	associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
}


Alien::~Alien() {
	minionArray.clear();			// Esvazia o array com minions
}

void Alien::Start() {
	GameObject* minionGO = nullptr;
	Minion* minion = nullptr;
	double minionArc = 0;
	int i;

	// Carrega os minions
	for (i = 0; i < Minions; i++) {	
		minionGO = new GameObject();
		minionArc = i * 2 * PI / Minions;
		minion = new Minion(*minionGO, Game::GetInstance().GetState().GetObjectPtr(&associated), (float)minionArc);

		minionGO->AddComponent(minion);

		minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGO));
	}
}

void Alien::Update(float dt) {
	// Pega as coordenadas do mouse
	auto inputManager = InputManager::GetInstance();
	auto mouseX = inputManager.GetMouseX();
	auto mouseY = inputManager.GetMouseY();
	int i;

	if (hp <= 0) 
		associated.RequestDelete();				// Remove o Alien se ele nao tem mais vida
	else{
		associated.angleDeg += ALIEN__ANGULAR_SPEED * dt;

		if (inputManager.MousePress(LEFT_MOUSE_BUTTON))			// Atira caso o botao esquerdo do mouse seja apertado
			taskQueue.push(Action(Action::SHOOT, mouseX + Camera::pos.x, mouseY + Camera::pos.y));
		else if (inputManager.MousePress(RIGHT_MOUSE_BUTTON))	// Anda caso o botao direito do mouse seja apertado
			taskQueue.push(Action(Action::MOVE, mouseX + Camera::pos.x, mouseY + Camera::pos.y));

		if (!taskQueue.empty()) {
			auto task = taskQueue.front();

			// Se a distancia eh minima, coloca o Alien imediatamente la e a acao eh dada como realizada
			if (task.type == Action::MOVE && task.pos.Distancia(associated.box.Center()) <= ALIEN_SPEED * dt) {
				associated.box = task.pos;
				associated.box.Centralize();
				speed = {0, 0};
				taskQueue.pop();
			}
			else if (task.type == Action::MOVE) {			// Movimenta o Alien
				if (speed.x == 0 && speed.y == 0) {			// O Alien soh se move se estiver parado
					speed = {ALIEN_SPEED*dt, 0};			// Alien ganha velocidade
					// Coloca o movimento do Alien na direcao certa
					speed = speed.GetRotated(task.pos.InclinacaoDaDiferenca(associated.box.Center()));
				}
				associated.box += speed;;
			}
			else if (task.type == Action::SHOOT) {			// Tiro
				if (Minions > 0) {
					auto closestMinionGO = minionArray[0].lock();
					auto minionGO = closestMinionGO;

					for (i = 1; i < Minions; i++) {
						minionGO = minionArray[i].lock();
						
						if (closestMinionGO.get() && minionGO.get()) {		// verifica se os dois shared_ptrs estao populados
							if (task.pos.Distancia({ minionGO->box.x,minionGO->box.y }) <
								task.pos.Distancia({ closestMinionGO->box.x,closestMinionGO->box.y }))
								closestMinionGO = minionGO;					// Se ha algum minion mais perto, eh ele que deve atirar
							else
								closestMinionGO = closestMinionGO;			// Se nao, mantem-se o mesmo atirador
						}
					}

					auto closestMinion = (Minion*)closestMinionGO->GetComponent("Minion");
					closestMinion->Shoot(task.pos);
				}
				taskQueue.pop();
			}
		}
	}

	
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
	if (type == "Minion")
		return true;
	else
		return false;
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) {
	this->type = type;
	pos = {x,y};
}
