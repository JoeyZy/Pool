#include "WindowsKeyboardController.h"
#include "windows.h"

/*
Do contolling;
*/


WindowsKeyboardController::WindowsKeyboardController(Model* model, View* view) {
	this->model = model;
	this->view = view;
}

void WindowsKeyboardController::controll() {
	doControlling = true;
	HANDLE hIn;
	HANDLE hOut;
	COORD KeyWhere;
	COORD EndWhere;
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
		if (!InRec.Event.KeyEvent.bKeyDown) {
			switch (InRec.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_LEFT:
				//cout << "move left" << endl;
				model->move(LEFT);
				view->draw(model);
				break;
			case VK_UP:
				//cout << "move up" << endl;
				model->move(UP);
				view->draw(model);
				break;
			case VK_RIGHT:
				//cout << "move right" << endl;
				model->move(RIGHT);
				view->draw(model);
				break;
			case VK_DOWN:
				//cout << "move down" << endl;
				model->move(DOWN);
				view->draw(model);
				break;
			case 13: // 'Enter'
				doControlling = false;
				break;
			}
		}
	}
}