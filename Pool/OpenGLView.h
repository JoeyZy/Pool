#pragma once
#include "view.h"

class OpenGLView :
	public View
{
private:
	static OpenGLView* instance;
	OpenGLView();
public:
	static OpenGLView* getInstance() {
		if (!instance) {
			instance = new OpenGLView();
		}
		return instance;
	}
	~OpenGLView();
	void initGL(int argc, char** argv);
};

