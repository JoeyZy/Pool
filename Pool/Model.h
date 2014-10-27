#pragma once
#include "MoveType.h"

class Model
{
	int x, y, radius;
public:
	int getX() {
		return x;
	}
	void setX(int x) {
		this->x=x;
	}
	int getY() {
		return y;
	}
	void setY() {
		this->y=y;
	}
	int getRadius() {
		return radius;
	}
	void setRadius() {
		this->radius=radius;
	}
	virtual void move(MoveType move) = 0;
	Model();
	~Model();
};

