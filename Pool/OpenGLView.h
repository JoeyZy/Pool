#pragma once
#include "view.h"

class OpenGLView :
	public View
{
public:
	static int x; 
	static int y;
	OpenGLView(int argc, char** argv);
	~OpenGLView();
	void init();
	void View::draw(Model* model);
};

