#include "windows.h"
#include <iostream>
#include "Model.h"
#include "View.h"

using namespace std;

class Controller {
	Model *model;
	View *view;
public:
	void setModel(Model *model);
	Model* getModel();
	void setView(View *view);
	View* getView();

	virtual void controll() = 0;
};