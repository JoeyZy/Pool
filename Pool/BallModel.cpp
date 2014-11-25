#include "BallModel.h"
#include "Controller.h"
#include <thread>
#include <math.h>
# define M_PI         3.141592653589793238462643383279502884 /* pi */

BallModel::BallModel() {
	type = "Ball";
	frames = 250;
	m = 10;
	startSpeed = 0.12f; //number of points to pass for model in frames/second
//	stepLeft = 0.0; //numer of point for model to pass to left direction
	stepUp = 0.0; // -//- up
	stepRight = 0.0; // -//- right
//	stepDown = 0.0; // -//- down
	//position
	x = 0.0; 
	y = 0.0;
	friction = 0.002f; //number of points to decrease in frames/second for model
	radius = 20; //radious
	maxSpeed = 4.0; //max number of points to pass for model in frames/second
	listen();
}
BallModel::~BallModel() {
}



int BallModel::getRadius(){
	return radius;
}
void BallModel::setRadius(int radius) {
	this->radius = radius;
}

void BallModel::move(MoveType move) {
	areaWidth = controller->getView()->areaWidth;
	areaHeight = controller->getView()->areaHeight;
	switch (move) {
	case LEFT:
		stepRight -= startSpeed;
		if (abs(stepRight)> maxSpeed) stepRight = -maxSpeed;
//		increaseSpeed(stepLeft, stepRight);
		break;
	case UP:
		stepUp += startSpeed;
		if (abs(stepUp)> maxSpeed) stepUp = maxSpeed;
//		increaseSpeed(stepUp, stepDown);
		break;
	case RIGHT:
		stepRight += startSpeed;
		if (abs(stepRight)> maxSpeed) stepRight = maxSpeed;
//		increaseSpeed(stepRight, stepLeft);
		break;
	case DOWN:
		stepUp -= startSpeed;
		if (abs(stepUp)> maxSpeed) stepUp = -maxSpeed;
//		increaseSpeed(stepDown, stepUp);
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
	float c = sqrt(pow(stepRight,2) + pow(stepUp,2));
	if (c < friction) {
		c = stepRight = stepUp = 0;
	} 
	float localFriction = friction;
	//controll speed
	if (c > maxSpeed) {
		localFriction = c - maxSpeed; 
	}

	float x  = abs((c - localFriction)/c);
	//	std::cout << x << " " << c << " " << stepLeft << " " <<  stepRight << " " <<  stepUp << " " <<  stepDown << endl;
	if (x < 1) {
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
			stepRight = -stepRight;
		}
		// mirror model from horizontal borders
		if (y+radius+1>=areaHeight/2 || y-radius-1<=-areaHeight/2) {
			stepUp = -stepUp;
		}
		/*
		if (controller != NULL) {
			vector<Model*> models = controller->getView()->getModels();
			for (auto model: models) {
				if (this == model) continue;
				BallModel* localModel = (BallModel*) model;
				int dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));
				if (dis +1 == radius + localModel->getRadius()) {
					cout << dis << " " << x << " " << y << " " << localModel->getX() << " " << localModel->getY() << endl;
					cout << "lower" << endl;
					float dx = x-localModel->getX();
					float dy = y-localModel->getY();
					float collisionision_angle = atan(dy/dx);
					float magnitude_1 = sqrt(pow(stepLeft,2) + pow(stepRight,2) + pow(stepUp,2) + pow(stepDown, 2));
					float magnitude_2 = sqrt(pow(localModel->stepLeft,2) + pow(localModel->stepRight,2) + pow(localModel->stepUp,2) + pow(localModel->stepDown, 2));
					float direction_1 = atan((stepUp + stepDown) /(stepLeft + stepRight));
					float direction_2 = atan((localModel->stepUp + localModel->stepDown) /(localModel->stepLeft + localModel->stepRight));
					float new_xspeed_1 = magnitude_1*cos(direction_1-collisionision_angle);
					float new_yspeed_1 = magnitude_1*sin(direction_1-collisionision_angle);
					float new_xspeed_2 = magnitude_2*cos(direction_2-collisionision_angle);
					float new_yspeed_2 = magnitude_2*sin(direction_2-collisionision_angle);
					float final_xspeed_1 = ((m-localModel->m)*new_xspeed_1+(localModel->m+localModel->m)*new_xspeed_2)/(m+localModel->m);
					float final_xspeed_2 = ((m+m)*new_xspeed_1+(localModel->m-m)*new_xspeed_2)/(m+localModel->m);
					float final_yspeed_1 = new_yspeed_1;
					float final_yspeed_2 = new_yspeed_2;
					stepLeft>stepRight?stepLeft:stepRight = cos(collisionision_angle)*final_xspeed_1+cos(collisionision_angle+M_PI/2)*final_yspeed_1;
					stepUp>stepDown?stepUp:stepDown = sin(collisionision_angle)*final_xspeed_1+sin(collisionision_angle+M_PI/2)*final_yspeed_1;
					localModel->stepLeft>localModel->stepRight?localModel->stepLeft:stepRight = cos(collisionision_angle)*final_xspeed_2+cos(collisionision_angle+M_PI/2)*final_yspeed_2;
					localModel->stepUp>localModel->stepDown?localModel->stepUp:stepDown = sin(collisionision_angle)*final_xspeed_2+sin(collisionision_angle+M_PI/2)*final_yspeed_2;
				}
			}
		}
		*/
		y+=stepUp;
		x+=stepRight;
		correctSpeed();
		std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000/frames)));
	}
}


