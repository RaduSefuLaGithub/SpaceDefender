#pragma once
#include "gameobject.h"
#include "shape.h"

class Meteorite : public GameObject, public Circle {
public:
	Meteorite();

	void setx(int valx);
	void sety(int valy);
	void sethp(int valhp);
	int gethp();
};