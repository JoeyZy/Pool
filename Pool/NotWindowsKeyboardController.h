#pragma once

#include "Controller.h"

class NotWindowsKeyboardController: public Controller {
public:
	NotWindowsKeyboardController();
	NotWindowsKeyboardController(Model* model, View* view);
	~NotWindowsKeyboardController();
	void controll();
};