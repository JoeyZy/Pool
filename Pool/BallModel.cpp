#include "BallModel.h"
#include "Controller.h"
#include <thread>
#include <math.h>

BallModel::BallModel() {
	areaWidth = 1280;
	areaHeight = 720;
	frames = 250;
	m = 10;
	startSpeed = 0.12f; //number of points to pass for model in frames/second
	stepLeft = 0.0; //numer of point for model to pass to left direction
	stepUp = 0.0; // -//- up
	stepRight = 0.0; // -//- right
	stepDown = 0.0; // -//- down
	//position
	x = 0.0; 
	y = 0.0;
	friction = 0.005f; //number of points to decrease in frames/second for model
	radius = 20; //radious
	type = "Ball";
	maxSpeed = 4.0; //max number of points to pass for model in frames/second
}
BallModel::~BallModel() {
}



int BallModel::getRadius(){
	return radius;
}
void BallModel::setRadius(int radius) {
	this->radius = radius;
}

void BallModel::setPassiveBall(Model* model) {
	passiveBall = model;
}

Model* BallModel::getPassiveBall(){
	return passiveBall;
}

void BallModel::move(MoveType move) {

	switch (move) {
	case LEFT:
		increaseSpeed(stepLeft, stepRight);
		break;
	case UP:
		increaseSpeed(stepUp, stepDown);
		break;
	case RIGHT:
		increaseSpeed(stepRight, stepLeft);
		break;
	case DOWN:
		increaseSpeed(stepDown, stepUp);
		break;
	}
}

void BallModel::increaseSpeed(float &speed1, float &speed2) {
	speed1 += startSpeed;
	if (speed1 > maxSpeed) speed1 = maxSpeed;
	if (speed2 > speed1) {
		speed2 = speed2 - speed1;
		speed1 = 0;
	} else if (speed2 < speed1) {
		speed1 = speed1 - speed2;
		speed2 = 0;
	} else {
		speed1 = speed2 = 0;
	}
}

void BallModel::correctSpeed() {
	// speed c = sqrt ( speedX^2 + speedY^2)
	float c = sqrt(pow(stepLeft,2) + pow(stepRight,2) + pow(stepUp,2) + pow(stepDown, 2));
	if (c < friction) {
		c = stepLeft = stepRight = stepUp = stepDown = 0;
	} 
	float localFriction = friction;
	//controll speed
	if (c > maxSpeed) {
		localFriction = c - maxSpeed; 
	}

	float x  = abs((c - localFriction)/c);
	std::cout << x << " " << c << " " << stepLeft << " " <<  stepRight << " " <<  stepUp << " " <<  stepDown << endl;
	if (x < 1) {
		stepDown*=x;
		stepLeft*=x;
		stepRight*=x;
		stepUp*=x;
	}
}

void BallModel::listen() {
	std::thread t1(&BallModel::doListening, this);
	t1.detach();
}

void BallModel::doListening() {
	while (true) {

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
		std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000/frames)));
	}
}


