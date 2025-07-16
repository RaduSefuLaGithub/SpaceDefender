#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "spaceship.h"
#include "main.h"

void SpaceShip::spawn(int vx, int vy, int vspeed, int vhp, int vdmg) {
	spriteRect.x = vx; spriteRect.y = vy; speed = vspeed; hp = vhp; dmg = vdmg;
}

int SpaceShip::getspeed() { return speed; }

void SpaceShip::shoot() {
	if (SDL_GetTicks()-lastshoot >= firerate) {
		int i=0;
		while(i<MaxBullets and bullets[i].gethp()!=0) 
			i++;
		if (i<MaxBullets) bullets[i].spawn(spriteRect.x+gunx-spriteRect.w/20*6/2, spriteRect.y+guny-spriteRect.h/20*6/2, spriteRect.w/20*6, spriteRect.h/20*6, speed*3, 1, dmg);
		lastshoot = SDL_GetTicks();
	}
}

void SpaceShip::die() {}



Player::Player() {
	spriteRect.w = 20*5;
	spriteRect.h = 20*5;
	sprite = IMG_LoadTexture(renderer, "Sprites/Fighter_v1.png");
	SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
	x[0] = spriteRect.w/2; y[0] = 0;
	x[1] = 0; y[0] = spriteRect.h-1;
	x[2] = spriteRect.w-1; y[1] = spriteRect.h-1;
	gunx = spriteRect.w/2; guny = -spriteRect.h/5;
}