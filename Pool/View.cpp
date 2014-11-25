#include "View.h"

void View::addModel(Model* model) {
	model->setView(this);
	models.push_back(model);
}

vector<Model*> View::getModels() {
	return models;
}

string View::getType() {
	return type;
}