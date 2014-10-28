#pragma once
#include "MoveType.h"

class Model
{
protected:
	int x, y, radius;
public:
	int getX();
	void setX(int x);
	int getY();
	void setY();
	int getRadius();
	void setRadius();
	virtual void move(MoveType move) = 0;
};

