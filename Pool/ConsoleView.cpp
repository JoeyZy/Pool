#include "ConsoleView.h"
#include <iostream>

void ConsoleView::draw(Model* model) {
	if (model->getType()=="Ball") {
		cout << model->getType() << ": x=" << model->getX() << ", y= " << model->getY() << ", radius=" << model->getRadius() << endl;
	} else {
		cout << "Don't know how to draw it" << endl;
	}
}
