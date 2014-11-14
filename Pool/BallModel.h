#pragma once
#include <iostream>
#include "Model.h"

class BallModel: public Model {
public:
	int radius;
	int defaultSpeed;
	int getRadius();
	void setRadius(int radius);
	BallModel();
	~BallModel();
	void move(MoveType move);
};