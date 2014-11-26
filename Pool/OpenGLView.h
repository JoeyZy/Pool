#pragma once
#include "view.h"
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <string>

class OpenGLView :
	public View
{
private:
	static OpenGLView* instance;
	OpenGLView();
public:
	static CRITICAL_SECTION cs;
	static OpenGLView* getInstance() {
		if (!instance) {
			instance = new OpenGLView();
			InitializeCriticalSection(&cs);
		}
		return instance;
	}
	~OpenGLView();
	void initGL(int argc, char** argv);
};

