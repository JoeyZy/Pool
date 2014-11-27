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
	InitializeCriticalSection(&OpenGLView::cs);
	View* view = OpenGLView::getInstance(); //View
	Model* mainModel = new BallModel(-200); //Controlled model	
	Controller* c = new WindowsKeyboardController(mainModel, view); //Controller
	c->controll(); //do controlling
	Model* model1 = new BallModel(100,0); //Model1
	view->addModel(model1);
	//set weight (default = 10)
	((BallModel*)mainModel)->m = 1000;
	view->addModel(new BallModel(200,200));
	view->addModel(new BallModel(-100,0));
//	view->addModel(new BallModel(0,0));
	view->addModel(new BallModel(200,100));
	((OpenGLView*)view)->initGL(argc, argv); //post init in main thread OpenGL
	delete c;
	delete view;
	delete model1;
	delete mainModel;
	system("pause");
	return 0;
};