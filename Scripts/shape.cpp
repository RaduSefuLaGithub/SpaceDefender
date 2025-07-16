#include "shape.h"

int Circle::getx() { return x; }
int Circle::gety() { return y; }
int Circle::getr() { return r; }
	
std::string Circle::getShape() {
	return "circle";
}



int Triangle::getx(int id) { return x[id]; }
int Triangle::gety(int id) { return y[id]; }

std::string Triangle::getShape() {
	return "triangle";
}
