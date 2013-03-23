/**
	Author: Matthew Vlietstra
	FileName: Menu.h
	Version: 0.1
	Purpose: To provide various methods for displaying a menu's & other things

	Description:
	This contains an array of function pointers, & an array of text.
	Thus the porgrammer can create a new menu, then add menu items which point to other methods which input new pointers & text.
	Thefor complex menu systems can be implemented.
*/


#ifndef MENU_H
#define MENU_H

#include <string.h>
#include "gl/glut.h"

#define MAX_MENU 10

int menuStartXY[2];
float menuHW[2];
int menuCount;
int menuEffect;
int selectedMenu;
int menuFade;
void *previousMenu(void);

float colour[3];
//void backObject;

enum MENU_EFFECTS {NO_EFFECT, MENU_FADE_EFFECT, etc};

void (*menuFuncArray[MAX_MENU])(void); //Array of function Pointers
void (*menuFuncPoint)(void); //Called when the menu is printed
char menuStringTxt[MAX_MENU][20]; //2 dimensional array of characters
void printTextXY(const char text[], int x, int y, int font);
void pressEnter();
void incrementSelectedMenu();
void decreaseSelectedMenu();

void newMenu(int x, int y, float height, float width, int effect, void *func);
void newMenuSelect(int x, int y, float height, float width, int effect, void *func, int select);
void addMenuItem(const char text[], void *func);
void printMenu();
void printnl(char text[], int x, int y, int font, int spacing);

#endif