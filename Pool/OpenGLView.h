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
//		EnterCriticalSection(&OpenGLView::getInstance()->cs);
		if (!instance) {
			//InitializeCriticalSection(&cs);
			instance = new OpenGLView();
		}
//		LeaveCriticalSection(&OpenGLView::getInstance()->cs);
		return instance;
	}
	~OpenGLView();
	void addModel(Model* model);
	void initGL(int argc, char** argv);
};

