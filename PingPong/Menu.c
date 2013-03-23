#include "Menu.h"

/**
 * Same as newMenu, except that this has an extra parameter to select a specific menu item
 * The first menu is selected by default for newMenu.
*/
void newMenuSelect(int x, int y, float height, float width, int effect, void *func, int select) 
{
	newMenu(x, y, height, width, effect, func);
	selectedMenu = select; //Select a menu
}

/**
 * Empties/Prepaires for a new menu
*/
void newMenu(int x, int y, float height, float width, int effect, void *func) //void *object
{
	menuStartXY[0] = x;
	menuStartXY[1] = y;

	menuHW[0] = height;
	menuHW[1] = width;

	menuEffect = effect;
	menuCount = 0;
	selectedMenu = 0;
	menuFade = 1;

	colour[0] = 0.0;
	colour[1] = 0.0;
	colour[2] = 0.0;

	menuFuncPoint = func;
}

///Adds a new menu item, only needs to be called once per menu item.
void addMenuItem(const char text[], void *func)
{
	if(menuCount < MAX_MENU)
	{
		//menuFuncArray[menuCount]
		menuFuncArray[menuCount] = func; //The Function to call when the menu item is clicked/selected
		strcpy(menuStringTxt[menuCount], text); //Copy the text for the menu
		menuCount++; //Increment MenuCount	
	}
}

void incrementSelectedMenu() { selectedMenu++; }
void decreaseSelectedMenu() { selectedMenu--; }

void pressEnter()
{
	//previousMenu
	(*menuFuncArray[selectedMenu])(); //Excute the specific function that corresponds to the selected text.
}

/**
 *Prints text at a specified xy location as well as accepting a specified font.
 *Note this method loops until it find the \0 characer (same method that strcpy uses)
*/
void printTextXY(const char text[], int x, int y, int font)
{
	int i;
	glRasterPos2i(x, y);
	for (i = 0; text[i] != '\0'; i++) //Somewhat dangerous :)
		glutBitmapCharacter(font, text[i]); //GLUT_BITMAP_HELVETICA_18
}

/**
 *This method accepts a string of text as well as a location/ spacing, 
 *it then splits the text up when it finds a \n character - so that it can print text line by line
 *Thus it allows the user to print lines of text easily.
*/
void printnl(char text[], int x, int y, int font, int spacing)
{
	int i;
	int prev = 0;
	char *pch;
	char *str = strdup(text); //Duplicate the string

	pch = strtok (str,"\n");

	while (pch != NULL)
	{
		printTextXY(pch, x, y-=spacing, font);

		pch = strtok (NULL, "\n");
	}
}

///Just a basic rectange to indicate a selected menu item.
void rectangle()
{
    glBegin(GL_QUADS);
        glVertex2f(0.0,		0.0);
        glVertex2f(0.0,		32.0);
		glVertex2f(200.0,	32.0);
		glVertex2f(200.0,	0.0);
	glEnd();	
}

///This is called in the display, it prints the menu items.
void printMenu()
{
	static float lastTime = 0.0f, presentTime = 0.0f;
	int i,j;
	float fade = 0.0;
	float tp;

	presentTime = glutGet(GLUT_ELAPSED_TIME);

	tp = (presentTime - lastTime);

	//presentTime = glutGet(GLUT_ELAPSED_TIME);

	fade = 0.0006 * tp;

	if(tp > 1000)
	{
		fade = 0.01;
		//lastTime = presentTime;
	}

	lastTime = presentTime;

	(*menuFuncPoint)(); //Excute The Function
	//(*menuFuncArray[selectedMenu])();

	if(selectedMenu >= menuCount) { selectedMenu = 0; }
	else if (selectedMenu <= -1) { selectedMenu = menuCount-1; }


	for(i = 0; i < menuCount; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		if(selectedMenu == i)
		{
			for(j = 0; j < 3; j++)
			{
				if(colour[j] >= 1.0){ menuFade = 0; } 
				else if(colour[j] <= 0.0){ menuFade = 1; }

				if(menuFade){ colour[j]+=fade; }//Need to fix this so that it depends on time...
				else{ colour[j]-=fade; }
			}
			
			glColor3f(colour[0], colour[1], colour[2]); //Selected menu item Fade
			printTextXY(menuStringTxt[i],  menuStartXY[0], menuStartXY[1]-(i*30), (int)GLUT_BITMAP_HELVETICA_18);	//Printing it here, prints it on top of the box (DEPTH TESTING MUST ENABLED)

			//Draw / Fade Box arround the selected menu item
			glColor3f(1.0-colour[0], 1.0-colour[1], 1.0-colour[2]);
			glPushMatrix();
				glTranslated(menuStartXY[0]-10, menuStartXY[1]-10-(i*30), 0.0);
				rectangle();
			glPopMatrix();
		}
		else
		{
			printTextXY(menuStringTxt[i],  menuStartXY[0], menuStartXY[1]-(i*30), (int)GLUT_BITMAP_HELVETICA_18);	
		}
	}
}
