#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
//#include "main.h"
//#include "spaceship.h"
// g++ -I "C:/SDL3-3.2.16/x86_64-w64-mingw32/include" -I "C:/SDL3_image-3.2.4/x86_64-w64-mingw32/include" -L "C:/SDL3-3.2.16/x86_64-w64-mingw32/lib" -L "C:/SDL3_image-3.2.4/x86_64-w64-mingw32/lib" Scripts/*.cpp -lSDL3 -lSDL3_image -o game.exe
#define Name "Game"
#define Width 1500
#define Height 1000
#define FrameDelay 25
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
bool SDL3Setup() {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Error Initiallising: %s \n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(Name, Width, Height, 0);
	if(!window) {
		fprintf(stderr, "Window Pointer is NULL: %s \n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if(!renderer) {
		fprintf(stderr, "Renderer Pointer is NULL: %s \n", SDL_GetError());
		return false;
	}

	return true;
}

void SDL3Exit() {
	if(renderer)
		SDL_DestroyRenderer(renderer);
	renderer = NULL;
	
	if(window)
		SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main() {

	if(!SDL3Setup())
		return -69;

	// Player player;
	// player.spawn(500, 500, 15, 100, 5);

	printf("bruh help");
	// const int W=1,A=2,S=4,D=8,SPC=16;
	// int keysPressed=0, keysCopy;
	// bool running = true;
	// while(running) {
	// 	SDL_RenderClear(renderer);

	// 	while(SDL_PollEvent(&event)) {
	// 		if(event.type == SDL_EVENT_QUIT)
	// 			running = false;
	// 		if(event.type == SDL_EVENT_KEY_DOWN) {
	// 			if(event.key.scancode == SDL_SCANCODE_ESCAPE) running = false;
	// 			else if(event.key.key == SDLK_W && !(keysPressed&W)) keysPressed += W;
	// 			else if(event.key.key == SDLK_A && !(keysPressed&A)) keysPressed += A;
	// 			else if(event.key.key == SDLK_S && !(keysPressed&S)) keysPressed += S;
	// 			else if(event.key.key == SDLK_D && !(keysPressed&D)) keysPressed += D;
	// 			else if(event.key.key == SDLK_SPACE && !(keysPressed&SPC)) keysPressed += SPC;
	// 		}
	// 		if(event.type == SDL_EVENT_KEY_UP) {
	// 			if(event.key.key == SDLK_W && (keysPressed&W)) keysPressed -= W;
	// 			else if(event.key.key == SDLK_A && (keysPressed&A)) keysPressed -= A;
	// 			else if(event.key.key == SDLK_S && (keysPressed&S)) keysPressed -= S;
	// 			else if(event.key.key == SDLK_D && (keysPressed&D)) keysPressed -= D;
	// 			else if(event.key.key == SDLK_SPACE && (keysPressed&SPC)) keysPressed -= SPC;
	// 		}
	// 	}
	// 	keysCopy = keysPressed;
	// 	// if((keysCopy&(W+S))==W+S) keysCopy -= W+S;
	// 	// if((keysCopy&(A+D))==A+D) keysCopy -= A+D;
	// 	// if((keysCopy&(W+A))==W+A) { player.spriteRect.x -= player.getspeed()/2; player.spriteRect.y -= player.getspeed()/2; }
	// 	// else if((keysCopy&(W+D))==W+D) { player.spriteRect.x += player.getspeed()/2; player.spriteRect.y -= player.getspeed()/2; }
	// 	// else if((keysCopy&(S+A))==S+A) { player.spriteRect.x -= player.getspeed()/2; player.spriteRect.y += player.getspeed()/2; }
	// 	// else if((keysCopy&(S+D))==S+D) { player.spriteRect.x += player.getspeed()/2; player.spriteRect.y += player.getspeed()/2; }
	// 	if((keysCopy&W)==W) player.spriteRect.y -= player.getspeed();
	// 	if((keysCopy&A)==A) player.spriteRect.x -= player.getspeed();
	// 	if((keysCopy&S)==S) player.spriteRect.y += player.getspeed();
	// 	if((keysCopy&D)==D) player.spriteRect.x += player.getspeed();

	// 	for(int i=0; i<player.MaxBullets; i++)
	// 		if(player.bullets[i].gethp()) {
	// 			player.bullets[i].spriteRect.y -= player.bullets[i].getspeed();
	// 			if(player.bullets[i].isOutBounds()) player.bullets[i].spawn(0, 0, 0, 0, 0, 0, 0);
	// 		}
	// 	if((keysCopy&SPC)==SPC) player.shoot();

	// 	SDL_RenderTexture(renderer, player.sprite, NULL, &player.spriteRect);
	// 	for(int i=0; i<player.MaxBullets; i++)
	// 		if(player.bullets[i].gethp())
	// 			SDL_RenderTexture(renderer, player.bullets[i].sprite, NULL, &player.bullets[i].spriteRect);
	// 	SDL_RenderPresent(renderer);
	// 	SDL_Delay(40);
	// }

	SDL3Exit();

	return 0;
}