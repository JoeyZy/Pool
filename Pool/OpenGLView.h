#pragma once
#include "view.h"

class OpenGLView :
	public View
{
public:
	OpenGLView();
	~OpenGLView();
	void initGL(int argc, char** argv);
};

