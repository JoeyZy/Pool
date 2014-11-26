#include "BallModel.h"
#include "Controller.h"
#include <thread>
#include <math.h>
#include "SingleLockObj.h"
#include "OpenGLView.h"

# define M_PI         3.141592653589793238462643383279502884 /* pi */

BallModel::BallModel() {
	type = "Ball";
	isModelling = false;
	frames = 250;
	m = 100000;
	startSpeed = 0.12f; //number of points to pass for model in frames/second
	//	stepLeft = 0.0; //numer of point for model to pass to left direction
	speedY = 0.0; // -//- up
	speedX = 0.0; // -//- right
	//	stepDown = 0.0; // -//- down
	//position
	x = 0.0; 
	y = 0.0;
	friction = 0;//0.002f; //number of points to decrease in frames/second for model
	radius = 40; //radious
	maxSpeed = 4.0; //max number of points to pass for model in frames/second
	//	listen();
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

void BallModel::correctSpeed() {
	// speed c = sqrt ( speedX^2 + speedY^2)
	float c = sqrt(pow(speedX,2) + pow(speedY,2));
	if (c < friction) {
		c = speedX = speedY = 0;
	} 
	float localFriction = friction;
	//controll speed
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
				//				x<0?speedX+=startSpeed:speedX-=startSpeed;
			}
		}
		// mirror model from horizontal borders
		if (y+radius>=areaHeight/2 || y-radius<=-areaHeight/2) {
			speedY = -speedY;
			while (y+radius>=areaHeight/2 || y-radius<=-areaHeight/2) {
				y<0?y+=startSpeed:y-=startSpeed;
				//				y<0?speedY+=startSpeed:speedY-=startSpeed;
			}
		}

		if (view != NULL){// && type.compare("ball2")!=0) {
			//cout << type << " " << type.compare("ball2") << endl;
			//		isModelling = true;
			vector<Model*> models = view->getModels();
			for (auto model: models) {
				BallModel* localModel = (BallModel*) model;
				if (this == localModel || isModelling) continue;
				EnterCriticalSection(&OpenGLView::getInstance()->cs);
	//			cout << type << " in section" << endl;
	//			if (localModel->isModelling) continue;
				float dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));
				if (dis  <= radius + localModel->getRadius()) {
					time_t  timev;
					cout << "lower: " << type << " " << time(&timev) << endl;
					float dx = x-localModel->getX();
					float dy = y-localModel->getY();
					float dif = dx!=0?dy/dx:0;
					float collisionision_angle = dx==0?dy/abs(dy)*M_PI/2:atan(dif);
					float magnitude_1 = sqrt(pow(speedX,2) + pow(speedY,2)); 
					float magnitude_2 = sqrt(pow(localModel->speedX,2) + pow(localModel->speedY,2));
					dif = speedX!=0?speedY/speedX:0;
					float direction_1 = dx==0?dy/abs(dy)*M_PI/2:atan(dif);
					dif = localModel->speedX!=0?localModel->speedY/localModel->speedX:0;
					float direction_2 = dx==0?dy/abs(dy)*M_PI/2:atan(dif);
					//cout << collisionision_angle << " " << magnitude_1 << " " << magnitude_2 << " " << direction_1 << " " << direction_2 << endl;
					float new_xspeed_1 = magnitude_1*cos(direction_1-collisionision_angle);
					float new_yspeed_1 = magnitude_1*sin(direction_1-collisionision_angle);
					float new_xspeed_2 = magnitude_2*cos(direction_2-collisionision_angle);
					float new_yspeed_2 = magnitude_2*sin(direction_2-collisionision_angle);
					float final_xspeed_1 = ((m-localModel->m)*new_xspeed_1+(localModel->m+localModel->m)*new_xspeed_2)/(m+localModel->m);
					float final_xspeed_2 = ((m+m)*new_xspeed_1+(localModel->m-m)*new_xspeed_2)/(m+localModel->m);
					float final_yspeed_1 = new_yspeed_1;
					float final_yspeed_2 = new_yspeed_2;
					speedX = dx==0?0:dx/abs(dx)*(cos(collisionision_angle)*final_xspeed_1+cos(collisionision_angle+M_PI/2)*final_yspeed_1);
					speedY = dy==0?0:dy/abs(dy)*(sin(collisionision_angle)*final_xspeed_1+sin(collisionision_angle+M_PI/2)*final_yspeed_1);
					localModel->speedX = (cos(collisionision_angle)*final_xspeed_2+cos(collisionision_angle+M_PI/2)*final_yspeed_2);
					localModel->speedY = dy==0?0:dy/abs(dy)*(sin(collisionision_angle)*final_xspeed_2+sin(collisionision_angle+M_PI/2)*final_yspeed_2);

					dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));

					while (dis  <= radius + localModel->getRadius()) {
						float stepX = dx!=0?dx/abs(dx)*startSpeed:0;
						float stepY = dy!=0?dy/abs(dy)*startSpeed:0;
						x+=stepX;
						y+=stepY;
						localModel->x+=-stepX;
						localModel->y+=-stepY;
			/*		y-=speedY;
					x-=speedX;
					localModel->y-=speedY;
					localModel->x-=speedX;*/
						dis = sqrt(pow(x - localModel->getX(),2) + pow(y - localModel->getY(), 2));
					}
					y-=speedY;
					x-=speedX;
					localModel->y-=speedY;
					localModel->x-=speedX;

				}
		//		cout << type << " out section" << endl;
				LeaveCriticalSection(&OpenGLView::getInstance()->cs);
			}
			//		isModelling = false;
		
		}
		y+=speedY;
		x+=speedX;
			//	correctSpeed();

		std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000/frames)));
	}

}


