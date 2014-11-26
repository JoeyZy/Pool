#include "OpenGLView.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#include "BallModel.h"
#include <thread>
#include <vector>
using namespace std;
const double PI=3.141592653589793238463;

OpenGLView* OpenGLView::instance = 0;

void init(void)
{
	glClearColor(0.0,0.7,0.0,0.0);
	glShadeModel(GL_FLAT);
}

//draw circle
void circle(float x, float y, float r, int segments)
{
	glBegin( GL_TRIANGLE_FAN );
	glVertex2f(x, y);
	for( int n = 0; n <= segments; ++n ) {
		float const t = 2*PI*(float)n/(float)segments;
		glVertex2f(x + sin(t)*r, y + cos(t)*r);
	}
	glEnd();
}

void displayCircle(void)
{
	OpenGLView* openGLView = OpenGLView::getInstance();
	vector<Model*> models = openGLView->getModels();
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	bool first = true;
	for (auto model: models) {
		BallModel* localModel = (BallModel*) model;
		circle(localModel->getX(), localModel->getY(), localModel->getRadius(), 40);
		first = false;
		glColor3f(0.0,0.0,0.7);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void spinDisplay(void)
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	OpenGLView* openGLView = OpenGLView::getInstance();
	vector<Model*> models = openGLView->getModels();
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-OpenGLView::getInstance()->areaWidth/2,OpenGLView::getInstance()->areaWidth/2,-OpenGLView::getInstance()->areaHeight/2,OpenGLView::getInstance()->areaHeight/2,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

OpenGLView::OpenGLView() {
	type = "OpenGL";
	areaWidth = 1280;
	areaHeight = 720;
}

void OpenGLView::initGL(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(areaWidth,areaHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Pool");
	init();
	glutDisplayFunc(displayCircle);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
}

