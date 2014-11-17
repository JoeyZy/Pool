#include "View.h"

Model* View::model;

void View::setModel(Model* model) {
	this->model = model;
}

Model* View::getModel() {
	return model;
}

string View::getType() {
	return type;
}