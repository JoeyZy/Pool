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
	Model* mainModel = new BallModel(); //Model
//	mainModel->listen(); //modelling
	View* view = new OpenGLView(); //View
	Controller* c = new WindowsKeyboardController(mainModel, view); //Controller
	c->controll(); //do controlling
	((OpenGLView*)view)->initGL(argc, argv); //post init in main thread OpenGL
	delete c;
	delete view;
	delete mainModel;
	system("pause");
	return 0;
};