#include "ConsoleController.h"
#include "windows.h"

/*
Do contolling;
*/


void ConsoleController::controll() {
	HANDLE hIn;
	HANDLE hOut;
	COORD KeyWhere;
	COORD EndWhere;
	bool Continue = TRUE;
	int KeyEvents = 0;
	INPUT_RECORD InRec;
	DWORD NumRead;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "Key Events: " << std::endl;

	while (Continue)
	{
		ReadConsoleInput(hIn,
			&InRec,
			1,
			&NumRead);
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
		}
	}
}