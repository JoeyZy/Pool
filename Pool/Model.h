#pragma once
#include "MoveType.h"
#include "string"
using namespace std;

class Model
{
protected:
	int x, y;
	string type;
public:
	int getX();
	void setX(int x);
	int getY();
	void setY();
	string getType();
	void setType(string type);
	virtual void move(MoveType move) = 0;
};

