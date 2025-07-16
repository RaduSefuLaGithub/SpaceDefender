#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "bullet.h"
#include "main.h"

void Bullet::spawn(int vx, int vy, int vw, int vh, int vspeed, int vhp, int vdmg) {
	spriteRect.x = vx; spriteRect.y = vy; spriteRect.w = vw; spriteRect.h = vh; speed = vspeed; hp = vhp; dmg = vdmg;
}

bool Bullet::isOutBounds() {
	if(spriteRect.y <= -spriteRect.h) return true;
	if(spriteRect.y >= Height+spriteRect.h) return true;
	if(spriteRect.x <= -spriteRect.w) return true;
	if(spriteRect.x >= Width+spriteRect.w) return true;
	return false;
}

int Bullet::getspeed() { return speed; }
int Bullet::gethp() { return hp; }

void Bullet::die() {}

Bullet_v1::Bullet_v1() {
	sprite = IMG_LoadTexture(renderer, "Sprites/Bullet_v1.png");
	SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
	hp = 0;
	x[0] = 0; y[0] = 0;
	x[1] = spriteRect.w-1; y[0] = 0;
	x[2] = spriteRect.w/2; y[1] = spriteRect.h/2;
}