#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class GameObject {
public:
	SDL_FRect spriteRect;
    SDL_Texture *sprite;
protected:
	int speed;
    int hp;
    int dmg;

public:
    virtual void takeDamage(int amount);
private:
	virtual void die() = 0;
};