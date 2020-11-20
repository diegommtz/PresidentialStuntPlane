#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
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

	float accIncrement;

	/// <summary>
	/// Rotation degrees on X axis
	/// </summary>
	float rotX;

	/// <summary>
	/// Rotation degrees on Z axis
	/// </summary>
	float rotZ;

	/// <summary>
	/// Tilting degrees of the plane
	/// </summary>
	float visRot;

	/// <summary>
	/// Timer before returning tilt to original position
	/// </summary>
	int tiltTimer;

	/// <summary>
	/// Position of the camera
	/// </summary>
	float camPos[3];


	//DEBUG
	bool brPoint = false;
	void Debug();
	//TEMP vars

	Plane();
	void SetNormalMaterial();
	void SetCollisionMaterial();
	float* GetPosition();
	float* GetCamPosition();

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

