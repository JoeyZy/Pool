#include "BallModel.h"

	BallModel::BallModel() {
		x = 0;
		y = 0;
		radius = 5;
		type = "Ball";
	}
	void BallModel::move(MoveType move) {
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

