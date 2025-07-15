#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
using std::string, std::cout, std::endl, std::abs, std::sqrt, std::min, std::max;
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
// g++ -I "C:/SDL3-3.2.16/x86_64-w64-mingw32/include" -I "C:/SDL3_image-3.2.4/x86_64-w64-mingw32/include" -L "C:/SDL3-3.2.16/x86_64-w64-mingw32/lib" -L "C:/SDL3_image-3.2.4/x86_64-w64-mingw32/lib" main.cpp -lSDL3 -lSDL3_image -o game.exe
#define Name "Game"
#define Width 1500
#define Height 1000
#define FrameDelay 25

SDL_Window *window;
SDL_Renderer *renderer;
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
SDL_Event event;



double PointSegmentDistance(int px, int py, int x0, int y0, int x1, int y1) {
    int ABx = x1-x0, ABy = y1-y0, APx = px-x0, APy = py-y0;
	int abSquared = ABx*ABx + ABy*ABy;

    // Handle zero-length segment (if endpoints are the same)
    if (abSquared == 0) {
	int dx = px - x0;
	int dy = py - y0;
	return sqrt(dx*dx + dy*dy);
    }

    int dot = APx*ABx + APy*ABy;
    double t = static_cast<double>(dot) / abSquared;

    // Clamp t between 0 and 1
    t = max(0.0, min(1.0, t));

    double ClosestX = x0 + t * ABx, ClosestY = y0 + t * ABy;
    double dx = px - ClosestX, dy = py - ClosestY;

    return sqrt(dx*dx + dy*dy);
}

int MapSize = 1;
class Shape {
public:
	virtual string getShape() = 0;
};

class Circle : public Shape {
protected:
	int x, y, r;
public:
	int getx() { return x; }
	int gety() { return y; }
	int getr() { return r; }
	
	string getShape() override {
		return "circle";
	}
};

class Triangle : public Shape {
protected:
	int x[3], y[3];
public:
	int getx(int id) { return x[id]; }
	int gety(int id) { return y[id]; }

	string getShape() override {
		return "triangle";
	}
};

class GameObject {
public:
	SDL_FRect spriteRect;
    SDL_Texture *sprite;
protected:
	int speed;
    int hp;
    int dmg;

public:
    virtual void takeDamage(int amount) {
		hp -= amount;
		if (hp <= 0) die();
    }
private:
	virtual void die() = 0;
};

class Meteorite : public GameObject, public Circle {
public:
	Meteorite() {
		hp = 0;
	}

	void setx(int valx) { x = valx; }
	void sety(int valy) { y = valy; }
	void sethp(int valhp) { hp = valhp; }
	int gethp() { return hp; }
};


class Bullet : public GameObject, public Triangle {
public:
	void spawn(int vx, int vy, int vw, int vh, int vspeed, int vhp, int vdmg) {
		spriteRect.x = vx; spriteRect.y = vy; spriteRect.w = vw; spriteRect.h = vh; speed = vspeed; hp = vhp; dmg = vdmg;
	}

	bool isOutBounds() {
		if(spriteRect.y <= -spriteRect.h) return true;
		if(spriteRect.y >= Height+spriteRect.h) return true;
		if(spriteRect.x <= -spriteRect.w) return true;
		if(spriteRect.x >= Width+spriteRect.w) return true;
		return false;
	}

	int getspeed() { return speed; }
	int gethp() { return hp; }

private:
	void die() override {
	}
};

class Bullet_v1 : public Bullet {
public:
	Bullet_v1() {
		sprite = IMG_LoadTexture(renderer, "Sprites/Bullet_v1.png");
		SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
		hp = 0;
		x[0] = 0; y[0] = 0;
		x[1] = spriteRect.w-1; y[0] = 0;
		x[2] = spriteRect.w/2; y[1] = spriteRect.h/2;
	}
};

class SpaceShip : public GameObject {
protected:
    int gunx, guny;
public:
	void spawn(int vx, int vy, int vspeed, int vhp, int vdmg) {
	    spriteRect.x = vx; spriteRect.y = vy; speed = vspeed; hp = vhp; dmg = vdmg;
	}

