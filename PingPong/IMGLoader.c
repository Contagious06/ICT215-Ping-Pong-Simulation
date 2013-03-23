#include "IMGLoader.h"



///Loads a raw image (note doesn't switch it around...) and returns a pointer to it.
pixel* loadIMG(char fileName[], const int xMax, const int yMax)
{
	FILE *readIMG;
	pixel *tmpIMG;
	pixel *tmpBuff;
	int i;
	int offset;
	int x, y;
	int charin;
	tmpBuff = malloc( 3*xMax*yMax*sizeof(pixel) );


	if ((readIMG = fopen(fileName, "rb")) == NULL) /* open failed */
	{
		printf("ERROR: cannot open: %s", fileName);
		getchar();
		exit(1); /* terminate execution */
	}

	offset = 0;
	for( i = 0; i < 3; i++)
	{
		for ( y = 0; y < yMax; y++ )
		{
			for ( x = 0; x < xMax; x++)
			{
				//printf("r%d %d\n",r, c);
				if((charin=fgetc(readIMG))==EOF) /* if read failed */
				{
					printf("Error Reading file! \n");
					charin = getchar();
					exit(1); /* terminate execution */
				}
				//imageRGB[i][r][c] = charin;
				tmpBuff[xMax*offset + x] = charin;

			}
			offset++;
		}
	}

	return(tmpBuff);
}