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
//	std::thread t1(function_1);
//	t1.join();
	model = new BallModel();
	View* view = new OpenGLView(argc, argv); 
		//= new ConsoleView(); 
	c = new WindowsKeyboardController(model, view);
	//c->controll();
	//delete view;
	std::thread t1(function_1);
	std::thread t2(function_2);
//	view = new OpenGLView(argc, argv);
//	c->controll();
	((OpenGLView*)view)->initGL();
	delete c;
	delete view;
	delete model;
	system("pause");
	return 0;
};