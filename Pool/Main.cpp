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

Controller* c;
Model* model;
BallModel* passiveBall;

void function_1() {
	model->doListening();
}

void function_2() {
	//passiveBall->doListening();
}

void function_3() {
	c->controll();
}

int main(int argc, char **argv) {
	model = new BallModel(); //Model
//	passiveBall = new BallModel();
//	passiveBall->setX(400);
//	((BallModel*)model)->setPassiveBall(passiveBall);
//	passiveBall->setPassiveBall(model);
	View* view = new OpenGLView(argc, argv); //View
	c = new WindowsKeyboardController(model, view); //Controller -
	std::thread t1(function_1); //modellin
	std::thread t2(function_2); //modelling
	std::thread t3(function_3); //keyboard lisntener
	((OpenGLView*)view)->initGL(); //post init OpenGL
	delete c;
	delete view;
	delete model;
	system("pause");
	return 0;
};