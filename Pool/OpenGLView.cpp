#include "OpenGLView.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#include "BallModel.h"
using namespace std;
const double PI  =3.141592653589793238463;

int OpenGLView::x;
int OpenGLView::y;

void OpenGLView::draw(Model* model) {
	if (model->getType()=="Ball") {
				cout << "Console: " << model->getType() << ": x=" << model->getX() << ", y= " << model->getY() << endl;
		x = model->getX();
		y = model->getY();
	} else {
		cout << "Don't know how to draw it" << endl;
	}
}

GLfloat spin=0.0;
void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
}
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
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
//	glTranslatef(spin, spin, 0.0);
	glColor3f(1.0,1.0,1.0);
	//	glRectf(-50.0,-50.0,0.0,0.0);
//	std::cout << "Circle " << OpenGLView::x << " " << OpenGLView::y << std::endl;
	circle(OpenGLView::x, OpenGLView::y, 10.0, 40);
	glPopMatrix();
	glutSwapBuffers();
}
void spinDisplay(void)
{
//	spin++;
	spin += 0.001;
	glutPostRedisplay();
}
void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0,50.0,-50.0,50.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLView::init() {
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Pool");
	init();
	glutDisplayFunc(displayCircle);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinDisplay);
	glutMainLoop();

}

OpenGLView::OpenGLView(int argc, char **argv) {
	type = "OpenGL";
	glutInit(&argc,argv);

	//glutMouseFunc(mouse);
//glutMainLoop();
}
