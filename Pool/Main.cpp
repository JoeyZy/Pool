#include <iostream>
#include "Controller.h"
#include "WindowsKeyboardController.h"
#include "NotWindowsKeyboardController.h"
#include "Model.h"
#include "BallModel.h"
#include "ConsoleView.h"
#include "OpenGLview.h"
#include <thread>

//Main + 1 + 2 + 3 + 4

int main(int argc, char **argv) {
	Model* model = new BallModel(); //Model
	model->listen(); //modelling
	View* view = new OpenGLView(argc, argv); //View
	Controller* c = new WindowsKeyboardController(model, view); //Controller
	c->controll(); //do controlling
	((OpenGLView*)view)->initGL(); //post init in main thread OpenGL
	delete c;
	delete view;
	delete model;
	system("pause");
	return 0;
};