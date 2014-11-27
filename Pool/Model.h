#pragma once
#include "MoveType.h"
#include "string"
using namespace std;

class Controller;
class View;

class Model
{
protected:
	Controller *controller;
	View* view;
	float x, y, speedX, speedY, friction;
	string type;
public:
//	CRITICAL_SECTION critical;
	static int id;
	int areaWidth;
	int areaHeight;
	volatile bool isModelling;
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
	View* getView();
	void setView(View* view);
	virtual void listen() = 0;
	virtual void move(MoveType move) = 0;
};

