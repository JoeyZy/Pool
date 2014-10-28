#include "Controller.h"

void Controller::setModel(Model *model) {
	this->model = model;
}
Model* Controller::getModel(){
	return model;
}
void Controller::setView(View *view) {
	this->view = view;
}
View* Controller::getView(){
	return view;
}