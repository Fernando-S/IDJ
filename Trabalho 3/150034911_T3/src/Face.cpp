#include "Face.h"


Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
}

void Face::Damage(int damage) {

	hitpoints = hitpoints - damage;

	if (hitpoints <= 0) {
		this->soundComponent = (Sound*)associated.GetComponent("Sound");
		if (soundComponent && !soundComponent->IsPlaying()) {
			soundComponent->Play();
			Update(1);
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
	if (DeadAlready()) {
		if (soundComponent && !soundComponent->IsPlaying())						// objeto so deve morrer se o som de explosao ja foi tocado
			associated.RequestDelete();
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