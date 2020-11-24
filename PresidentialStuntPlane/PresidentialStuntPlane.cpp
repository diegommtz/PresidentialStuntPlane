#include <Windows.h>	// Comment this line if Linux
#include<GL/gl.h>		
#include <GL/glut.h>
#include <stdlib.h>		// Library used for random method

#include <time.h>       /* time */
#include<string.h>
#include<vector>
#include "Plane.h"
#include "Terrain.h"
#include "Menu.h"
#include "Ring.h"
#include "Sphere.h"
#include "GameOver.h"

// Game manager
enum gameState { MainMenu, Play, Pause, GameOv } state;

Plane* plane;


//#include "TextureSetup.h"
//static GLuint name[1];
//RGBpixmap myTex;

void SetEmeraldMaterial(void) {
	//Emerald
	GLfloat mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f,1.0f };
	GLfloat mat_diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 1.0f };
	GLfloat mat_specular[] = { 0.633f, 0.727811f, 0.633f, 1.0f };
	GLfloat shine[] = { 0.6 * 128.0f };

	// Set material properties 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

//para los randompoints de las esferas
float rp1;
float rp2;
float rp3;
int numberSpheres = 5;
float r[100][3];

std::vector<Sphere> powerUps;
vector<Sphere> a;

#include "Terrain.h"

Terrain* terrain;
Menu* menu;
Ring* ring;
GameOver* gameOver;

int timeRemaining;
int totalTime;

void nRan() {
	srand(time(NULL));
	for (int i = 0; i < numberSpheres; i++) {
		rp1 = (float)((-10) + rand() % 21);
		rp2 = (float)(1 + rand() % (3 - 1));
		rp3 = (float)((-10) + rand() % 21);
		
		
		r[i][0] = rp1;
		r[i][1] = rp2;
		r[i][2] = rp3;
	}
}

//Cambia la posici�n de la esfera que tuvo colisi�n con el avi�n
void changePos(int thePos) {
	srand(time(NULL));
		rp1 = (float)((-10) + rand() % 21);
		rp2 = (float)(1 + rand() % (3 - 1));
		rp3 = (float)((-10) + rand() % 21);
		r[thePos][0] = rp1;
		r[thePos][1] = rp2;
		r[thePos][2] = rp3;
}

//SI SE USA ESTE, DESBLOQUER TIMER EN MAIN
static void Timer(int value) {
	//respawnFlag = !respawnFlag;
	/* initialize random seed: */
	srand(time(NULL));
	for (int i = 0; i < numberSpheres; i++) {
		rp1 = (float)((-2) + rand() % 5);
		rp2 = (float)(1 + rand() % (3 - 1));
		rp3 = (float)((-2) + rand() % 5);
		r[i][0] = rp1;
		r[i][1] = rp2;
		r[i][2] = rp3;
	}

	glutPostRedisplay();
	// 100 milliseconds
	glutTimerFunc(5000, Timer, 0);
}

static void PlaneTimer(int value) {
	
	if (state == Play) {
		timeRemaining--;
		totalTime++;
	}

	std::cout << "Time Remaining: " << timeRemaining << std::endl;
	glutTimerFunc(1000, PlaneTimer, 0);
}


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
	glEnable(GL_LIGHTING);

	srand(time(NULL));

	 //Creo objetos
	/*for (int i = 0; i < numberSpheres; i++) {
		rp1 = (float)((-2) + rand() % 5);
		rp2 = (float)(1 + rand() % (3 - 1));
		rp3 = (float)((-2) + rand() % 5);
		Sphere sphere(rp1,rp2,rp3);
		powerUps.push_back(sphere);
	}*/

	for (int i = 0; i < numberSpheres; i++) {
		Sphere sphere;
		powerUps.push_back(sphere);
	}

	//seteo objetos
	for (int i = 0; i < numberSpheres; i++) {
		powerUps[i].setCube();
	}

	
	//// initialize texture
	//InitializeTexture(myTex, &name[0], (char*)"C:/Users/ednamo/Desktop/TEC/energy.bmp");

	srand(time(NULL));
	for (int i = 0; i < numberSpheres; i++) {
		rp1 = (float)((-2) + rand() % 5);
		rp2 = (float)(1 + rand() % (3 - 1));
		rp3 = (float)((-2) + rand() % 5);

		cout << rp1 << " " << rp2 << " " << rp3 << endl;
		r[i][0] = rp1;
		r[i][1] = rp2;
		r[i][2] = rp3;
	}


	// Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);

	plane = new Plane();
	terrain = new Terrain();
	menu = new Menu();
	ring = new Ring();
	gameOver = new GameOver();
	state = MainMenu;

	timeRemaining = 20;
	totalTime = 0;
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

