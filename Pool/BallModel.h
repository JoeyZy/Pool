#pragma once
#include <iostream>
#include "Model.h"

class BallModel: public Model {
public:
	Model* passiveBall;
	void setPassiveBall(Model* model);
	Model* getPassiveBall();
	float m;
	float stepLeft;
	float stepUp;
	float stepRight;
	float stepDown;
	int radius;
	float startSpeed;
	float maxSpeed;
	int getRadius();
	void setRadius(int radius);
	BallModel();
	~BallModel();
	void move(MoveType move);
	void listen();
	void doListening();
	void correctSpeed();
};