#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#define Name "Game"
#define Width 1500
#define Height 1000
#define FrameDelay 25

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern bool SDL3Setup();

void SDL3Exit();

int main();