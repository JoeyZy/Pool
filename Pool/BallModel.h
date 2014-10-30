#pragma once
#include <iostream>
#include "Model.h"
#include "MoveType.h"

class BallModel: public Model {
public:
	int radius;
	int getRadius();
	void setRadius(int radius);
	BallModel();
	~BallModel();
	void move(MoveType move);
};