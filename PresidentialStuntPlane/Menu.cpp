#include "Menu.h"

Menu::Menu()
{
	leftOp = true;
	leftVertex = .5;
	rightVertex = 1.5;
}

void Menu::Draw()
{
	if (leftOp)
	{
		glLineWidth(2.0);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, -leftVertex);
		glVertex3f(0, 0, -rightVertex);
		glEnd();
	}
	else
	{
		glLineWidth(2.0);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, leftVertex);
		glVertex3f(0, 0, rightVertex);
		glEnd();
	}
}

Menu::~Menu() {}