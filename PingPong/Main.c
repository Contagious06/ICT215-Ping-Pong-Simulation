/*
Author: Matthew Vlietstra
Version: 0.1

References:

*/

#include "Objects.h"
#include <stdlib.h>
#include "gl/glut.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
//#include "glm.h"
//#include "assert.h"
#include "MenuItems.h"
#include "Misc.h"
#include "Controls.h"
#include "Collision.h"
#include "IMGLoader.h"

#define WINDOW_NAME "Ping Pong"

//	<Prototypes>
void display(void);
void myReshape(int w, int h);
void camera();
void mouseFunc(int button, int state, int x, int y);
void idleFunc();
//void kbSpecialFunc();
//	</Prototypes>

void initializeVariables()
{
	gravity = 1;
	// <Racket>
	gameIsPaused = 1;
	gravityIsOn = 1;


	img = NULL;
	exitMenu = 0;

	friction = 0.10;

	racket.location[0] = 12.5;
	racket.location[1] = 10;
	racket.location[2] = 35;
	racket.radius = 20;
	racket.mass = 0.03;

	racket.velocity[0] = 0;
	racket.velocity[1] = 0;
	racket.velocity[2] = 0;
	// </Racket>

	// <Ball>
	resetBall();
	//ball.location[0] = 12.5;
	//ball.location[1] = 20;
	//ball.location[2] = 2;

	//ball.velocity[0] = 0;
	//ball.velocity[1] = -30;
	//ball.velocity[2] = -20;

	ball.radius = 0.5;
	ball.mass = 0.01;
	// </Ball>

	// <Net>
	net.center[0] = 13;
	net.center[1] = 2.5;
	net.center[2] = 2;
	
	net.XYZ[0] = 26.0;
	net.XYZ[1] = 5.0;
	net.XYZ[2] = 0.4;

	net.coef = -0.3;

	// </Net>


	// <TableUp>
	tableUp.center[0] = 12.5;
	tableUp.center[1] = 13;
	tableUp.center[2] = -0.1;
	
	tableUp.XYZ[0] = 25.0;
	tableUp.XYZ[1] = 26.0;
	tableUp.XYZ[2] = 0.4;

	tableUp.coef = -0.8;
	// </TableUp>
	

	// <TableDown>
	
	tableDown.center[0] = 12.5;
	tableDown.center[1] = -0.1;
	tableDown.center[2] = 13;
	
	tableDown.XYZ[0] = 70;
	tableDown.XYZ[1] = 0.4;
	tableDown.XYZ[2] = 70;

	//tableDown.XYZ[0] = 25;
	//tableDown.XYZ[1] = 0.4;
	//tableDown.XYZ[2] = 26;

	tableDown.coef = -0.8;


	// </TableDown>
}

int main()
{
	//setUpScreen();
	initializeVariables();
	mainMenu(); //Setup the main menu

	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //For some reason enabling double buffering messes up collision detection/the ball doesn't stop moving.... i assume it's because single buffering calls idle func less or something...
	glutInitWindowSize(640, 480);
	glutCreateWindow( WINDOW_NAME );
	glutReshapeFunc(myReshape);
	
	glutDisplayFunc(display);
		
	glClearColor(RGB(0x4A), RGB(0x77), RGB(0xD5), 0);

	glutSpecialFunc(kbSpecialFunc);
	glutKeyboardFunc(kbDown);
	glutKeyboardUpFunc(kbUp);
	glutIdleFunc(idleFunc);
	glutMouseFunc(mouseFunc);	

	pauseGame();

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
}

void camera()
{
		//Front View
		gluLookAt(	12.5,		10.0,		50.0, //Cam Location
					12.5,	0.0,	0.0, //LookAt
					0.0,	1.0,	0.0	);


		//Site View
		//gluLookAt(	-20.5,		1.0,		12.0, //Cam Location
		//			12.5,	0.0,	12.0, //LookAt
		//			0.0,	1.0,	0.0	);

	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	

	checkKeyPressed();

	if(gameIsPaused)
	{
		printMenu();
		glFlush();
		glutSwapBuffers();
		return;
	}
	
	camera();
	drawBall();
	drawShadows();
	drawTable();

	drawPlane();

	glEnable(GL_LIGHTING);
	drawRacket(racket.location[0], racket.location[1], racket.location[2]);
		
	glDisable(GL_LIGHTING);
	
		
	//glutSetCursor(GLUT_CURSOR_NONE); //Gets rid of the cursor (it's annoying..)

	glFlush();

	glutSwapBuffers();
		
	return;
}

/** 
 * When the window is resized this is called...
 */
