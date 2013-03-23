#include "Misc.h"

float RGB(int x)
{
	float y = 0.0;
	if(x != 0)
		y = (float)x/255.0;
	return y;
}

float degToRad(float degrees)
{
	return(degrees * 3.1415926535/180); //www.teacherschoice.com.au/Maths_Library/Angles/Angles.htm
}

void pauseGame()
{
	glClearColor(RGB(0xFF), RGB(0xFF), RGB(0xFF), 0);
	gameIsPaused = 1;
	
	glutReshapeWindow(glutGet(GLUT_INIT_WINDOW_WIDTH)+1, glutGet(GLUT_INIT_WINDOW_HEIGHT));
}

void ballBounce()
{
	ball.location[0] = 6.5;
	ball.location[1] = 20;
	ball.location[2] = 5;

	ball.velocity[0] = 0;
	ball.velocity[1] = 1;
	ball.velocity[2] = 0;

}

void resetBall()
{
	ball.location[0] = 12.5;
	ball.location[1] = 7;
	ball.location[2] = 1;

	ball.velocity[0] = 0;
	ball.velocity[1] = 10;
	ball.velocity[2] = 35;
}