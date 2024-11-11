#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

void trim(char str[]);

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");

	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}

	int capacity = 100;
	int arrSize = 0;

	char ** arr = malloc(capacity * sizeof(char*));

	char line[1000];

	while (fgets(line, 1000, in) != NULL)
	{
		trim(line);

		if (arrSize == capacity)
		{
			capacity += 100;
			arr = realloc(arr, capacity * sizeof(char*));
		}

		int lineLength = strlen(line);

		arr[arrSize] = malloc(lineLength + 1);
		
		strcpy(arr[arrSize], line);
		
		arrSize++;
	}

	arrSize--;

	*size = arrSize;

	fclose(in);

	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		char* foundString = strstr(lines[i], target);

		if (foundString != NULL)
		{
			return lines[i];
		}
	}

	return NULL;
}

char * stringSearch(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(lines[i], target) == 0)
		{
			return lines[i];
		}
	}

	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for (int i = 0; i < size; i ++)
	{
		free(arr[i]);
	}

	free(arr);
}

void trim(char str[])
{
    char *newLine = strchr(str, '\n');
    if (newLine) *newLine = '\0';
}