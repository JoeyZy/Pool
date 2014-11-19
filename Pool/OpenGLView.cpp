#include "OpenGLView.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#include "BallModel.h"
#include <thread>
using namespace std;
const double PI  =3.141592653589793238463;

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
	BallModel* model = (BallModel*) OpenGLView::model;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	circle(model->getX(), model->getY(), model->getRadius(), 40);
	if (model->getPassiveBall()!=NULL) circle(model->getPassiveBall()->getX(), model->getPassiveBall()->getY(), ((BallModel*)(model->getPassiveBall()))->getRadius(), 40);
	glPopMatrix();
	glutSwapBuffers();
}

void spinDisplay(void)
{
	glutPostRedisplay();
}
void reshape(int w, int h)
{

	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-OpenGLView::model->areaWidth/2,OpenGLView::model->areaWidth/2,-OpenGLView::model->areaHeight/2,OpenGLView::model->areaHeight/2,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

OpenGLView::OpenGLView(int argc, char **argv) {
	type = "OpenGL";
	glutInit(&argc,argv);
}

void OpenGLView::initGL() {
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(OpenGLView::model->areaWidth,OpenGLView::model->areaHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Pool");
	init();
	glutDisplayFunc(displayCircle);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
}

