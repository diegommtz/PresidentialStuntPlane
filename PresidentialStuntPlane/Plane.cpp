#include "Plane.h"

Plane::Plane() {
	posFixed[0] = 0.0;
	posFixed[1] = 0.0;
	posFixed[2] = 0.0;

	pos[0] = 3.0;
	pos[1] = 0.3;
	pos[2] = 0.0;

	ppos[0] = 3.0;
	ppos[1] = 1.0;
	ppos[2] = 0.0;

	vel[0] = 0.5;
	vel[1] = 0.0;
	vel[2] = 0.0;

	pvel[0] = 0.0;
	pvel[1] = 0.0;
	pvel[2] = 0.0;

	radio1 = 0.8;
	radio2 = 0.3;

	accUser[0] = 0.0;
	accUser[1] = 0.0;
	accUser[2] = 0.0;

	acc[0] = 0.0;
	acc[1] = 0.0;
	acc[2] = 0.0;

	deltaT = 0.0001;

	move = true;

	xRot = 0.f;
	yRot = 0.f;
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

void Plane::Fly() {
	SetNormalMaterial();
	if (move) {
		// Acceleration
		acc[0] = -9.81 + accUser[0];
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

	// Movable teapot
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);

	glRotatef(-xRot, 0, 0, 1);		// Rotar en z es tiltUp/Down
	glRotatef(yRot, 1, 0, 0);		// Rotar en x es left/right

	glutWireSphere(radio2, 8, 8);
	glutSolidTeapot(radio2);

	glPopMatrix();

	// Tiles
	{
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
	}
	// End Tiles

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
	ppos[1] = 1.0;
	ppos[2] = 0.0;

	vel[0] = 0.5;
	vel[1] = 0.0;
	vel[2] = 0.0;

	pvel[0] = 0.0;
	pvel[1] = 0.0;
	pvel[2] = 0.0;
}

void Plane::TiltUp() {
	if(xRot < 40)
		xRot++;
}

void Plane::TiltDown() {
	if (xRot > -40)
		xRot--;
}

void Plane::TiltLeft() {
	if (yRot < 50)
		yRot++;
}

void Plane::TiltRight() {
	if (yRot > 50)
		yRot--;
}

Plane::~Plane() {}
