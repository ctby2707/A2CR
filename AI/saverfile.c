#include <stdio.h>
#include <stdlib.h>
#include "saverfile.h"

void savefile (char* path, double* list, int size)
{
	FILE* file = NULL;
	file = fopen(path, "w");
	for (int i = 0; i < size; i++)
	{
		fprintf(file, "%lf\n", *(list+i));
	}
	fclose(file);
}
