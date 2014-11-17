#include "BallModel.h"
#include "Controller.h"
#include <thread>

BallModel::BallModel() {
	areaWidth = 1280;
	areaHeight = 720;
	startSpeed = 0.35f; //number of points to pass for model in 1/60
	stepLeft = 0.0; //numer of point for model to pass to left direction
	stepUp = 0.0; // -//- up
	stepRight = 0.0; // -//- right
	stepDown = 0.0; // -//- down
	//position
	x = 0.0; 
	y = 0.0;
	friction = 0.015f; //number of points to decrease in 1/60 second for model
	radius = 20; //radious
	type = "Ball";
	coeff = 1.11f; // coeff to multiple speed when key is gripped
	maxSpeed = 6.0; //max number of points to pass for model in 1/60 second
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
		if (stepLeft<maxSpeed) {
			if (stepLeft < 0) stepLeft = 0;
			float newValue = stepLeft + (stepLeft>1)?coeff*stepLeft:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepLeft = newValue;
		}
		break;
	case UP:
		if (stepUp < 0) stepUp = 0;
		if (stepUp<maxSpeed) {
			float newValue = stepUp + (stepUp>1)?coeff*stepUp:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepUp = newValue;
		}
		break;
	case RIGHT:
	
		if (stepRight < 0) stepRight = 0;
		if (stepRight<maxSpeed) {
			float newValue = stepRight + (stepRight>1)?coeff*stepRight:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepRight = newValue;
		}
		break;
	case DOWN:
		if (stepDown < 0) stepDown = 0;
		if (stepDown<maxSpeed) {
			float newValue = stepDown + (stepDown>1)?coeff*stepDown:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepDown = newValue;
		}
		break;
	}
}

void BallModel::correctSpeed() {
	if (stepLeft > 0) {
		stepLeft-=friction;
	}
	if (stepUp > 0) {
		stepUp-=friction;
	}
	if (stepRight > 0) {
		stepRight-=friction;
	}
	if (stepDown > 0) {
		stepDown-=friction;
	}
}

void BallModel::doListening() {
	while (true) {
		std::cout << "Listening " << x << " " << y << " " << stepRight << " " << stepDown << endl;
		// mirror model way from vertical borders
		if (x+radius+1>=areaWidth/2 || x-radius-1<=-areaWidth/2) {
			float buf = stepLeft;
			stepLeft = stepRight;
			stepRight = buf;
		}
		// mirror model from horizontal borders
		if (y+radius+1>=areaHeight/2 || y-radius-1<=-areaHeight/2) {
			float buf = stepUp;
			stepUp = stepDown;
			stepDown = buf;
		}

		if (stepLeft > 0) {
			x-=stepLeft;
		}
		if (stepUp > 0) {
			y+=stepUp;
		}
		if (stepRight > 0) {
			x+=stepRight;
		}
		if (stepDown > 0) {
			y-=stepDown;
		}
		correctSpeed();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}


