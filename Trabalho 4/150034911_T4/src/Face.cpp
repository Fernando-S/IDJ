#include "Face.h"


Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
}

void Face::Damage(int damage) {

	hitpoints = hitpoints - damage;

	if (hitpoints <= 0) {
		this->soundComponent = (Sound*)associated.GetComponent("Sound");
		if (soundComponent) {
			soundComponent->Play();
		}
		associated.RemoveComponent(associated.GetComponent("Sprite"));
	}
}

bool Face::DeadAlready() {
	if (hitpoints <= 0)
		return true;
	else
		return false;
}

void Face::Update(float dt) {
	if(Camera::isMoving){
		this->associated.box.x += Camera::speed.x;
		this->associated.box.y += Camera::speed.y;
	};

	if (DeadAlready()) {
		if (soundComponent && !soundComponent->IsPlaying())						// objeto so deve morrer se o som de explosao ja foi tocado
			associated.RequestDelete();
	}
	else {
		auto inputManager = InputManager::GetInstance();

		// todo - ta matando tudo q clica, ignorando layers por enquanto
		if (inputManager.MousePress(LEFT_MOUSE_BUTTON) &&
			associated.box.Contains({ (float)inputManager.GetMouseX(), (float)inputManager.GetMouseY()})) {
			Damage(std::rand() % 10 + 10);
		}
	}
}

void Face::Render() {

}

bool Face::Is(std::string type) {
	if (type == "Face")
		return true;
	else
		return false;
}