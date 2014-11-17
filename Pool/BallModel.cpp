#include "BallModel.h"
#include "Controller.h"
#include <thread>

BallModel::BallModel() {
	x = 0;
	y = 0;
	speedX = 0;
	speedY = 0;
	friction = 1;
	radius = 10;
	type = "Ball";
	defaultSpeed = 20;
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
		speedX= -defaultSpeed;
		//			controller->getView()->draw(this);
		break;
	case UP:
		speedY = defaultSpeed;
		//			controller->getView()->draw(this);
		break;
	case RIGHT:
		speedX= defaultSpeed;
		//			controller->getView()->draw(this);
		break;
	case DOWN:
		speedY= -defaultSpeed;
		//			controller->getView()->draw(this);
		break;
	}
}


