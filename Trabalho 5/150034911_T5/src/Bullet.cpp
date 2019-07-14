#include "Bullet.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const char* sprite) : Component(associated) {
	Bullet::speed = {speed, 0};
	Bullet::distanceLeft = maxDistance;
	Bullet::damage = damage;
	Bullet::speedMagnitude = speed;

	associated.AddComponent(new Sprite(associated, sprite));
	associated.angleDeg = (180 / PI)*angle;				// Corrige o angulo do Tiro
	this->speed = this->speed.GetRotated(angle);		// Corrige a direcao do Tiro
}

void Bullet::Update(float dt) {
	distanceLeft -= speedMagnitude * dt;

	if (distanceLeft <= 0)
		associated.RequestDelete();
	else
		associated.box += speed * dt;
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
	if (type == "Bullet")
		return true;
	else
		return false;
}

int Bullet::GetDamage() {
	return damage;
}
