#pragma once
#include <iostream>
#include "Model.h"

class BallModel: public Model {
public:
	float moveLeft;
	float moveUp;
	float moveRight;
	float moveDown;
	float stepLeft;
	float stepUp;
	float stepRight;
	float stepDown;
	int radius;
	float startSpeed;
	float coeff;
	float maxSpeed;
	int getRadius();
	void setRadius(int radius);
	BallModel();
	~BallModel();
	void move(MoveType move);
	void doListening();
	void correctSpeed();
};