#include "Controls.h"

void centerMouse()
{
	glutWarpPointer((GLint)(glutGet(GLUT_WINDOW_WIDTH)/2), (GLint)(glutGet(GLUT_WINDOW_HEIGHT)/2));
}

void kbSpecialFunc(int key, int x, int y)
{
	if(gameIsPaused)
	{
		switch(key)
		{
		case GLUT_KEY_DOWN:
			incrementSelectedMenu();
			break;

		case GLUT_KEY_UP:
			decreaseSelectedMenu();
			break;
		}
	}
}

void kbUp(unsigned char key, int x, int y)
{
	keys[(int)tolower(key)] = 0;
}

void kbDown(unsigned char key, int x, int y)
{
	keys[(int)tolower(key)] = 1;
	//printf("%c ", key);
}

void mouseFunc(int button, int state, int x, int y)
{
	//printf("%d %d\n", x, y);
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && exitMenu == 1)
	{
		if(x >= 250 && y >= 130 && x <= 450 && y <= 380)
			exit(0);
	}
}

void checkKeyPressed()
{
	
	if(gameIsPaused)
	{
		if(keys[13]) //Enter
		{
			pressEnter();
			keys[13] = 0;
		}

	}
	else
	{
		
		if(keys[(int)'w'])
		{
			racket.velocity[2]--;
			//racket.location[2]-=0.5;
			racket.velocity[2] =-20.5;
			//keys[(int)'w'] = 0;
		}

		if(keys[(int)'s'])
		{
			racket.velocity[2]++;
			//racket.location[2]+=0.5;
			racket.velocity[2] =20.5;
			//keys[(int)'s'] = 0;
		}

		if(keys[(int)'d'])
		{
			racket.velocity[0]++;
			//racket.location[0]+=0.5;
			//racket.velocity[0] =20.5;
			//keys[(int)'d'] = 0;
		}

		if(keys[(int)'a'])
		{
			//racket.location[0]-=0.5;
			racket.velocity[0]--;
			racket.velocity[0] =-20.5;
			//keys[(int)'a'] = 0;
		}

		if(keys[(int)' '])
		{
			racket.velocity[1]+=3;
		}

		if(keys[(int)'r'] && !keys[(int)'g'])
		{
			resetBall();
		}

		if(keys[(int)'b'])
		{
			ballBounce();
		}

		//if(keys[(int)'r'] && keys[(int)'g'])
		//{
		//	gravity =  1;
		//}

		if(keys[(int)'g'] && keys[(int)'-']) //Decrease Grav
		{
			
			gravity-= 0.5;
			printf("Gravity Decrease! Now: %f \n", gravity);
			///keys[(int)'g'] = 0;
			keys[(int)'-'] = 0;
		}

		if(keys[(int)'g'] && keys[(int)'=']) //Increase Grav: + show u don't have to press shift
		{
			gravity+= 0.5;
			printf("Gravity Increase! Now: %f \n", gravity);
			//keys[(int)'g'] = 0;
			keys[(int)'='] = 0;
		}

		//if(keys[(int)'g'] && keys[(int)'d']) //+ show u don't have to press shift
		//{
		//	//gravity+= 0.5;
		//	gravityIsOn = !gravityIsOn;
		//	//keys[(int)'g'] = 0;
		//	keys[(int)'d'] = 0;
		//}

		if(keys[(int)'g'] && keys[(int)'r'] && !keys[(int)'='] && !keys[(int)'-']) //Reset Grav
		{
			gravity =  1.0;
			printf("Gravity Reset! Now: %f \n", gravity);
		}

		if(keys[(int)'f'] && keys[(int)'-']) //Decrease Friction
		{
			
			if(friction > 0 )
			{
				friction-= 0.1;
				printf("Friction Decrease! Now: %f \n", friction);
			}
			///keys[(int)'g'] = 0;
			keys[(int)'-'] = 0;
		}

		if(keys[(int)'f'] && keys[(int)'=']) //Increase Friction: + show u don't have to press shift
		{
			friction+= 0.1;
			printf("Friction Increase! Now: %f \n", friction);
			//keys[(int)'g'] = 0;
			keys[(int)'='] = 0;
		}

		if(keys[(int)'f'] && keys[(int)'d']) //Disable/Reset Friction
		{
			if(friction != 0.0)
				friction = 0.0;
			else
				friction = 0.09;
			
			//keys[(int)'g'] = 0;
			keys[(int)'d'] = 0;
		}

		if(keys[27]) //Esc
		{
			pauseGame();
			mainMenu();
			keys[27] = 0;
		}
	}

}

