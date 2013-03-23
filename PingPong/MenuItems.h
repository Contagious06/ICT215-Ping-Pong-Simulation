/**
	Author: Matthew Vlietstra
	FileName: MenuItems.h
	Version: 0.1
	Purpose: To display various menu's

	Description:
	This file implements the menu. It contains the various menuItems and so forth
*/

#ifndef MENUITEMS_H
#define MENUITEMS_H

#include <stdlib.h>
#include "gl/glut.h"
#include <stdio.h>
#include "Menu.h"
#include "Objects.h"
#include "Misc.h"
#include "IMGLoader.h"

void mainMenu();
void aboutCustom();
void exitIMG();
void exitCustomFunc();
void exitGame();
void physicsMenu();
void options();

int gravityIsOn;
float gravity;
float friction;
pixel *img;

int exitMenu;

float ballMass;
float racketMass;
	
int menuGravSelect;
int gameIsPaused;

int sideViewEnabled;


#endif