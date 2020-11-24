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

class Menu
{
public:
	
	/// <summary>
	/// left option selected?
	/// </summary>
	bool leftOp;

	/// <summary>
	/// left positive position of line vertex
	/// </summary>
	float leftVertex;

	/// <summary>
	/// right positive position of line vertex
	/// </summary>
	float rightVertex;

	Menu();
	void Draw();
	void CustomRenderText(string phrase);
	~Menu();
};