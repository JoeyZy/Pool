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
	Model* model1 = new BallModel(); //Model1
	Model* mainModel = new BallModel(); //Model
	model1->setX(model1->getX()+100);
//	model1->setY(model1->getY()+50);
	model1->setType("ball2");
	Controller* c = new WindowsKeyboardController(mainModel, view); //Controller
	view->addModel(model1);
	c->controll(); //do controlling
	((OpenGLView*)view)->initGL(argc, argv); //post init in main thread OpenGL
	delete c;
	delete view;
	delete model1;
	delete mainModel;
	system("pause");
	return 0;
};