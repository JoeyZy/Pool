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

void function_1() {
	model->doListening();
}

void function_2() {
	c->controll();
}

int main(int argc, char **argv) {
	model = new BallModel(); //Model
	View* view = new OpenGLView(argc, argv); //View
	c = new WindowsKeyboardController(model, view); //Controller -
	std::thread t1(function_1); //keyboard listener in separate thread 
	std::thread t2(function_2); //model calcs in separate thread
	((OpenGLView*)view)->initGL(); //post init OpenGL
	delete c;
	delete view;
	delete model;
	system("pause");
	return 0;
};