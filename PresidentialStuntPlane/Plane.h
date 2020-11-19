#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

class Plane
{
public:
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

	float accIncrement;

	Plane();
	void SetNormalMaterial();
	void SetCollisionMaterial();
	void Fly();
	void Reset();
	bool Collision(float x, float y, float z, float radio);
	void ToggleMove();
	void Up();
	void Down();
	void Left();
	void Right();
	~Plane();
};

