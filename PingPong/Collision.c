#include "Collision.h"

///Collision Detection between spheres. Need the absolute values.
int sphereCollisionDetection(vector3Df aLocation, float aRadius, vector3Df bLocation, float bRadius)
{
	GLfloat  a, b, c, h;
	a = aLocation[0] - bLocation[0];
	b = aLocation[1] - bLocation[1];
	c = aLocation[2] - bLocation[2];

	h = a*a + b*b + c*c; //3D pythagoras: www.odeion.org/pythagoras/pythag3d.html
	
	if(aRadius * bRadius >= h) //Doesn't use the square root function (More efficient)
	{
		return(1);
	}

	return(0);
}

///Determines if a box has collided with a sphere
int boxAndSpehereCollision(	obj *sphere,		//The sphere itself
							const float location[3],	//Location xyz of sphere (3D box)
							const float XYZ[3])		//Length Width Height							
{
	int index, j;
	int collided = 0;
	float	x1, x2, y1, y2, z1, z2;

	x1 = location[0]-(XYZ[0]*0.5);
	x2 = location[0]+(XYZ[0]*0.5);

	y1 = location[1]-(XYZ[1]*0.5);
	y2 = location[1]+(XYZ[1]*0.5);

	z1 = location[2]-(XYZ[2]*0.5);
	z2 = location[2]+(XYZ[2]*0.5);

	if(y1 <= sphere->location[1]+sphere->radius &&sphere->location[1]-sphere->radius <= y2)
	{
		if(x1 <= sphere->location[0]+sphere->radius && sphere->location[0]-sphere->radius <= x2)
		{
			if(z1 <= sphere->location[2]+sphere->radius && sphere->location[2]-sphere->radius <= z2)
			{
				return 1; //The Sphere did collide with the box
			}
		}
	}
	return 0; //The sphere did not collide with the box
}

//Epic Collision Detection :)
///Determines which direction the sphere collided with object and acts accordingly with the coef
int collision222(obj *temp, const float location[3], const float XYZ[3], float coef)
{
	int y, i;

	if(boxAndSpehereCollision(temp, location, XYZ))
	{
		y = -1;

		for(i = 0; i < 3; i++)
		{
			temp->location[i] = temp->oldLocation[i];

			if(!boxAndSpehereCollision(temp, location, XYZ) && y == -1)
			{
				y = i;
			}
		}

		temp->velocity[y] = coef*temp->velocity[y];
		return 1; //If the ball did collide
	}
	return 0; //If the ball didn't collide
}

///Calls the collision detection functions for the table tops & racket
void collisionDetection()
{
	//y Floor - down
	//const float location[] = {12.5, -0.1, 13}; //Center of Object
	//const float XYZ[] = {25, 0.4, 26};
	const float location[] = {12.5, -0.1, 13}; //Center of Object
	const float XYZ[] = {25, 0.4, 26};
	int i = 1;

	//Up
	const float location2[] = {12.5, 13, -0.1};
	const float XYZ2[] = {25.0, 26.0, 0.4};

	const float RacketBounding[] = {3.7, 2, 3};

	const float netLocation[] = {13, 2.5, 2};
	const float NetXYZ[] = {26.0, 5.0, 0.4};


	float ballOldVelocity[3];

	float tempy;
	obj lolcat;
	int y = 0;

	//testtest();
	//boxCollisionDetect(location, XYZ, 0.8, &ball, 0);	



	collision222(&ball, tableDown.center, tableDown.XYZ, tableDown.coef);
	collision222(&ball, tableUp.center, tableUp.XYZ, tableUp.coef);

	if(collision222(&ball, net.center, net.XYZ, net.coef))
	{
		printf("Net Collision!!!\n");
	}
	
	if(collision222(&ball, racket.location, RacketBounding, -1.0))
	{
		for(i = 0; i < 3; i++)
		{
			ballOldVelocity[i] = ball.velocity[i];
		}
		

		//ball.velocity[0] = ball.velocity[0]+(racket.velocity[0]*1.5);
		//ball.velocity[1] = ball.velocity[1]+10;
		//ball.velocity[2] = ball.velocity[2]+(racket.velocity[2]*1.5);

		ball.velocity[0] = ball.velocity[0]+(racket.velocity[0]*1.5);
		ball.velocity[1] = -(ball.velocity[1]+(racket.velocity[2]*1.6));
		ball.velocity[2] = ball.velocity[2]+(racket.velocity[2]);
		
		
		racket.velocity[0] = -(ballOldVelocity[0]*0.5); // Move the racket back (Prevents another collision, buggy)
		//racket.velocity[1] = -(ballOldVelocity[1]*0.5);
		racket.velocity[2] = -(ballOldVelocity[2]*0.5);


	}


	//Old Racket Collision Detection using spheres
	////boxCollisionDetect(location, XYZ, 0.8, &ball);

	//if(sphereCollisionDetection(ball.location, ball.radius, racket.location, racket.radius))
	//{
	//	if(ball.location[2] >= racket.location[2]-2)
	//	{
	//		//ball.location[2] = racket.location[2]-40;
	//		ball.velocity[0] =-ball.velocity[0]+racket.velocity[0];
	//		ball.velocity[1] =-ball.velocity[1]+20;
	//		ball.velocity[2] =-ball.velocity[2]+racket.velocity[2]-25;
	//	}
	//}

	return;
}

///Need to be updated to the new collision detection method.
void racketCollision()
{

	//const float location[] = {12.5, -0.1, 13}; //Center of Object
	//const float XYZ[] = {25, 0.4, 26};


	if (racket.location[0] <= 0.0)
	{
		racket.velocity[0] = 0;
		racket.location[0] = 0;
	}
	else if (racket.location[0] >= 25.0)
	{
		racket.velocity[0] = 0;
		racket.location[0] = 25;
	}
	
	if (racket.location[2] <= 20.0)
	{
		racket.velocity[2] = 0;
		racket.location[2] = 20;
	}
	else if (racket.location[2] >= 32.0)
	{
		racket.velocity[2] = 0;
		racket.location[2] = 32;
	}

	if (racket.location[1] <= 2.0)
	{
		racket.velocity[1] = 0;
		racket.location[1] = 2;
	}
	else if (racket.location[1] >= 10.0)
	{
		racket.velocity[1] = 0;
		racket.location[1] = 9.9;
	}
	return;
}