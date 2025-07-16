#include "meteorite.h"

Meteorite::Meteorite() {
		hp = 0;
}

void Meteorite::setx(int valx) { x = valx; }
void Meteorite::sety(int valy) { y = valy; }
void Meteorite::sethp(int valhp) { hp = valhp; }
int Meteorite::gethp() { return hp; }
