#include <Windows.h>	// Comment this line if Linux
#include<glut.h>		//"glut.h" if local
#include<GL/gl.h>		
#include <stdlib.h>		// Library used for random method

#include "Plane.h"

Plane* plane;


void customInitialize(void)
{
	// Set "clear" (background) color (r,g,b,a)
	// RGB [0 to 1]
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set shading model to use
	glShadeModel(GL_SMOOTH);

	// DEFINE material properties (for objects in scene)
	GLfloat mat_spec[] = { 0.393548, 0.271906, 0.166721, 1.0 };
	GLfloat mat_shiny[] = { 0.2 };
	GLfloat mat_amb[] = { 0.2125, 0.1275, 0.54, 1.0 };
	GLfloat mat_dif[] = { 0.714, 0.4284, 0.18144, 1.0 };

	// SET material properties
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	// DEFINE light properties (for lights in scene)
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };

	// SET light properties
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	// Activate (enable) lights
	glEnable(GL_LIGHT0);

	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);

	plane = new Plane();
}

void DrawAxis(void)
{
	// Disable lighting
	glDisable(GL_LIGHTING);
	// Drawing Axis
	glLineWidth(2.0);

	//Set red color and draw the x axis
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glEnd();

	//Set red color and draw the y axis
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.5, 0.0);
	glEnd();

	//Set red color and draw the z axis
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.5);
	glEnd();

	glEnable(GL_LIGHTING);
}

void display(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(plane->pos[0] + 5, plane->pos[1] + 0.3, plane->pos[2], plane->pos[0], plane->pos[1], plane->pos[2], 0.0, 1.0, 0.0);

	DrawAxis();

	plane->Fly();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	// Set the viewport size, based on function input
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// set the projection matrix based on input size
	glMatrixMode(GL_PROJECTION);
	// first set as identity
	glLoadIdentity();
	// then set perspective projection parameters based on aspect ratio
	gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 0.10, 20.0);		// For 3D
	//gluOrtho2D(0, 400, 0, 400);	// For 2D

	// Set the model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the "look at" point - where the "camera" is and
	// where it is "pointed"
	// gluLookAt(5.0, 5.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		// Use "Esc" key to exit
	case 27:
		exit(0);
		break;
	case'r':
		plane->Reset();
		break;
	case'm':
		plane->ToggleMove();
		break;
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		plane->Up();
		break;
	case GLUT_KEY_DOWN:
		plane->Down();
		break;
	case GLUT_KEY_LEFT:
		plane->Left();
		break;
	case GLUT_KEY_RIGHT:
		plane->Right();
		break;
	}
	glutPostRedisplay();
}

// Alternate version for iOS / Linux
// int main(int argc, char * argv[])
int main(int argc, char** argv)
{
	// GLUT INITIALIZATION
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sierpinski Triangle");

	// Additional initialization
	customInitialize();

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutSpecialFunc(processSpecialKeys);

	// Do main loop
	glutMainLoop();

	// Exit
	return 0;
}