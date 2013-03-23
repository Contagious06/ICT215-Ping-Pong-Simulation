/**
	Author: Matthew Vlietstra
	FileName: Objects.h
	Version: 0.1
	Purpose: 

	Description:

*/

#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>
#include "gl/glut.h" 
#include "glm.h"
#include "Misc.h"

typedef float vector3Df[3];
typedef float vector2Df[2];
typedef int vector2Di[2];

typedef struct
{
	GLfloat location[3];
	GLfloat oldLocation[3];
	GLfloat velocity[3];
	GLfloat mass;
	GLfloat rotation[2];
	GLfloat radius;
}obj;

obj ball;
obj racket;

typedef struct
{
	GLfloat center[3];
	GLfloat XYZ[3];
	GLfloat mass;
	GLfloat coef;
}rect3D;

rect3D net;
rect3D tableDown;
rect3D tableUp;

void drawPlane();
void drawShadows();
void drawRacketShadow();
void drawBallShadow();
void drawBall();
void drawRacket(float x, float y, float z);
void drawTable();
void drawNet();

#endif