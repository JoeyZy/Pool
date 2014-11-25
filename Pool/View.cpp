#include "View.h"

void View::addModel(Model* model) {
	models.push_back(model);
}

vector<Model*> View::getModels() {
	return models;
}

string View::getType() {
	return type;
}