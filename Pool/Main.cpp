#include <iostream>
#include "Controller.h"
#include "WindowsKeyboardController.h"
#include "NotWindowsKeyboardController.h"
#include "Model.h"
#include "BallModel.h"
#include "ConsoleView.h"
#include "OpenGLview.h"

//Main + 1 + 2 + 3 + 4

int main() {
	Model* model = new BallModel();
	View* view = new ConsoleView(); 
	Controller* c = new WindowsKeyboardController(model, view);
	c->controll();
	delete view;
	view = new OpenGLView();
	c->setView(view);
	c->controll();
	delete c;
	delete view;
	delete model;
	system("pause");



};