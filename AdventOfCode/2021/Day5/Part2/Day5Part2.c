#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Part Two ---

Unfortunately, considering only horizontal and vertical lines doesn't give you the full picture; you need to also consider diagonal lines.

Because of the limits of the hydrothermal vent mapping system, the lines in your list will only ever be horizontal, vertical, or a diagonal line at exactly 45 degrees. In other words:

    An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
    An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.

Considering all lines from the above example would now produce the following diagram:

1.1....11.
.111...2..
..2.1.111.
...1.2.2..
.112313211
...1.2....
..1...1...
.1.....1..
1.......1.
222111....

You still need to determine the number of points where at least two lines overlap. In the above example, this is still anywhere in the diagram with a 2 or larger - now a total of 12 points.

Consider all of the lines. At how many points do at least two lines overlap?

Your puzzle answer was 20299.
*/

char** readInput(const char* filename, int lineLength, int* numLines, bool debug)
{
	// Open File
	FILE* fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}
	if (debug) printf("Opened file: %s\n", filename); 

	// Count Lines
	char cr;
	int lines = 0;

	while(cr != EOF) 
	{
		if (cr == '\n') lines++;
		cr = getc(fp);
	}
	if (debug) printf("Number of lines: %ld\n", lines); 
	rewind(fp);

	// Read data
	char** data = (char**)malloc(lines * sizeof(char*));
	int n;

	for (int i = 0; i < lines; i++) 
	{
		data[i] = (char*)malloc(lineLength * sizeof(char));
		fgets(data[i], lineLength, fp);

		if (ferror(fp))
		{
			perror("fopen");
			exit;
		}	
	}

	if (debug)
	{
		for (int i = 0; i < lines; i++) printf("%s\n", data[i]);
	}
	
	// Close File
	fclose(fp);

	*numLines = lines;
	return data;
}

// Convert a string of integers with a delimiting character to an array of ints
int* stringToInts(char* input, char token, int* numInts, bool debug)
{
	char* current = &input[0];
	char* start;
	int numIntsLocal = 0;

	// Get the number of ints in the string
	while (*current != '\n')
	{
		if (*current == token)
		{
			// Count multiple tokens in a row as one token
			while (*(current + 1) == token) current++;
			numIntsLocal++;
		}
		current++;
	}
	numIntsLocal++;

	if (debug) printf("Number of numbers is %d\n", numIntsLocal);
	
	int* ints = malloc(numIntsLocal * sizeof(int));
	current = &input[0] - 1;

	for (int i = 0; *current != '\n'; i++)
	{
		start = current + 1;
		while (*current != token && *current != '\n') current++;
		ints[i] = strtol(start, &current, 10);
		if (debug) printf("%d\n", ints[i]);
	}

	if (numInts != NULL) *numInts = numIntsLocal;
	return ints;
}

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} Point;

Point* formatInput(char** input, int* inputLength)
{
	Point* filteredInput = malloc(*inputLength * sizeof(*filteredInput));
	
	for (int i = 0; i < *inputLength; i++)
	{
		char c = input[i][0];
		int endCoord1 = 0;
		int startCoord2;
		int endCoord2;

		while (c != ' ') 
		{
			c = input[i][endCoord1];
			endCoord1++;
		}

		endCoord1 -= 2;
		
		startCoord2 = endCoord1 + 2;
		c = input[i][startCoord2];

		while (c != ' ') 
		{
			c = input[i][startCoord2];
			startCoord2++;
		}
		startCoord2;

		endCoord2 = startCoord2 + 1;

		while (c != '\n') 
		{
			c = input[i][endCoord2];
			endCoord2++;
		}

		endCoord2 -= 2;
		int length = (endCoord1 + (endCoord2 - startCoord2) + 4);
		char* formatted = malloc(length * sizeof(char));
		int currentIndex = 0;

		for (int j = 0; j <= endCoord1; j++) 
		{
			formatted[j] = input[i][j];
			currentIndex++;
		}
		formatted[currentIndex] = ',';
		currentIndex++;
		int endFormat1 = currentIndex;
		for (int j = currentIndex; j <= endFormat1 + (endCoord2 - startCoord2); j++)
		{
			formatted[j] = input[i][j + 3];
			currentIndex++;
		}
		formatted[currentIndex] = '\n';
		formatted[currentIndex + 1] = '\0';

		int* coords = stringToInts(formatted, ',', NULL, false);

		filteredInput[i].x1 = coords[0]; 
		filteredInput[i].y1 = coords[1]; 
		filteredInput[i].x2 = coords[2]; 
		filteredInput[i].y2 = coords[3];
	}

	return filteredInput;
}

// Plot the lines on the grid
void plotLines(Point* input, int inputLength, int** grid)
{
	for (int i = 0; i < inputLength; i++)
	{
		// Vertical
		if (input[i].x1 == input[i].x2)
		{
			// Down
			if (input[i].y1 < input[i].y2)
			{
				for (int j = input[i].y1; j <= input[i].y2; j++) grid[input[i].x1][j]++;
			}
			// Up
			else
			{
				for (int j = input[i].y2; j <= input[i].y1; j++) grid[input[i].x1][j]++;
			}
		}
		// Horizontal
		else if (input[i].y1 == input[i].y2)
		{
			// Right
			if (input[i].x1 < input[i].x2)
			{
				for (int j = input[i].x1; j <= input[i].x2; j++) grid[j][input[i].y1]++;
			}
			// Left
			else
			{
				for (int j = input[i].x2; j <= input[i].x1; j++) grid[j][input[i].y1]++;
			}
		}
		// Diagonal
		else
		{
			// Down and right
			if (input[i].y1 < input[i].y2 && input[i].x1 < input[i].x2)
			{
				for (int j = 0; j <= input[i].y2 - input[i].y1; j++) grid[input[i].x1 + j][input[i].y1 + j]++;
			}
			// Up and left
			else if (input[i].y1 > input[i].y2 && input[i].x1 > input[i].x2)
			{
				for (int j = 0; j >= input[i].y2 - input[i].y1; j--) grid[input[i].x1 + j][input[i].y1 + j]++;
			}
			// Down and left
			else if (input[i].y1 < input[i].y2 && input[i].x1 > input[i].x2)
			{
				for (int j = 0; j <= input[i].y2 - input[i].y1; j++) grid[input[i].x1 - j][input[i].y1 + j]++;
			}
			// Up and right
			else if (input[i].y1 > input[i].y2 && input[i].x1 < input[i].x2)
			{
				for (int j = 0; j <= input[i].x2 - input[i].x1; j++) grid[input[i].x1 + j][input[i].y1 - j]++;
			}
		}

	}
}

int checkGrid(int** grid)
{
	int numOverThreshold = 0;
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			if (grid[i][j] >= 2) numOverThreshold++;
		}
	}
	
	return numOverThreshold;
}

int main(int argc, char* argv[])
{	
	int inputLength;													// How long the input file is
	const char* filename = "..\\..\\inputs\\Day5.txt";					// Path to the input file
	char** input = readInput(filename, 25, &inputLength, false);		// Read in the input file and get it's length
	Point* filteredInput = formatInput(input, &inputLength);			// Input converted to ints and with diagonal moves removed
	// Allocating memory for the grid of the ocean floor
	int** oceanFloor = malloc(1000 * sizeof(int*));
	for (int i = 0; i < 1000; i++) oceanFloor[i] = calloc(1000, sizeof(int));

	plotLines(filteredInput, inputLength, oceanFloor);
	printf("There are %d spots where 2 or more lines overlap\n", checkGrid(oceanFloor));

	getchar();
}