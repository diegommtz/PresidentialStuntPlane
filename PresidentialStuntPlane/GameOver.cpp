#include "GameOver.h"
#include <string>
 
GameOver::GameOver()
{
}

void GameOver::Draw(int totalTime)
{
	glPushMatrix();
	glTranslatef(-0.35, .3, 0);
	CustomRenderText("Game Over");
	glPopMatrix();

	string timeLasted = "You survived for " + std::to_string(totalTime) + " seconds";
	glPushMatrix();
	glTranslatef(-0.45, 0, 0);
	glScaled(.5, .5, .5);
	CustomRenderText(timeLasted);
	glPopMatrix();

	glLineWidth(2.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-.5, -1, 0);
	glVertex3f(.5, -1, 0);
	glEnd();

	glPushMatrix();
	glTranslatef(-.1, -.25, 0);
	glScaled(.9, .9, .9);
	CustomRenderText("Exit");
	glPopMatrix();
}

void GameOver::CustomRenderText(string phrase)
{
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

GameOver::~GameOver()
{
}
