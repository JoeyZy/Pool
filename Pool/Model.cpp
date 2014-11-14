#include "Model.h"
#include <iostream>
#include "Controller.h"

int Model::getX() {
	return x;
}
void Model::setX(int x) {
	this->x=x;
}
int Model::getY() {
	return y;
}
void Model::setY(int y) {
	this->y=y;
}
void Model::setType(string type) {
	this->type = type;
}
string Model::getType() {
	return type;
}
void Model::setController(Controller* controller) {
	this->controller = controller;
}
Controller* Model::getController() {
	return controller;
}

void Model::doListening() {
//	while (true) {
		correctSpeed(speedX);
		correctSpeed(speedY);
		std::cout << "Listening " << speedX << " " << speedY << endl;
		x += speedX;
		y += speedY;
		std::cout << controller->getView()->getType() << std::endl;
		controller->getView()->draw(this);
//	}
}

void Model::correctSpeed(int &speed) {
	if (speed > 0) {
		if (speed - friction >= 0) 
			speed -= friction;
		else speed = 0;
	} else if (speed < 0) {
		if (speed + friction <= 0) 
			speed += friction;
		else speed = 0;
	}
}