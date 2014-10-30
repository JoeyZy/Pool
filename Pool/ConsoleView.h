#pragma once
#include "view.h"
class ConsoleView :
	public View
{
public:
	ConsoleView();
	~ConsoleView();
	void View::draw(Model* model);
};

