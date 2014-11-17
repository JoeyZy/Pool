#pragma once
#include "view.h"

class OpenGLView :
	public View
{
public:
	static int x; 
	static int y;
	static int width;
	static int height;
	OpenGLView(int argc, char** argv);
	~OpenGLView();
	void initGL();
	//void displayCircle();
};

