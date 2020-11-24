#include "Menu.h"

Menu::Menu()
{
	leftOp = true;
	leftVertex = .5;
	rightVertex = 1.5;
}

void Menu::CustomRenderText(string phrase) {
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 70.0);

	glMatrixMode(GL_MODELVIEW);
	glScalef(.001, .001, .001);

	const char* arr = phrase.c_str();
	const char* c;

	glColor3f(1.0, 1.0, 1.0);
	for (c = arr; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

void Menu::Draw()
{	
	glPushMatrix();
	glTranslatef(-0.35, .3, 0);
	CustomRenderText("Presidential");
	glPopMatrix();

	glPushMatrix();
	glScaled(.8, .8, .8);
	glTranslatef(-0.4, .2, 0);
	CustomRenderText("Stunt Plane");
	glPopMatrix();

	glPushMatrix();	
	glTranslated(0, -0.5, 0);

	if (leftOp)
	{
		glLineWidth(2.0);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(-leftVertex, 0, 0);
		glVertex3f(-rightVertex, 0, 0);
		glEnd();
	}
	else
	{
		glLineWidth(2.0);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(leftVertex, 0, 0);
		glVertex3f(rightVertex, 0, 0);
		glEnd();
	}

	glPushMatrix();
	glTranslatef(-.45, .37, 0);
	CustomRenderText("Start");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.2, .37, 0);
	CustomRenderText("Exit");
	glPopMatrix();
	glPopMatrix();
}

Menu::~Menu() {}