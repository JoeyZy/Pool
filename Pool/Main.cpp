#include <iostream>
#include "Controller.h"
#include "WindowsKeyboardController.h"
#include "NotWindowsKeyboardController.h"
#include "Model.h"
#include "BallModel.h"
#include "ConsoleView.h"

//Main + 1 + 2

int main() {
	Model* model = new BallModel();
	View* view = new ConsoleView(); 
	Controller* c = new WindowsKeyboardController();
	c->setModel(model);
	c->setView(view);
	c->controll();
	delete model;
	delete view;
	delete c;
};