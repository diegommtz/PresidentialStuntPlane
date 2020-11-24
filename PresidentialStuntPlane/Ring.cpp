#include "Ring.h"
#include <iostream>
#define PI 3.14159265358979

Ring::Ring()
{
	radius = .5;
	thick = .1;

	planeDistance = 3.2;

	// Initialize random seed
	srand(time(NULL));
}

void SetMaterial()
{
	//Silver
	GLfloat mat_ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
	GLfloat mat_diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat mat_specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	float shine = 51.2f;
	GLfloat emission[] = { 0.45,0.333,0.075,1.0 };

	//glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	// Set material properties 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	
}

bool Ring::CheckCollision(float* planePos, float planeRadius)
{	
	float temp0 = planePos[0];
	float temp1 = planePos[1];
	float temp2 = planePos[2];

	float xDiff = pos[0] - planePos[0];
	float yDiff = pos[1] - planePos[1];
	float zDiff = pos[2] - planePos[2];

	float dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff, 2));

	if (dist < radius + .5)
		return true;
	else
		return false;
}

void Ring::SetRandPosition(float planePos[3], float rotX)
{
	rotY = rand() % 180;

	float angleXY = (rand() % 180) * PI / 180;
	float angleXZ = ((rand() % 180) + rotX - 90) * PI / 180;

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
	SetMaterial();
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(rotY, 0, 1, 0);
	// Draw big torus
	glutSolidTorus(thick, radius, 20, 20);
	glPopMatrix();
}

Ring::~Ring()
{
}
