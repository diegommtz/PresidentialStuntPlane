#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

class Ring
{
public:
	/// <summary>
	/// current position
	/// </summary>
	float pos[3];

	/// <summary>
	/// radius of the ring
	/// </summary>
	float radius;

	/// <summary>
	/// thickiness of the ring
	/// </summary>
	float thick;

	/// <summary>
	/// Distance from the plane
	/// </summary>
	float planeDistance;

	/// <summary>
	/// Rotatioon on Y axis
	/// </summary>
	float rotY;

	Ring();
	bool CheckCollision(float planePos[3], float planeRadius);
	void SetRandPosition(float planePos[3]);
	void Draw();
	~Ring();
};

