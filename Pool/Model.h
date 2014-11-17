#pragma once

#include "MoveType.h"
//#include "Controller.h"
#include "string"
using namespace std;

class Controller;

class Model
{
protected:
	Controller *controller;
	float x, y, speedX, speedY, friction;
	string type;
public:
	int areaWidth;
	int areaHeight;
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	int getSpeedX();
	void setSpeedX(int speedX);
	string getType();
	void setType(string type);
	Controller* getController();
	void setController(Controller* controller);
	virtual void doListening();
	virtual void move(MoveType move) = 0;
};

