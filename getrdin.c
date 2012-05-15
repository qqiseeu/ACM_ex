/*Get input of INT type*/

#include <stdio.h>
#include "myioset.h"
#include <stdlib.h>

static void		myfscanf(FILE *fp, const char * typestr, int *aim, int num, char *filename);
static void		myfread(int *aim, size_t type, int num, FILE *fp, char *filename);

int* getipt(char *data, int mode, int *pN)      
{
	int			 scale;
	FILE		*datafile;
	int			*tmparray;

	if (NULL != data)
		{
			datafile = fopen(data, "r");
			switch (mode)
				{
				case BIN_MODE:
					if (NULL == datafile)
						{
							fprintf(stderr, "Can't open file %s.\n", data);
							exit(1);
						}
					myfread(&scale, sizeof(int), 1, datafile, data);
				
					tmparray = (int*)malloc(sizeof(int) *	scale);
					if (NULL == tmparray)
						{
							fprintf(stderr, "Can't allocate enough space.");
							exit(2);
						}
					myfread(tmparray, sizeof(int), scale, datafile, data);
					break;

				case CHAR_MODE:
					if (NULL == datafile)
						{
							fprintf(stderr, "Can't open file %s.", data);
							exit(1);
						}
					myfscanf(datafile, "%d", &scale, 1, data);
					
					tmparray = (int*)malloc(sizeof(int) *	scale);
					if (NULL == tmparray)
						{
							fprintf(stderr, "Can't allocate enough space.");
							exit(2);
						}
					myfscanf(datafile, "%d", tmparray, scale, data);
					break;

				default:
					fprintf(stderr, "Please choose the right mode.\n");
					exit(6);

					break;
			}
		}
	else
		{
			data = "~/AlgorithmEx/RandomInput";
			datafile = fopen(data, "r");
			if (NULL == datafile)
				{
					fprintf(stderr, "Can't open file %s.\n", data);
					exit(1);
				}
			myfread(&scale, sizeof(int), 1, datafile, data);
				
			tmparray = (int*)malloc(sizeof(int) *	scale);
			if (NULL == tmparray)
				{
					fprintf(stderr, "Can't allocate enough space.");
					exit(2);
				}
			myfread(tmparray, sizeof(int), scale, datafile, data);
		}

	*pN = scale;
	return tmparray;
}

static void		myfscanf(FILE *fp, const char * typestr, int *aim, int num, char *filename)
{
	int i;

	for (i=0; i<num; i++)
		fscanf(fp, typestr, aim+i);

	if (i < num)
		if (0 != feof(fp))
			{
				fprintf(stderr, "Haven't read enough data from %s.\n", filename);
				exit(3);
			}
		else if(0 != ferror(fp))
			{
				fprintf(stderr, "Error in reading data from %s.\n", filename);
				exit(4);
			}
		else
			{
				fprintf(stderr, "Unkown error occured.\n");
				exit(5);
			}
}

static void		myfread(int *aim, size_t type, int num, FILE *fp, char *filename)
{
	if (num != fread(aim, type, num, fp))
		if (0 != feof(fp))
			{
				fprintf(stderr, "Haven't read enough data from %s.\n", filename);
				exit(3);
			}
		else if(0 != ferror(fp))
			{
				fprintf(stderr, "Error in reading data from %s.\n", filename);
				exit(4);
			}
		else
			{
				fprintf(stderr, "Unkown error occured.\n");
				exit(5);
			}

}
