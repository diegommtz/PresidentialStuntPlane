#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include"CG_Tec.h";

class Terrain
{
public:
	Terrain();
	void Build();
	~Terrain();
};
