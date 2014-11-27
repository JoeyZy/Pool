#define _USE_MATH_DEFINES
#include "BallModel.h"
#include "Controller.h"
#include <thread>
#include <cmath>
#include "OpenGLView.h"

//# define M_PI         3.141592653589793238462643383279502884 /* pi */

BallModel::BallModel(float x, float y) {
	type = "Ball "+ to_string(id++);
	isModelling = false;
	frames = 250;
	m = 10;
	startSpeed = 0.12f; //number of points to pass for model in frames/second
	//	stepLeft = 0.0; //numer of point for model to pass to left direction
	speedY = 0.0; // -//- speed
	speedX = 0.0; // -//- 
	//position
	this->x=x;
	this->y=y;
	friction = 0.001f; //number of points to decrease in frames/second for model
	radius = 40; //radious
	maxSpeed = 14.0; //max number of points to pass for model in frames/second
	//	listen();
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
		speedX -= startSpeed;
		if (abs(speedX)> maxSpeed) speedX = -maxSpeed;
		break;
	case UP:
		speedY += startSpeed;
		if (abs(speedY)> maxSpeed) speedY = maxSpeed;
		break;
	case RIGHT:
		speedX += startSpeed;
		if (abs(speedX)> maxSpeed) speedX = maxSpeed;
		break;
	case DOWN:
		speedY -= startSpeed;
		if (abs(speedY)> maxSpeed) speedY = -maxSpeed;
		break;
	}
}

//controll speed
void BallModel::correctSpeed() {
	float c = sqrt(pow(speedX,2) + pow(speedY,2));
	if (c < friction) {
		c = speedX = speedY = 0;
	} 
	float localFriction = friction;
	if (c > maxSpeed) {
		localFriction = c - maxSpeed; 
	}

	float x  = abs((c - localFriction)/c);
	if (x < 1) {
		speedX*=x;
		speedY*=x;
	}
}

void BallModel::listen() {
	std::thread t1(&BallModel::doListening, this);
	t1.detach();
}

void BallModel::doListening() {
	areaWidth = view->areaWidth;
	areaHeight = view->areaHeight;
	while (true) {

		// mirror model way from vertical borders
		if (x+radius>=areaWidth/2 || x-radius<=-areaWidth/2) {
			speedX = -speedX;
			while (x+radius>=areaWidth/2 || x-radius<=-areaWidth/2) {
				x<0?x+=startSpeed:x-=startSpeed;
			}
		}
		// mirror model from horizontal borders
		if (y+radius>=areaHeight/2 || y-radius<=-areaHeight/2) {
			speedY = -speedY;
			while (y+radius>=areaHeight/2 || y-radius<=-areaHeight/2) {
				y<0?y+=startSpeed:y-=startSpeed;
			}
		}

		if (view != NULL){
			vector<Model*> models = view->getModels();
			for (auto model: models) {
				BallModel* localModel = (BallModel*) model;
				if (this == localModel || isModelling) continue;
				float dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));
				if (dis  <= radius + localModel->getRadius()) {
					EnterCriticalSection(&OpenGLView::getInstance()->cs);
					localModel->isModelling = true;
					LeaveCriticalSection(&OpenGLView::getInstance()->cs);
					time_t  timev;
					cout << "lower: " << type << " " << time(&timev) << endl;
					float dx = x-localModel->getX();
					float dy = y-localModel->getY();
					float collisionision_angle = atan2(dy,dx);
					float magnitude_1 = sqrt(pow(speedX,2) + pow(speedY,2)); 
					float magnitude_2 = sqrt(pow(localModel->speedX,2) + pow(localModel->speedY,2));
					float direction_1 = atan2(speedY,speedX);
					float direction_2 = atan2(localModel->speedY,localModel->speedX);
					//cout << collisionision_angle << " " << magnitude_1 << " " << magnitude_2 << " " << direction_1 << " " << direction_2 << endl;
					float new_xspeed_1 = magnitude_1*cos(direction_1-collisionision_angle);
					float new_yspeed_1 = magnitude_1*sin(direction_1-collisionision_angle);
					float new_xspeed_2 = magnitude_2*cos(direction_2-collisionision_angle);
					float new_yspeed_2 = magnitude_2*sin(direction_2-collisionision_angle);
					float final_xspeed_1 = ((m-localModel->m)*new_xspeed_1+(localModel->m+localModel->m)*new_xspeed_2)/(m+localModel->m);
					float final_xspeed_2 = ((m+m)*new_xspeed_1+(localModel->m-m)*new_xspeed_2)/(m+localModel->m);
					float final_yspeed_1 = new_yspeed_1;
					float final_yspeed_2 = new_yspeed_2;
					speedX = (cos(collisionision_angle)*final_xspeed_1+cos(collisionision_angle+M_PI_2)*final_yspeed_1);
					if (speedX > -0.000001 && speedX < 0.000001) speedX = 0;
					speedY = (sin(collisionision_angle)*final_xspeed_1+sin(collisionision_angle+M_PI_2)*final_yspeed_1);
					if (speedY > -0.000001 && speedY < 0.000001) speedY = 0;
					localModel->speedX = (cos(collisionision_angle)*final_xspeed_2+cos(collisionision_angle+M_PI_2)*final_yspeed_2);
					if (localModel->speedX > -0.000001 && localModel->speedX < 0.000001) localModel->speedX = 0;
					localModel->speedY = (sin(collisionision_angle)*final_xspeed_2+sin(collisionision_angle+M_PI_2)*final_yspeed_2);
					if (localModel->speedY > -0.000001 && localModel->speedY < 0.000001) localModel->speedY = 0;

					dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));

					while (dis  <= radius + localModel->getRadius()) {
						if (speedX == 0 && speedY ==0 && localModel->speedY==0 && localModel->speedX==0) {
						//	speedX = speedY = localModel->speedY = localModel->speedX = 0.0001;
							break;
						}
						y+=speedY;
						x+=speedX;
						localModel->y+=localModel->speedY;
						localModel->x+=localModel->speedX;
						dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));
					}
					EnterCriticalSection(&OpenGLView::getInstance()->cs);
					localModel->isModelling  = false;
					LeaveCriticalSection(&OpenGLView::getInstance()->cs);
				}
			}

		}
		y+=speedY;
		x+=speedX;
		correctSpeed();

		std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000/frames)));
	}

}


