#include <iostream>
#include <cmath>
#include "gameobject.h"
#include "shape.h"

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
    t = std::max(0.0, std::min(1.0, t));

    double ClosestX = x0 + t * ABx, ClosestY = y0 + t * ABy;
    double dx = px - ClosestX, dy = py - ClosestY;

    return sqrt(dx*dx + dy*dy);
}

bool CollisionCheck(GameObject *go1, GameObject *go2) {
    Shape *s1 = dynamic_cast<Shape*>(go1);
    Shape *s2 = dynamic_cast<Shape*>(go2);
    if(!s1) { printf("s1 is not shape\n"); return 0;}
    if(!s2) { printf("s2 is not shape\n"); return 0;}
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