#pragma once
#include <iostream>
#include "Model.h"


class BallModel: public Model {
public:
	BallModel(float x = 0.0, float y = 0.0);
	double frames;
	float m;
	float speedX;
	float speedY;
	int radius;
	float startSpeed;
	float maxSpeed;
	int getRadius();
	void setRadius(int radius);
	void move(MoveType move);
	void increaseSpeed(float &speed1, float &speed2);
	void listen();
	void doListening();
	void correctSpeed();
};