/*	Problem with this is when the centerMouse function is called glut 
 *	recalls this function,so ill use this method until i find a better 
 *	way of doing this...
*/
void passiveMouse(int x, int y) //called when the mouse is moved
{
	static float lastTime = 0.0f, presentTime = 0.0f;
	float dt;
	GLint centerIt = 0;
	int winX = glutGet(GLUT_WINDOW_WIDTH);
	int winY = glutGet(GLUT_WINDOW_HEIGHT);


	float tmpX, tmpY;

	presentTime = glutGet(GLUT_ELAPSED_TIME);

	if(gameIsPaused)
	{
		lastTime = presentTime;
		return;
	}
	
	dt = 0.001*((float)(presentTime - lastTime));
	//printf("Test%f\n", 30.0/(float)winX*x);

	//tmpX = 30.0/(float)winX*x; 
	//tmpY = 20.0/(float)(winY-200)*y;	
	
	tmpX = 30.0/(float)winX*x; 
	tmpY = 20.0/(float)(winY-200)*y;	

	racket.location[0] = tmpX;
	racket.location[2] = tmpY;



	//racket.velocity[0] = tmpX-(tmpX*0.5);
	//racket.velocity[2] = tmpY-(tmpY*0.5);
	//racket.velocity[0] = -(15 - tmpX);
	//racket.velocity[2] = -(10 - tmpY);

	//printf("%f %f\n", , );

	//racket.location[0] = x*dt*0.5;
	//racket.location[2] = y*dt*0.5;



	lastTime = presentTime;
	return;

	//Need to fix this up...
	if((GLint)(glutGet(GLUT_WINDOW_WIDTH)/2) > x)
	{
		racket.velocity[0]-=5;
		centerIt = 1;
	} 
	
	if((GLint)(glutGet(GLUT_WINDOW_WIDTH)/2) < x)
	{
		racket.velocity[0]+=5;
		centerIt = 1;
	}
	
	if((GLint)(glutGet(GLUT_WINDOW_HEIGHT)/2) > y) //Up: 500/2 = 250 > 249
	{
		racket.velocity[2]-=4;
		centerIt = 1;
	}
	
	if((GLint)(glutGet(GLUT_WINDOW_HEIGHT)/2) < y)
	{
		racket.velocity[2]+=4;
		centerIt = 1;
	}
	
	//if(centerIt){centerMouse();} //Center the mouse if it has moved
	
}

///*	Problem with this is when the centerMouse function is called glut 
// *	recalls this function,so ill use this method until i find a better 
// *	way of doing this...
//*/
//void passiveMouse(int x, int y) //called when the mouse is moved
//{
//	GLint centerIt = 0;
//	
//	if(gameIsPaused)
//		return;
//
//
//	//Need to fix this up...
//	if((GLint)(glutGet(GLUT_WINDOW_WIDTH)/2) > x)
//	{
//		racket.velocity[0]-=5;
//		centerIt = 1;
//	} 
//	
//	if((GLint)(glutGet(GLUT_WINDOW_WIDTH)/2) < x)
//	{
//		racket.velocity[0]+=5;
//		centerIt = 1;
//	}
//	
//	if((GLint)(glutGet(GLUT_WINDOW_HEIGHT)/2) > y) //Up: 500/2 = 250 > 249
//	{
//		racket.velocity[2]-=4;
//		centerIt = 1;
//	}
//	
//	if((GLint)(glutGet(GLUT_WINDOW_HEIGHT)/2) < y)
//	{
//		racket.velocity[2]+=4;
//		centerIt = 1;
//	}
//	
//	if(centerIt){centerMouse();} //Center the mouse if it has moved
//	
//}
//	</Controls>