void myReshape(int width, int height)
{
   //www.nehe.gamedev.net/data/lessons/lesson.asp?lesson=01
	if (height==0)								// Prevent A Divide By Zero By
	{
		height=1;							// Making Height Equal One
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window

	if(gameIsPaused)
	{
		gluOrtho2D(0.0,768.0, 0.0,480.0);
		glutReshapeWindow(640, 480);
	}
	else
	{
		gluPerspective(45.0f,((GLfloat)width)/((GLfloat)height+40),0.01f,100.0f);
		glutReshapeWindow(768,480);
	}
	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();
}

/** 
 * Adds graivity to y
 */
float forces(int i, int j)
{
	if(!1) //
		return(0.0);
	else if (j==1)
		return(-gravity);
	else
		return(0.0);
}

/** 
 * Adds graivity to y and frictions... needs testing......
 */
float forces222(int i, int j, float velocity)
{
	float frict = 1;
	if(velocity > 0)
	{
		frict = -friction;
	}
	else if(velocity < 0)
	{
		frict = friction;
	}
	//friction
	
	if(j==1) //Y, so applie gravity + friction
	{
		return((-(gravity-frict)));
	}

	return(frict);
}


/** 
 * Text book Example on particle physics (Interactive Computer Graphics A Top Down Approach, fith edition PG 574),
 * adapted to work with spheres & incorparate better collision detection
 */
void idleFunc()
{
	static float lastTime = 0.0f, presentTime = 0.0f;
	static abcd = 0;
	int i = 0, j;
	float dt;

	presentTime = glutGet(GLUT_ELAPSED_TIME);

	if(gameIsPaused)
	{
		glutPostRedisplay();
		lastTime = presentTime;
		return;
	}

	dt = 0.001*(presentTime - lastTime);
	//printf(">%d\n", dt);
	//abcd++;
	//printf("%d %f\n", abcd, dt);
	//racket.location[1]+=dt*racket.velocity[1];

	for(j=0; j<3;j++)
	{
		ball.oldLocation[j] = ball.location[j];

		ball.location[j]+=dt*ball.velocity[j];
		ball.velocity[j]+=dt*forces222(i, j, ball.velocity[j])/ball.mass;
		//ball.velocity[j]+=dt*forces222(i, j, ball.velocity[j])/ball.mass;
		//ball.velocity[j] = ball.velocity[j] * 0.95;
		//printf("%f\n",spheres[i].location[j]);

		
		racket.location[j]+=dt*racket.velocity[j];
		racket.velocity[j]+=dt*forces(i, j)/racket.mass;
		
		

		//racket.velocity[j] = racket.velocity[j] * 0.95; //slow down the racket
		//racket.velocity[j] = racket.velocity[j] * 0.98;
	}

	racket.velocity[0]*=0.9; 
	racket.velocity[2]*=0.9; 
	//racket.location[j]+=dt*racket.velocity[j];
	//racket.velocity[j]+=dt*forces222(i, j, racket.velocity[j])/racket.mass;


	collisionDetection();
	racketCollision();

	/*
	//x
	racket.location[0]+=dt*racket.velocity[0];
	racket.velocity[0]+=dt*0.0/racket.mass;

	racket.velocity[0] = racket.velocity[0] * 0.95; //slow down the racket(Friction)

	//y
	racket.location[2]+=dt*racket.velocity[2];
	racket.velocity[2]+=dt*0.0/racket.mass;

	racket.velocity[2] = racket.velocity[2] * 0.95; //slow down the racket(Friction)
	*/

	


	if(ball.velocity[2] > 0)
	{
		if(ball.location[2] > racket.location[2]-10 && ball.location[2] < racket.location[2]+10)
		{
			if(racket.location[1] < ball.location[1])
			{
				//racket.velocity[1]=ball.velocity[1];
				racket.location[1] = ball.location[1];
			}

			//printf("lol");
		}
	}


	if(ball.location[1] >= 5)
	{
		//racket.location[1] = ball.location[1];
		//if(racket.location[1] <= ball.location[1]+2.5)
		//{
			//racket.velocity[1]+=ball.location[1]-racket.location[1];
		//}
	}

	

	//Need to change this to the new method of collision detection
	if(ball.location[2] <= -4.1 || ball.location[2] >= 50 || ball.location[1] <= -10.1)
	{
		//ball.location[0] = 12.5;
		//ball.location[1] = 5;
		//ball.location[2] = 3;

		//ball.velocity[1] = 30;
		//ball.velocity[0] = 0;
		//ball.velocity[2] = 20;

		//ball.radius = 0.5;
		//ball.mass = 0.01;

		resetBall();
	}

	lastTime = presentTime;
	glutPostRedisplay();
}