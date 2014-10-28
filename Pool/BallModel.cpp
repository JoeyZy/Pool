
#pragma once
#include <iostream>
#include "Model.h"
#include "MoveType.h"

class Ball: public Model
{
public:
	Ball() {
		x = 0;
		y = 0;
		radius = 5;
	}
	void move(MoveType move) {
		switch (move) {
		case LEFT:
			x-=10;
			break;
		case UP:
			y += 10;
			break;
		case RIGHT:
			x+=10;
			break;
		case DOWN:
			y-=10;
			break;
		}
	}
};
