#pragma once

#include "Controller.h"

class WindowsKeyboardController: public Controller {
public:
	WindowsKeyboardController();
	WindowsKeyboardController(Model* model, View* view);
	~WindowsKeyboardController();
	void controll();
	void doControlling();
};