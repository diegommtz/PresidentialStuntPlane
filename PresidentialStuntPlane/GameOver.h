#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /* srand, rand */

using namespace std;

class GameOver
{
public:
	GameOver();
	void Draw(int totalTime);
	void CustomRenderText(string phrase);
	~GameOver();
};

