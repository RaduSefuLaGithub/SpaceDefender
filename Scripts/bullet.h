#pragma once
#include "gameobject.h"
#include "shape.h"

class Bullet : public GameObject, public Triangle {
public:
	void spawn(int vx, int vy, int vw, int vh, int vspeed, int vhp, int vdmg);

	bool isOutBounds();

	int getspeed();
	int gethp();

private:
	void die() override;
};

class Bullet_v1 : public Bullet {
public:
	Bullet_v1();
};