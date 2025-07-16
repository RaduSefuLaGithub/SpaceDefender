#pragma once
#include "gameobject.h"

double PointSegmentDistance(int px, int py, int x0, int y0, int x1, int y1);

bool CollisionCheck(GameObject *go1, GameObject *go2);