#include "Ring.h"
#define PI 3.14159265358979

Ring::Ring()
{
	radius = .5;
	thick = .1;

	planeDistance = 3;

	// Initialize random seed
	srand(time(NULL));
}

bool Ring::CheckCollision(float planePos[3], float planeRadius)
{	
	return false;
}

void Ring::SetRandPosition(float planePos[3])
{
	rotY = rand() % 180;

	float angleXY = (rand() % 181) * PI / 180;
	float angleXZ = (rand() % 181) * PI / 180;

	float x = planeDistance * sin(angleXY);

	float yzDist = planeDistance * cos(angleXY);

	float y = yzDist * cos(angleXZ);
	float z = yzDist * sin(angleXZ);

	pos[0] = planePos[0] + x;
	pos[1] = planePos[1] + y;
	pos[2] = planePos[2] + z;

}

void Ring::Draw()
{
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(rotY, 0, 1, 0);
	// Draw big torus
	glutWireTorus(thick, radius, 20, 20);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

Ring::~Ring()
{
}
