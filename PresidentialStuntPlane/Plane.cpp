#include "Plane.h"

#define PI 3.14159265358979
Mesh* myMesh;

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

	pvel[0] = 2.0;
	pvel[1] = 0.0;
	pvel[2] = 0.0;

	radio1 = 0.3;
	radio2 = 0.3;

	acc[0] = 0.0;
	acc[1] = 0.0;
	acc[2] = 0.0;

	deltaT = 0.001;

	accIncrement = 100;

	move = true;

	rotX = 0;
	rotZ = 0;
	visRot = 0;
	tiltTimer = 0;

	char arr[] = "C://Users/crl_s/OneDrive/Escritorio/Beriev_A50/BerievA50.obj"; // SOTO

	//char arr[] = "C://Users/ednamo/Desktop/Beriev_A50/BerievA50.obj"; //NAVA

	//char arr[] = "C://Users/diego/source/repos/objects/Beriev_A50/BerievA50.obj"; // DEUS

	char* file = &arr[0];

	myMesh = new Mesh(file);
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
	if (rotZ < 30)
		rotZ+=2;
}

void Plane::Down()
{
	if (rotZ > -30)
		rotZ-=1;
}

void Plane::Left()
{
	tiltTimer = 100;

	if (visRot > -45)
		visRot-=1;

	rotX -= 2;
}

void Plane::Right()
{
	tiltTimer = 100;

	if (visRot < 45)
		visRot+=2;

	rotX += 2;
}

void Plane::Debug() {
	Plane::brPoint = true;

	//Copy pastea esto en cualquier parte del código y pon un breakpoint. Al presionar Q se ejecuta.
	/*if (brPoint) {
		int a = 3;
		a++;
		brPoint = false;
	}*/
}

float* Plane::GetPosition() {
	return pos;
}

float* Plane::GetCamPosition() {
	return camPos;
}

void Plane::Fly() {
	SetNormalMaterial();

	/*
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glutWireSphere(radio1, 8, 8);
	glutSolidTeapot(radio1);
	glPopMatrix();
	*/

	float distance = sqrt((pos[0] - 0.0) * (pos[0] - 0.0) + (pos[1] - 0.0) * (pos[1] - 0.0) + (pos[2] - 0.0) * (pos[2] - 0.0));

	if (move) {

		// Velocity
		for (int i = 0; i < 3; i++) {
			vel[i] = pvel[i] + acc[i] * deltaT;
		}

		// Get velocity vector
		float totalVel = sqrt(pow(vel[0], 2) + pow(vel[1], 2) + pow(vel[2], 2));

		// Convert degrees to radians
		float angleZ = rotZ * PI / 180;
		float angleX = rotX * PI / 180;

		//Get velocities using trigonometric principles
		float xTempVel = totalVel * cos(angleZ);	//Velocity on x-z
		vel[0] = xTempVel * cos(angleX);
		vel[1] = totalVel * sin(angleZ);
		vel[2] = xTempVel * sin(angleX);

		//Position
		for (int i = 0; i < 3; i++) {
			pos[i] = ppos[i] + vel[i] * deltaT;
		}

		//Camera position
		float z = 5 * sin(angleX);
		float x = 5 * cos(angleX);

		camPos[0] = pos[0] - x;
		camPos[1] = pos[1];
		camPos[2] = pos[2] - z;

	}

	if (Collision(0.0, 0.0, 0.0, radio1)) {
		SetCollisionMaterial();
	}

	// Movable teapot
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);

	//Rotation
	glRotated(-rotX, 0, 1, 0);		// Rotation y - Left/Right
	glRotated(visRot, 1, 0, 0);		// Rotation x - Tilting to sides
	glRotated(rotZ, 0, 0, 1);		// Rotation z - Up/Down

	//Return side tilting to original rotation (timer)
	if (tiltTimer > 0) {
		tiltTimer--;
	}
	else {
		if (visRot > 0)
			visRot -= 0.1f;
		else if (visRot < 0)
			visRot += 0.1f;
	}

	glutWireSphere(radio2, 8, 8);
	myMesh->NormalizeMesh();
	//myMesh->DrawBoundingBox();
	glRotated(90, 0.0, 1.0, 0.0);
	myMesh->Draw();
	//glutSolidTeapot(radio2);
	glPopMatrix();

	//Update positions
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
