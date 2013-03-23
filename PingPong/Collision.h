/**
	Author: Matthew Vlietstra
	FileName: Collision.h
	Version: 0.1
	Purpose: Provides verious collision detection methods.

	Description:

*/


#ifndef COLLISION_H
#define COLLISION_H

#include <stdlib.h>
#include "gl/glut.h"
#include "Objects.h"
#include <stdio.h>

int sphereCollisionDetection(vector3Df aLocation, float aRadius, vector3Df bLocation, float bRadius);
int boxAndSpehereCollision(	obj *sphere, const float location[3], const float XYZ[3]);
int collision222(obj *temp, const float location[3], const float XYZ[3], float coef);
void collisionDetection();
void racketCollision();

#endif