/**
	Author: Matthew Vlietstra
	FileName: Controls.h
	Version: 0.1
	Purpose: Provides various input methods used to control aspects of the program.

	Description:

*/

#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdlib.h>
#include "gl/glut.h" 
#include "Menu.h"
#include <ctype.h>
#include "Objects.h"
#include "MenuItems.h"
#include "Misc.h"

//	<Movement Shizzles>
int keys[256]; //An array to keep track of keys pressed :)
//	</Movement Shizzles>

void kbSpecialFunc(int key, int x, int y);
void kbUp(unsigned char key, int x, int y);
void kbDown(unsigned char key, int x, int y);
void centerMouse();
void checkKeyPressed();
void passiveMouse(int x, int y);
void mouseFunc(int button, int state, int x, int y);

#endif