#include <iostream>
#include "Controller.h"
#include "ConsoleController.h"
#include "OpenGLController.h"
#include "Model.h"
#include "BallModel.h"
#include "ConsoleView.h"

//Main
//Added another comment

int main() {
	Model* model = new BallModel();
	View* view = new ConsoleView(); 
	Controller* c = new ConsoleController();
	c->setModel(model);
	c->setView(view);
	c->controll();
};