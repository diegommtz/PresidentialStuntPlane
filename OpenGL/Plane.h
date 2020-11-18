#pragma once
#include <Windows.h>	// Comment this line if Linux
#include <gl\GL.h>
#include "glut.h"		//"glut.h" if local
#include <stdlib.h>		// Library used for random method

class Plane
{
public:
	/// <summary>
/// position of static sphere
/// </summary>
	float posFixed[3];

	/// <summary>
	/// current position
	/// </summary>
	float pos[3];

	/// <summary>
	/// previous position
	/// </summary>
	float ppos[3];

	/// <summary>
	/// current velocity
	/// </summary>
	float vel[3];

	/// <summary>
	/// previous velocity
	/// </summary>
	float pvel[3];

	/// <summary>
	/// acceleration
	/// </summary>
	float acc[3];

	/// <summary>
	/// step
	/// </summary>
	float deltaT = 0.0;

	/// <summary>
	/// radius of static sphere
	/// </summary>
	float radio1 = 0.0;

	/// <summary>
	/// radius of movable sphere
	/// </summary>
	float radio2 = 0.0;

	/// <summary>
	/// Determines wether movable sphere moves or not
	/// </summary>
	bool move = false;

	/// <summary>
	/// smoother movement
	/// </summary>
	float accUser[3] = { 0.0 };

	Plane();
	void SetNormalMaterial();
	void SetCollisionMaterial();
	void Fly();
	void Reset();
	~Plane();
};

