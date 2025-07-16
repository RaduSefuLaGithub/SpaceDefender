#pragma once
#include <iostream>
class Shape {
public:
	virtual std::string getShape() = 0;
};

class Circle : public Shape {
protected:
	int x, y, r;
public:
	int getx();
	int gety();
	int getr();
	
	std::string getShape() override;
};

class Triangle : public Shape {
protected:
	int x[3], y[3];
public:
	int getx(int id);
	int gety(int id);

	std::string getShape() override;
};