	int getspeed() { return speed; }

private:
	int firerate = 1000;
	int lastshoot = -210000;
public:
	static constexpr int MaxBullets = 50;
	Bullet_v1 bullets[MaxBullets];
    void shoot() {
		if (SDL_GetTicks()-lastshoot >= firerate) {
			int i=0;
			while(i<MaxBullets and bullets[i].gethp()!=0) 
				i++;
			if (i<MaxBullets) bullets[i].spawn(spriteRect.x+gunx-spriteRect.w/20*6/2, spriteRect.y+guny-spriteRect.h/20*6/2, spriteRect.w/20*6, spriteRect.h/20*6, speed*3, 1, dmg);
			lastshoot = SDL_GetTicks();
		}
	}
private:
	void die() override {
	}
};

class Player : public SpaceShip, public Triangle {
public:
    Player() {
		spriteRect.w = 20*5;
		spriteRect.h = 20*5;
		sprite = IMG_LoadTexture(renderer, "Sprites/Fighter_v1.png");
		SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
		x[0] = spriteRect.w/2; y[0] = 0;
		x[1] = 0; y[0] = spriteRect.h-1;
		x[2] = spriteRect.w-1; y[1] = spriteRect.h-1;
		gunx = spriteRect.w/2; guny = -spriteRect.h/5;
    }
};


bool CollisionCheck(GameObject *go1, GameObject *go2) {
    Shape *s1 = dynamic_cast<Shape*>(go1);
    Shape *s2 = dynamic_cast<Shape*>(go2);
    if(!s1) { cout << "s1 is not shape" << endl; return 0;}
    if(!s2) { cout << "s2 is not shape" << endl; return 0;}
    if(s1->getShape() == "triangle" and s2->getShape() == "circle") {
	Shape *aux;
	aux = s1;
	s1 = s2;
	s2 = aux;
    }
    if(s1->getShape() == "circle" && s2->getShape() == "circle") {
	Circle *c1 = dynamic_cast<Circle*>(s1);
	Circle *c2 = dynamic_cast<Circle*>(s2);
	if(!c1 || !c2)
	    return 0;
	int xd = abs(c1->getx() - c2->getx());
	int yd = abs(c1->gety() - c2->gety());
	double dist = sqrt(xd*xd + yd*yd);
	if(dist<=c1->getr() + c2->getr())
	    return 1;
    }
    else if(s1->getShape() == "circle" && s2->getShape() == "triangle") {
	Circle *c1 = dynamic_cast<Circle*>(s1);
	Triangle *t2 = dynamic_cast<Triangle*>(s2);
	if(!c1 || !t2)
		return 0;
	int cx = c1->getx(), cy = c1->gety(), cr = c1->getr();
	int x[3], y[3], d[3];
	for(int i=0; i<3; i++) {
		x[i] = t2->getx(i);
		y[i] = t2->gety(i);
	}
	d[0] = (x[0] - x[1])*(cy - y[1]) - (y[0] - y[1])*(cx - x[1]);
	d[1] = (x[1] - x[2])*(cy - y[2]) - (y[1] - y[2])*(cx - x[2]);
	d[2] = (x[2] - x[0])*(cy - y[0]) - (y[2] - y[0])*(cx - x[0]);
	if(d[0]<0 && d[1]<0 && d[2]<0)
		return 1;
	if(d[0]>0 && d[1]>0 && d[2]>0)
		return 1;
	if((double)PointSegmentDistance(cx, cy, x[0], y[0], x[1], y[1]) <= cr)
		return 1;
	if((double)PointSegmentDistance(cx, cy, x[1], y[1], x[2], y[2]) <= cr)
		return 1;
	if((double)PointSegmentDistance(cx, cy, x[2], y[2], x[0], y[0]) <= cr)
		return 1;

	int xd, yd;
	double dist;
	for(int i=0; i<3; i++) {
	    xd = abs(cx - x[i]);
	    yd = abs(cy - y[i]);
	    dist = sqrt(xd*xd + yd*yd);
	    if(dist <= cr)
		return 1;
	}
    }
    else if(s1->getShape() == "triangle" && s2->getShape() == "triangle") {
	Triangle *t1 = dynamic_cast<Triangle*>(s1);
	Triangle *t2 = dynamic_cast<Triangle*>(s2);
	if(!t1 || !t2)
	    return 0;

	return 1;
    }
    return 0;
}

