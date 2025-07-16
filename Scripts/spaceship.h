#pragma once
#include "gameobject.h"
#include "shape.h"
#include "bullet.h"

class SpaceShip : public GameObject {
protected:
    int gunx, guny;
public:
	void spawn(int vx, int vy, int vspeed, int vhp, int vdmg);
	int getspeed();

private:
	int firerate = 1000;
	int lastshoot = -210000;
public:
	static constexpr int MaxBullets = 50;
	Bullet_v1 bullets[MaxBullets];
    void shoot();
private:
	void die() override;
};

class Player : public SpaceShip, public Triangle {
public:
    Player();
};