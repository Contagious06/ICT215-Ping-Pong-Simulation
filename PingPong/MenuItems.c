#include "MenuItems.h"



void customFunction()
{
	
}

void aboutCustom()
{
	glColor3f(0.0, 0.0, 0.0);

	//printTextXY("Ping Pong", 200, 430, 8);
	//printTextXY("Coded by Matthew Vlietstra", 200, 400, 7);

	printnl("	Ping! Pong!, is a 3D simulator coded in C, which utilizes the API glut.\nThe purpose of this game is to simulate physics, aswell as allow the user(s) to change parameters \nthat effect the game i.e. gravity.\n \nCoded By Matthew Vlietstra (matthewvlietstra@gmail.com) \n \n \nReferences\n + OBJ Loader (glm.h & glm.c) - Nate Robins\n + particle physics (Adapted to work with spheres & added better collision detection) - Interactive\n   Computer Graphics, A top Down Approache(Fith Edition) PG 574, 1997 - 2000", 100, 430, 7, 15);
}


void exitIMG()
{


}

void exitCustomFunc()
{
	if(img == NULL)
	{
		img = loadIMG("200x250rgbR.raw", 200, 250);
	}
	glColor3f(RGB(0x00), RGB(0x00), RGB(0x00));
	printnl("Are you sure you want to exit?", 100, 430, 8, 15);

	//Image of myself, when the user left clicks on it the program exits
	glRasterPos2i( 300, 100 );
	glDrawPixels( MAXCOL, MAXROW, GL_RGB, GL_UNSIGNED_BYTE, img );

	printnl("Author: Matthew Vlietstra - matthewvlietstra@gmail.com\nLeft click on the image or select \"Yes\", then press enter to exit.", 230, 100, 7, 15);
}

void exitGame()
{
	exitMenu = 1;
	newMenu(100, 370, 30.0, 100.0, 1, exitCustomFunc);
	addMenuItem("No", mainMenu);
	addMenuItem("Yes", exit);
}

//Not The best Way of doing it.. but meh
void changeRes768x480(){glutReshapeWindow(768,480);}
void changeRes1024x640(){glutReshapeWindow(1024,640);}
void changeRes1152x720(){glutReshapeWindow(1152,720);}
void changeRes1280x800(){glutReshapeWindow(1280,800);}
void changeRes1440x900(){glutReshapeWindow(1440,900);}
void changeRes1920x1200(){glutReshapeWindow(1920,1200);}

void fullScreenMode()
{
	glutFullScreen	(	);
}

void resoultionMenu() //Need to find a better way of doing this...
{
	newMenu(100, 400, 30.0, 100.0, 1, customFunction);
	addMenuItem("768x480", changeRes768x480);
	addMenuItem("1024x640", changeRes1024x640);
	addMenuItem("1152x720", changeRes1152x720);
	addMenuItem("1280x800", changeRes1280x800);
	addMenuItem("1440x900", changeRes1440x900);
	addMenuItem("1920x1200", changeRes1920x1200);
	addMenuItem("Full Screen", fullScreenMode);
	addMenuItem("Back", mainMenu);
}

void enableDisableGrav()
{
	menuGravSelect = 3;
	gravityIsOn = !gravityIsOn;
	physicsMenu(); //Need to recall that menu to update the text
}

void enableDisableSideView()
{
	menuGravSelect = 2;
	sideViewEnabled = !sideViewEnabled;
	physicsMenu(); //Need to recall that menu to update the text
}

void increaseGrav()
{
	gravity+=0.5;
	menuGravSelect = 4;

	if(gravity > 5.0)
	{
		gravity = 1.0;
	}

	physicsMenu(); //Need to recall that menu to update the text
}

void increaseBallMass()
{
	menuGravSelect = 0;
	ballMass = ballMass + 0.01;

	if(ballMass > 3.0)
	{
		ballMass = 0.00;
	}
	physicsMenu();
}

void increaseRacketMass()
{
	menuGravSelect = 1;
	racketMass = racketMass + 0.01;

	if(racketMass > 3.0)
	{
		racketMass = 0.00;
	}
	physicsMenu();
}

void menuBack()
{


}

void physicsMenu()
{
	char gravOnOff[30];
	char grav[30];

	char sideView[30];

	//newMenu(100, 400, 30.0, 100.0, 1, customFunction);
	newMenuSelect(100, 400, 30.0, 100.0, 1, customFunction, menuGravSelect);




	sprintf(grav,"Gravity: %.2f", gravity);
	addMenuItem(grav, increaseGrav);


	//addMenuItem("Friction: ON", increaseGrav);

	addMenuItem("Back", options);
}


void controlsCustom()
{
	glColor3f(0.0, 0.0, 0.0);

	//printTextXY("Ping Pong", 200, 430, 8);
	//printTextXY("Coded by Matthew Vlietstra", 200, 400, 7);

	printnl("W - Moves the racket Forwards\nS - Moves the Racket Backwards\nD - Moves the racket to the right\nA - Moves the racket to the left\nR - Resets the ball\nB - Ball Bounce\n \nG & R - Reset Gravity\nG & R - Reset Gravity\nG & - - Decrease Gravity\nG & + - Increase Gravity\nC - Disable/Enable Collision Detection\nF & D - Disable/Reset Friction\nG & - - Decrease Friction\nG & + - Increase Friction\n \nEsc - Pauses the game/ allows the user to twink variables", 100, 430, 7, 15);
}

void controlsMenu()
{
	newMenu(20, 20, 30.0, 100.0, 1, controlsCustom);
	addMenuItem("Back", mainMenu);

}

void options()
{
	newMenu(100, 400, 30.0, 100.0, 1, customFunction);
	//addMenuItem("Resolution", resoultionMenu);
	addMenuItem("Controls", controlsMenu);
	//addMenuItem("Physics", physicsMenu);
	addMenuItem("Back", mainMenu);
}

void about()
{
	newMenu(20, 20, 30.0, 100.0, 1, aboutCustom);
	addMenuItem("Back", mainMenu);
}

void helpMenuCustom()
{
	glColor3f(RGB(0x00), RGB(0x00), RGB(0x00));
	printTextXY("You Need Help?!!!", 100, 400, 8);
	printnl("With our advanced AI, we are able to determine and help you with your predicament.\nPlease convey your predicament into your microphone, and we'll get back to you...\n \nShortly...", 100, 390, 7, 15);

}

void helpMenu()
{
	newMenu(20, 20, 30.0, 100.0, 1, helpMenuCustom);
	addMenuItem("Back", mainMenu);
}

void startGame()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(RGB(0x4A), RGB(0x77), RGB(0xD5), 0);
	gameIsPaused = 0;
	glutReshapeWindow(768,480);
}

void mainMenu()
{
	exitMenu = 0;
	newMenu(100, 400, 30.0, 100.0, 1, customFunction);
	addMenuItem("Start Simulation", startGame);
	//addMenuItem("Options", options);
	addMenuItem("Controls", controlsMenu);
	addMenuItem("About", about);
	addMenuItem("Help", helpMenu);
	addMenuItem("Exit", exitGame);
}