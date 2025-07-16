#include "gameobject.h"

void GameObject::takeDamage(int amount) {
		hp -= amount;
		if (hp <= 0) die();
}