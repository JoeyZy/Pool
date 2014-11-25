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
	View* view = OpenGLView::getInstance(); //View
	Model* mainModel = new BallModel(); //Model
	Model* model1 = new BallModel(); //Model1
	model1->setX(model1->getX()+100);
	Controller* c = new WindowsKeyboardController(mainModel, view); //Controller
	view->addModel(model1);
	c->controll(); //do controlling
	((OpenGLView*)view)->initGL(argc, argv); //post init in main thread OpenGL
	delete c;
	delete view;
	delete mainModel;
	system("pause");
	return 0;
};