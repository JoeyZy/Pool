#pragma once
#include "view.h"

class OpenGLView :
	public View
{
public:
	OpenGLView();
	~OpenGLView();
	void View::draw(Model* model);
};

