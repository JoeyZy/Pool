#include "Model.h"
#include <iostream>
#include "Controller.h"
#include <thread>

float Model::getX() {
	return x;
}
void Model::setX(float x) {
	this->x=x;
}
float Model::getY() {
	return y;
}
void Model::setY(float y) {
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

void Model::setView(View* view) {
	this->view = view;
	listen();
}

View* Model::getView() {
	return view;
}
