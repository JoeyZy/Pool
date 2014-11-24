#include "BallModel.h"
#include "Controller.h"
#include <thread>

BallModel::BallModel() {
	areaWidth = 1280;
	areaHeight = 720;
	m = 10;
	startSpeed = 0.15f; //number of points to pass for model in 1/x
	stepLeft = 0.0; //numer of point for model to pass to left direction
	stepUp = 0.0; // -//- up
	stepRight = 0.0; // -//- right
	stepDown = 0.0; // -//- down
	//position
	x = 0.0; 
	y = 0.0;
	friction = 0.002f; //number of points to decrease in 1/x second for model
	radius = 20; //radious
	type = "Ball";
	maxSpeed = 4.0; //max number of points to pass for model in 1/x second
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
		if (stepLeft<maxSpeed) {
			if (stepLeft < 0) stepLeft = 0;
			float newValue = stepLeft + startSpeed/(stepRight<1?1:stepRight);
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepLeft = newValue;
			stepRight-=stepLeft;
		}
		break;
	case UP:
		if (stepUp < 0) stepUp = 0;
		if (stepUp<maxSpeed) {
			float newValue = stepUp + startSpeed/(stepDown<1?1:stepDown);
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepUp = newValue;
			stepDown-=stepUp;
		}
		break;
	case RIGHT:

		if (stepRight < 0) stepRight = 0;
		if (stepRight<maxSpeed) {
			float newValue = stepRight + startSpeed/(stepLeft<1?1:stepLeft); 
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepRight = newValue;
			stepLeft-=stepRight;
		}
		break;
	case DOWN:
		if (stepDown < 0) stepDown = 0;
		if (stepDown<maxSpeed) {
			float newValue = stepDown + startSpeed/(stepUp<1?1:stepUp); 
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepDown = newValue;
			stepUp-=stepDown;
		}
		break;
	}
}

void BallModel::correctSpeed() {

	if (stepLeft > 0) {
		stepLeft-=friction;//*stepLeft;
		if (stepLeft < 0) stepLeft=friction-stepLeft;
	} else {
		stepLeft = 0;
	}
	if (stepUp > 0) {
		stepUp-=friction;//*stepUp;
		if (stepUp < 0) stepUp=friction-stepUp;
	} else {
		stepUp = 0;
	}
	if (stepRight > 0) {
		stepRight-=friction;//*stepRight;
		if (stepRight < 0) stepRight=friction-stepRight;
	} else {
		stepRight = 0;
	}
	if (stepDown > 0) {
		stepDown-=friction;//*stepDown;
		if (stepDown < 0) stepDown=friction-stepDown;
	} else {
		stepDown = 0;
	}
}

void BallModel::listen() {
	std::thread t1(&BallModel::doListening, this);
	t1.detach();
}

void BallModel::doListening() {
	while (true) {
		std::cout << "Listening " << stepLeft << " " << stepUp << " " << stepRight << " " << stepDown << endl;
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

		/*		if (sqrt(pow(fabs(passiveBall->getX()-x),2.0) +	pow(fabs(passiveBall->getY()-y),2.0)) < radius + ((BallModel*)passiveBall)->getRadius()) {
		std::cout << "contact";
		float buf = stepLeft;
		stepLeft = stepRight;
		stepRight = buf;
		buf = stepUp;
		stepUp = stepDown;
		stepDown = buf;
		}
		*/
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
		std::this_thread::sleep_for(std::chrono::milliseconds(4));
	}
}


