#include "Objects.h"

///Draws a net...
void drawNet()
{
 	int x = 2, y = 2;
	float test;
	float startX = 0, startY = 0, startZ = 2;

	glColor3f(RGB(0xDD), RGB(0xDD), RGB(0xDD));
	//Right Side of net
	glBegin(GL_POLYGON);
		glVertex3f(startX,			startY+2,	startZ);
		glVertex3f(startX,			startY,		startZ);
		glVertex3f(startX+0.3,		startY,		startZ);
		glVertex3f(startX+0.3,		startY+2,	startZ);	
	glEnd();

	//Left Side of net
	glBegin(GL_POLYGON);
		glVertex3f(startX+25.7,			startY+2,	startZ);
		glVertex3f(startX+25.7,			startY,		startZ);
		glVertex3f(startX+26.0,		startY,		startZ);
		glVertex3f(startX+26.0,		startY+2,	startZ);	
	glEnd();

	//Top Of Net
	glBegin(GL_POLYGON);
		glVertex3f(startX,		startY+2,	startZ);
		glVertex3f(startX,		startY+2.3,		startZ);
		glVertex3f(startX+26,		startY+2.3,		startZ);
		glVertex3f(startX+26,		startY+2,	startZ);		
	glEnd();


	//Grid
	test = 0;
	for(y=0; y <= 5; y++) 
	{
		glPushMatrix();
			for(x=0; x <= 63; x++)
			{

				glTranslated(0.4,test,0);
				glBegin(GL_POLYGON); 
					glColor3f(RGB(0x7D), RGB(0x9A), RGB(0x7C));
					glVertex3f(startX,		startY-0.02,	startZ);
					glVertex3f(startX,		startY+0.2,		startZ);
					glVertex3f(startX+0.2,	startY+0.2,		startZ);
					glVertex3f(startX+0.2,	startY-0.02,	startZ);
				glEnd();
				test = 0;
			}
		glPopMatrix();
		test = 0.4*(float)y;
	}
	//glEnd();
}

///Draws the tableand then calls the net draw function...
void drawTable()
{
	//TableTopDown
 	glBegin(GL_POLYGON); 
		glColor3f(RGB(0x6D), RGB(0x8A), RGB(0x6C));
		glVertex3f(0.3,	-0.01,	0);
		glVertex3f(0.3,	-0.01,	26);
		glVertex3f(25.7,	-0.01,	26);
		glVertex3f(25.7,	-0.01,	0);
	glEnd();

	//WhiteLines
 	glBegin(GL_POLYGON); 
		glColor3f(1.0,		1.0,		1.0);
		glVertex3f(0,	-0.011,		0.0);
		glVertex3f(0,	-0.011,		26.3);
		glVertex3f(26,		-0.011,		26.3);
		glVertex3f(26,		-0.011,		0.0);
	glEnd();

	//TableTopUp
 	glBegin(GL_POLYGON); //Plane
		glColor3f(RGB(0x7A), RGB(0x7A), RGB(0x6C));
		glVertex3f(0.3,-0.01,0);
		glVertex3f(0.3,26,0);
		glVertex3f(25.7,26,0);
		glVertex3f(25.7,-0.01,0);
	glEnd();

	//WhiteLines
 	glBegin(GL_POLYGON); //Plane
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.0,0.0,-0.01);
		glVertex3f(0.0,26.3,-0.01);
		glVertex3f(26,26.3,-0.01);
		glVertex3f(26,0.0,-0.01);
	glEnd();

	//Net
	drawNet();
}

/** 
 * This method uses methods in the glm.c 
 * file to read the racket obj and display it.
 */
void drawRacket(float x, float y, float z)
{
	static GLMmodel* pmodel = NULL;

	glPushMatrix();
	//glRotatef(90,1.0,0.0,0.0);
	glTranslated(x,y,z);
	//glutSolidSphere(1,30,30);
	glColor3f(RGB(0xFF), RGB(0xFF), RGB(255));
    if (!pmodel) {
        pmodel = glmReadOBJ("racket3.obj");
        if (!pmodel) exit(0);
		glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
		glmScale(pmodel,2);
	}
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

///Draws the ping pong ball at the location specified by the ball struct
void drawBall()
{
	glPushMatrix();
		glTranslated(ball.location[0], ball.location[1], ball.location[2]);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidSphere(ball.radius,30,30);
	glPopMatrix();
}

///Draws the ping pong balls shadow at the location specified by the ball struct
void drawBallShadow()
{
	int i;
	
	glPushMatrix();
	glTranslated(ball.location[0], 0.2, ball.location[2]);
	for(i = 0; i < 4; i++)
	{
		glRotated(90.0, 0.0, 1.0, 0.0);
 		glBegin(GL_POLYGON); 
				glColor3f(0.0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.0);
				glColor3f(RGB(0x6D), RGB(0x8A), RGB(0x6C));
				
			glVertex3f(0,		0.0,		0.5);
			glVertex3f(0.5,		0.0,		0.5);
			glVertex3f(0.5,		0.0,		0.0);
		glEnd();
	}
	glPopMatrix();
}

///Draws the rackets shadow at the location specified by the racket struct
void drawRacketShadow()
{
	int i;
	
	glPushMatrix();
	glTranslated(racket.location[0], 0.2, racket.location[2]);
	for(i = 0; i < 4; i++)
	{
		glRotated(180.0, 0.0, 1.0, 0.0);
 		glBegin(GL_POLYGON); 
				glColor3f(0.0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.0);
				glColor3f(RGB(0x6D), RGB(0x8A), RGB(0x6C));
				
			glVertex3f(0,		0.0,		0.5);
			glVertex3f(0.5,		0.0,		0.5);
			glVertex3f(2.0,		0.0,		0.0);
		glEnd();


 		glBegin(GL_POLYGON); 
				glColor3f(0.0,		0.0,		0.0);
			glVertex3f(0,		0.0,		0.0);
				glColor3f(RGB(0x6D), RGB(0x8A), RGB(0x6C));
				
			glVertex3f(0,		0.0,		0.5);
			glVertex3f(-0.5,		0.0,		0.5);
			glVertex3f(-2.0,		0.0,		0.0);
		glEnd();
		
	}
	glPopMatrix();
}

///Draws the balls and rackets shadow...
void drawShadows()
{
	drawRacketShadow();
	drawBallShadow();
}

void drawPlane()
{
	//Draw Plane
	glPushMatrix();
		glTranslated(12.5,-0.02,12.5);

 		glBegin(GL_POLYGON); 
			glColor3f(RGB(0x6D), RGB(0x8A), RGB(0x6C));
			glVertex3f(-50,	-0.02,	-50);
			glVertex3f(-50,	-0.02,	50);
			glVertex3f(50.0,	-0.02,	50);
			glVertex3f(50.0,	-0.02,	-50);
		glEnd();
	glPopMatrix();
}