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
	int x, y, speedX, speedY, friction;
	string type;
public:

	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getSpeedX();
	void setSpeedX(int speedX);
	string getType();
	void setType(string type);
	Controller* getController();
	void setController(Controller* controller);
	virtual void move(MoveType move) = 0;
	void doListening();
	void correctSpeed(int &speed);
};

