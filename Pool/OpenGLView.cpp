#include "OpenGLView.h"
#include <iostream>

OpenGLView::OpenGLView() {
	type = "OpenGL";
}

void OpenGLView::draw(Model* model) {
	if (model->getType()=="Ball") {
		cout << "OpenGL: " << model->getType() << ": x=" << model->getX() << ", y= " << model->getY() << endl;
	} else {
		cout << "Don't know how to draw it" << endl;
	}
}