void renderText() {
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 50.0);

		glMatrixMode(GL_MODELVIEW);
		glScalef(.001, .001, .001);

		string timeRemainingStr = to_string(timeRemaining);
		const char* arr = timeRemainingStr.c_str();
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

void display(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	//Get camera's position based on plane
	float* camPosition = plane->GetCamPosition();
	float* planePos = plane->GetPosition();

	if(state != Play)
		glClearColor(0.0, 0.0, 0.0, 1.0);

	switch (state)
	{
	case MainMenu:
		gluLookAt(0, 0, 10, 0, 0, 0, 0.0, 1.0, 0.0);
		menu->Draw();
		break;
	case Play:

		glClearColor(.2, .85, .9, 1.0);

		gluLookAt(camPosition[0], camPosition[1], camPosition[2], plane->pos[0], plane->pos[1], plane->pos[2], 0.0, 1.0, 0.0);
		
		// Draw objects
		ring->Draw();
		terrain->Build();
		glPushMatrix();
			plane->Fly();
			glRotatef(-180, 0.0, 1.0, 0.0);
			glTranslatef(-0.07, 0.1, 0.0);
			renderText();
		glPopMatrix();

		// Ring Collisions
		if (ring->CheckCollision(planePos, plane->radio2))
		{
			ring->SetRandPosition(planePos);
			timeRemaining += 20;
		}
		
		//Dibuja esferas
		//SetEmeraldMaterial();
		glPushMatrix(); {
			for (int i = 0; i < numberSpheres; i++) {
				powerUps[i].draw(r[i][0], r[i][1], r[i][2]);
				//powerUps[i].sphereEnergy(r[i][0], r[i][1], r[i][2]);
			}
		}
		glPopMatrix();

		for (int i = 0; i < numberSpheres; i++) {//Error 2-4
			if (powerUps[i].collision(plane->GetPosition(), 0.3)) {

				//TODO: Aumentar la velocidad del avión

				changePos(i);
				break;
			}
		}

		if (timeRemaining <= 0)
			state = GameOv;

		break;
	case GameOv:
		gluLookAt(0, 0, 10, 0, 0, 0, 0.0, 1.0, 0.0);
		gameOver->Draw(totalTime);
		break;
	default:
		break;
	}	
	
	//if (a.size() > 0) {
	//	a[0].sphereEnergy(r[0][0], r[0][1], r[0][2]);
	//}


	//if (a.size() > 0) {
	//	if (a[0].collision(plane->GetPosition(), 0.3)) {
	//		//a.erase(a.begin());
	//		nRan();
	//		cout << "Borrado" << endl;
	//	}
	//}
	//

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
	case 'r':
		plane->Reset();
		break;
	case 'm':
		plane->ToggleMove();
		break;
	case 'q':
		plane->Debug();
		break;
	case ' ':
		if (state == MainMenu) {
			if (menu->leftOp)
				state = Play;
			else
				exit(0);
		}
		if (state == Play)
		{
			float* pos = plane->GetPosition();
			ring->SetRandPosition(pos);
		}
		if (state == GameOv) {			
				exit(0);
		}
		break;
	case 't':
		timeRemaining += 6;
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
		if (state == MainMenu)
			menu->leftOp = true;
		if (state == Play)
			plane->Left();
		break;
	case GLUT_KEY_RIGHT:
		if (state == MainMenu)
			menu->leftOp = false;
		if (state == Play)
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
	glutCreateWindow("Presidential Stunt Plane");

	// Additional initialization
	customInitialize();

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutSpecialFunc(processSpecialKeys);
	glutTimerFunc(1000, PlaneTimer, 0);

	//Timer(0);
	// Do main loop
	glutMainLoop();

	// Exit
	return 0;
}