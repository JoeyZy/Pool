#include "WindowsKeyboardController.h"
#include "windows.h"
#include <thread>


/*
Do contolling;
*/


WindowsKeyboardController::WindowsKeyboardController(Model* model, View* view) {
	this->model = model;
	this->view = view;
	model->setController(this); //Model listen to controller;
	view->setModel(model); //View listen to Model and redraw it by itself;
}

void WindowsKeyboardController::controll() {
	doControlling = true;
	HANDLE hIn;
	HANDLE hOut;
	INPUT_RECORD InRec;
	DWORD NumRead;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Used view: " << view->getType() << endl;
	while (doControlling)
	{
		ReadConsoleInput(hIn,
			&InRec,
			1,
			&NumRead);
		if (InRec.Event.KeyEvent.bKeyDown) {
			switch (InRec.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_LEFT:
				model->move(LEFT);
				break;
			case VK_UP:
				model->move(UP);
				break;
			case VK_RIGHT:
				model->move(RIGHT);
				break;
			case VK_DOWN:
				model->move(DOWN);
				break;
			case 13: // 'Enter'
				doControlling = false; //exit from loop
				break;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
