#include "Minion.h"
#include "Game.h"


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
	Minion::alienCenter = alienCenter;
	arc = arcOffsetDeg;
	
	// Carrega o Minion
	auto sprite = new Sprite(associated, "./assets/img/minion.png");
	auto randScale = (std::rand() % 51 + 100) / 100.0;
	sprite->SetScale(randScale, randScale);
	associated.AddComponent(sprite);

	Vec2 initialPos(RADIUS, 0);
	initialPos = initialPos.GetRotated(arcOffsetDeg);

	auto alienGO = alienCenter.lock();

	if (alienGO) {
		associated.box = alienGO->box.Center() + initialPos;
		associated.box.Centralize();
	}
	else {
		std::cout << "ERRO! Ponteiro para GameObject do Alien nulo!" << std::endl;
		associated.RequestDelete();
	}

}

void Minion::Update(float dt) {
	
	// Mantem o Minion em orbita
	auto alienGO = alienCenter.lock();
	
	if (alienGO) {
		Vec2 pos(RADIUS, 0);

		arc += ANGULAR_SPEED * dt;

		associated.angleDeg = (180 / PI)*arc;

		pos = pos.GetRotated(arc);
		associated.box = alienGO->box.Center() + pos;
		associated.box.Centralize();
	}
	else
		associated.RequestDelete();
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
	if (type == "Minion")
		return true;
	else
		return false;
}

void Minion::Shoot(Vec2 target) {
	// Carrega um Tiro
	auto bulletGO = new GameObject();
	bulletGO->box = associated.box.Center();

	auto bullet = new Bullet(*bulletGO, target.InclinacaoDaDiferenca(associated.box.Center()), BULLET_SPEED,
							 std::rand() % 11 + BULLET_MAX_DAMAGE - 10,	BULLET_MAX_DISTANCE, "./assets/img/minionbullet1.png");

	bulletGO->AddComponent(bullet);

	Game::GetInstance().GetState().AddObject(bulletGO);
}
