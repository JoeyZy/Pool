#pragma once
#include "MoveType.h"
#include "string"
using namespace std;

class Model
{
protected:
	int x, y, radius;
	string type;
public:
	int getX();
	void setX(int x);
	int getY();
	void setY();
	int getRadius();
	void setRadius();
	string getType();
	void setType(string type);
	virtual void move(MoveType move) = 0;
};

