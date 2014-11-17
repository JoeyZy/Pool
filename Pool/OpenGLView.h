#pragma once
#include "view.h"

class OpenGLView :
	public View
{
public:
	OpenGLView(int argc, char** argv);
	~OpenGLView();
	void initGL();
};