int main() {

	if(!SDL3Setup())
	    return -69;

	Player player;
	player.spawn(500, 500, 15, 100, 5);

	const int W=1,A=2,S=4,D=8,SPC=16;
	int keysPressed=0, keysCopy;
	bool running = true;
	while(running) {
		SDL_RenderClear(renderer);

		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_EVENT_QUIT)
				running = false;
			if(event.type == SDL_EVENT_KEY_DOWN) {
				if(event.key.scancode == SDL_SCANCODE_ESCAPE) running = false;
				else if(event.key.key == SDLK_W && !(keysPressed&W)) keysPressed += W;
				else if(event.key.key == SDLK_A && !(keysPressed&A)) keysPressed += A;
				else if(event.key.key == SDLK_S && !(keysPressed&S)) keysPressed += S;
				else if(event.key.key == SDLK_D && !(keysPressed&D)) keysPressed += D;
				else if(event.key.key == SDLK_SPACE && !(keysPressed&SPC)) keysPressed += SPC;
			}
			if(event.type == SDL_EVENT_KEY_UP) {
				if(event.key.key == SDLK_W && (keysPressed&W)) keysPressed -= W;
				else if(event.key.key == SDLK_A && (keysPressed&A)) keysPressed -= A;
				else if(event.key.key == SDLK_S && (keysPressed&S)) keysPressed -= S;
				else if(event.key.key == SDLK_D && (keysPressed&D)) keysPressed -= D;
				else if(event.key.key == SDLK_SPACE && (keysPressed&SPC)) keysPressed -= SPC;
			}
		}
		keysCopy = keysPressed;
		// if((keysCopy&(W+S))==W+S) keysCopy -= W+S;
		// if((keysCopy&(A+D))==A+D) keysCopy -= A+D;
		// if((keysCopy&(W+A))==W+A) { player.spriteRect.x -= player.getspeed()/2; player.spriteRect.y -= player.getspeed()/2; }
		// else if((keysCopy&(W+D))==W+D) { player.spriteRect.x += player.getspeed()/2; player.spriteRect.y -= player.getspeed()/2; }
		// else if((keysCopy&(S+A))==S+A) { player.spriteRect.x -= player.getspeed()/2; player.spriteRect.y += player.getspeed()/2; }
		// else if((keysCopy&(S+D))==S+D) { player.spriteRect.x += player.getspeed()/2; player.spriteRect.y += player.getspeed()/2; }
		if((keysCopy&W)==W) player.spriteRect.y -= player.getspeed();
		if((keysCopy&A)==A) player.spriteRect.x -= player.getspeed();
		if((keysCopy&S)==S) player.spriteRect.y += player.getspeed();
		if((keysCopy&D)==D) player.spriteRect.x += player.getspeed();

		for(int i=0; i<player.MaxBullets; i++)
			if(player.bullets[i].gethp()) {
				player.bullets[i].spriteRect.y -= player.bullets[i].getspeed();
				if(player.bullets[i].isOutBounds()) player.bullets[i].spawn(0, 0, 0, 0, 0, 0, 0);
			}
		if((keysCopy&SPC)==SPC) player.shoot();

		SDL_RenderTexture(renderer, player.sprite, NULL, &player.spriteRect);
		for(int i=0; i<player.MaxBullets; i++)
			if(player.bullets[i].gethp())
				SDL_RenderTexture(renderer, player.bullets[i].sprite, NULL, &player.bullets[i].spriteRect);
		SDL_RenderPresent(renderer);
		SDL_Delay(40);
	}

	SDL3Exit();

	return 0;
}