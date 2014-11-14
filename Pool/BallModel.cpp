#include "BallModel.h"
#include "Controller.h"
#include <thread>

BallModel::BallModel() {
	x = 0;
	y = 0;
	speedX = 0;
	speedY = 0;
	friction = 1;
	radius = 5;
	type = "Ball";
	defaultSpeed = 30;
}
int BallModel::getRadius(){
	return radius;
}
void BallModel::setRadius(int radius) {
	this->radius = radius;
}

void BallModel::move(MoveType move) {

	switch (move) {
	case LEFT:
		speedX= -10;
		//			controller->getView()->draw(this);
		break;
	case UP:
		speedY = 10;
		//			controller->getView()->draw(this);
		break;
	case RIGHT:
		speedX= 10;
		//			controller->getView()->draw(this);
		break;
	case DOWN:
		speedY= -10;
		//			controller->getView()->draw(this);
		break;
	}
}


