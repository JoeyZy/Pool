#include "ConsoleController.h"
#include "windows.h"

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
			std::cout << "Move left" << std::endl;
			break;
		case VK_UP:
			std::cout << "Move up" << std::endl;
			break;
		case VK_RIGHT:
			std::cout << "Move right" << std::endl;
			break;
		case VK_DOWN:
			std::cout << "Move down" << std::endl;
			break;
		defaut:
			break;
		}
	}
}