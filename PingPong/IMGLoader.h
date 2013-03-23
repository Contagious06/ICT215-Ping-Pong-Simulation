/**
	Author: Matthew Vlietstra
	FileName: IMGLoader.h
	Version: 0.1
	Purpose: 

	Description:

*/

#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <stdlib.h>
#include "GL\glut.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAXROW 250
#define MAXCOL 200

int r,c;
typedef unsigned char pixel;
pixel* loadIMG(char fileName[], const int xMax, const int yMax);

#endif