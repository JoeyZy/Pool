#pragma once

#include <iostream>
#include "Model.h"
#include "View.h"

class Controller {
protected:
	Model *model;
	View *view;
public:
	void setModel(Model *model);
	Model* getModel();
	void setView(View *view);
	View* getView();
	virtual void controll() = 0;
};