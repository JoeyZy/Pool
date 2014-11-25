#pragma once
#include <iostream>
#include "Model.h"

class BallModel: public Model {
public:
	double frames;
	float m;
//	float stepLeft;
	float stepUp;
	float stepRight;
//	float stepDown;
	int radius;
	float startSpeed;
	float maxSpeed;
	int getRadius();
	void setRadius(int radius);
	BallModel();
	~BallModel();
	void move(MoveType move);
	void increaseSpeed(float &speed1, float &speed2);
	void listen();
	void doListening();
	void correctSpeed();
};