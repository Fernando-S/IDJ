#include "Component.h"


Component::Component(GameObject& associated) : associated(associated) {

}

Component::~Component() {

}


void Component::Update(float dt) {

}

void Component::Render() {

}

bool Component::Is(std::string type) {
	if (type == "Component")
		return true;
	else
		return false;
}