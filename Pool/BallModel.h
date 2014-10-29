#pragma once
#include <iostream>
#include "Model.h"
#include "MoveType.h"

class BallModel: public Model {
public:
	BallModel();
	~BallModel();
	void move(MoveType move);
};