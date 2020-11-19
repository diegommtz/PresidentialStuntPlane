#include "Plane.h"

Plane::Plane() {
	pos[0] = 3.0;
	pos[1] = 0.3;
	pos[2] = 0.0;

	ppos[0] = 3.0;
	ppos[1] = 0.3;
	ppos[2] = 0.0;

	vel[0] = 0.5;
	vel[1] = 0.0;
	vel[2] = 0.0;

	pvel[0] = 0.0;
	pvel[1] = 0.0;
	pvel[2] = 0.0;

	radio1 = 0.3;
	radio2 = 0.3;

	accUser[0] = 0.0;
	accUser[1] = 0.0;
	accUser[2] = 0.0;

	acc[0] = 0.0;
	acc[1] = 0.0;
	acc[2] = 0.0;

	deltaT = 0.001;

	accIncrement = 100;

	move = true;
}

void Plane::SetNormalMaterial(void) {
	// Emerald
	GLfloat mat_spec[] = { 0.633, 0.727811, 0.633, 1.0 };
	GLfloat mat_shiny[] = { 0.6 };
	GLfloat mat_amb[] = { 0.0215, 0.1745, 0.0215, 1.0 };
	GLfloat mat_dif[] = { 0.07568, 0.61424, 0.07568, 1.0 };

	// SET material properties
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
}

void Plane::SetCollisionMaterial(void) {
	// RED
	GLfloat mat_spec[] = { 0.393548, 271906, 0.166721, 1.0 };
	GLfloat mat_shiny[] = { 0.2 };
	GLfloat mat_amb[] = { 0.8125, 0.1275, 0.054, 1.0 };
	GLfloat mat_dif[] = { 0.914, 0.2284, 0.18144, 1.0 };

	// SET material properties
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
}

bool Plane::Collision(float x, float y, float z, float radio) {

	float distance = sqrt((pos[0] - 0.0) * (pos[0] - 0.0) + (pos[1] - 0.0) * (pos[1] - 0.0) + (pos[2] - 0.0) * (pos[2] - 0.0));

	if (distance < (radio + radio2)) {
		return true;
	}

	return false;
}

void Plane::ToggleMove()
{
	move = !move;
}

void Plane::Up()
{
	accUser[1] += 100;
}

void Plane::Down()
{
	accUser[1] -= 100;
}

void Plane::Left()
{
	accUser[2] += 100;
}

void Plane::Right()
{
	accUser[2] -= 100;
}

void Plane::Fly() {
	SetNormalMaterial();

	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glutWireSphere(radio1, 8, 8);
	glutSolidTeapot(radio1);
	glPopMatrix();

	float distance = sqrt((pos[0] - 0.0) * (pos[0] - 0.0) + (pos[1] - 0.0) * (pos[1] - 0.0) + (pos[2] - 0.0) * (pos[2] - 0.0));

	if (move) {
		// Acceleration
		acc[0] = -0.1 + accUser[0];
		acc[1] = 0.0 + accUser[1];
		acc[2] = 0.0 + accUser[2];

		accUser[0] = 0.0;
		accUser[1] = 0.0;
		accUser[2] = 0.0;

		// Velocity
		for (int i = 0; i < 3; i++) {
			vel[i] = pvel[i] + acc[i] * deltaT;
		}

		//Position
		for (int i = 0; i < 3; i++) {
			pos[i] = ppos[i] + vel[i] * deltaT;
		}
	}

	if (Collision(0.0, 0.0, 0.0, radio1)) {
		SetCollisionMaterial();
	}

	// Movable teapot
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glutWireSphere(radio2, 8, 8);
	glutSolidTeapot(radio2);
	glPopMatrix();

#pragma region Tiles
	glPushMatrix();
	SetCollisionMaterial();
	glTranslatef(4.0, -0.25, 4.0);
	glScalef(8.0, 0.5, 8.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	SetNormalMaterial();
	glTranslatef(4.0, -0.25, -4.0);
	glScalef(8.0, 0.5, 8.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	SetCollisionMaterial();
	glTranslatef(-4.0, -0.25, -4.0);
	glScalef(8.0, 0.5, 8.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	SetNormalMaterial();
	glTranslatef(-4.0, -0.25, 4.0);
	glScalef(8.0, 0.5, 8.0);
	glutSolidCube(1.0);
	glPopMatrix();
#pragma endregion

	for (int i = 0; i < 3; i++) {
		ppos[i] = pos[i];
		pvel[i] = vel[i];
	}
}

void Plane::Reset() {
	pos[0] = 3.0;
	pos[1] = 0.3;
	pos[2] = 0.0;

	ppos[0] = 3.0;
	ppos[1] = 0.3;
	ppos[2] = 0.0;

	vel[0] = 0.5;
	vel[1] = 0.0;
	vel[2] = 0.0;

	pvel[0] = 0.0;
	pvel[1] = 0.0;
	pvel[2] = 0.0;
}

Plane::~Plane() {}
