#include "BallModel.h"
#include "Controller.h"
#include <thread>

BallModel::BallModel() {
	areaWidth = 1280;
	areaHeight = 720;
	startSpeed = 0.1f; //number of points to pass for model in 1/60
	stepLeft = 0.0; //numer of point for model to pass to left direction
	stepUp = 0.0; // -//- up
	stepRight = 0.0; // -//- right
	stepDown = 0.0; // -//- down
	//position
	x = 0.0; 
	y = 0.0;
	friction = 0.002f; //number of points to decrease in 1/60 second for model
	radius = 20; //radious
	type = "Ball";
	coeff = 1.18f; // coeff to multiple speed when key is gripped
	maxSpeed = 2.0; //max number of points to pass for model in 1/60 second
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
			float newValue = stepLeft + startSpeed;//(stepLeft>1)?coeff*stepLeft:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepLeft = newValue;
			stepRight-=stepLeft/40;
		}
		break;
	case UP:
		if (stepUp < 0) stepUp = 0;
		if (stepUp<maxSpeed) {
			float newValue = stepUp + startSpeed;//(stepUp>1)?coeff*stepUp:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepUp = newValue;
			stepDown-=stepUp/40;
		}
		break;
	case RIGHT:

		if (stepRight < 0) stepRight = 0;
		if (stepRight<maxSpeed) {
			float newValue = stepRight + startSpeed; //(stepRight>1)?coeff*stepRight:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepRight = newValue;
			stepLeft-=stepRight/40;
		}
		break;
	case DOWN:
		if (stepDown < 0) stepDown = 0;
		if (stepDown<maxSpeed) {
			float newValue = stepDown + startSpeed; //(stepDown>1)?coeff*stepDown:startSpeed;
			if (newValue > maxSpeed) newValue = maxSpeed;
			stepDown = newValue;
			stepUp-=stepDown/40;
		}
		break;
	}
}

void BallModel::correctSpeed() {

	if (stepLeft > 0) {
		stepLeft-=friction;
		if (stepLeft < 0) stepLeft=0;
	} else {
		stepLeft = 0;
	}
	if (stepUp > 0) {
		stepUp-=friction;
		if (stepUp < 0) stepUp=0;
	} else {
		stepUp = 0;
	}
	if (stepRight > 0) {
		stepRight-=friction;
		if (stepRight < 0) stepRight=0;
	} else {
		stepRight = 0;
	}
	if (stepDown > 0) {
		stepDown-=friction;
		if (stepDown < 0) stepDown=0;
	} else {
		stepDown = 0;
	}
}

void BallModel::doListening() {
	while (true) {
//		std::cout << "Listening " << stepLeft << " " << stepUp << " " << stepRight << " " << stepDown << endl;
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


