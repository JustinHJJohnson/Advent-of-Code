#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Day 5: Hydrothermal Venture ---

You come across a field of hydrothermal vents on the ocean floor! These vents constantly produce large, opaque clouds, so it would be best to avoid them if possible.

They tend to form in lines; the submarine helpfully produces a list of nearby lines of vents (your puzzle input) for you to review. For example:

0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2

Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 where x1,y1 are the coordinates of one end the line segment and x2,y2 are the coordinates of the other end. These line segments include the points at both ends. In other words:

    An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
    An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.

For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.

So, the horizontal and vertical lines from the above list would produce the following diagram:

.......1..
..1....1..
..1....1..
.......1..
.112111211
..........
..........
..........
..........
222111....

In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. Each position is shown as the number of lines which cover that point or . if no line covers that point. The top-left pair of 1s, for example, comes from 2,2 -> 2,1; the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.

To avoid the most dangerous areas, you need to determine the number of points where at least two lines overlap. In the above example, this is anywhere in the diagram with a 2 or larger - a total of 5 points.

Consider only horizontal and vertical lines. At how many points do at least two lines overlap?

Your puzzle answer was 5608.
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

Point* formatAndFilterInput(char** input, int* inputLength)
{
	int newInputLength = 0;
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
		
		if (coords[0] != coords[2] && coords[1] != coords[3]) continue;

		filteredInput[newInputLength].x1 = coords[0]; 
		filteredInput[newInputLength].y1 = coords[1]; 
		filteredInput[newInputLength].x2 = coords[2]; 
		filteredInput[newInputLength].y2 = coords[3]; 
		newInputLength++;
	}

	*inputLength = newInputLength;
	return filteredInput;
}

void plotLines(Point* input, int inputLength, int** grid)
{
	for (int i = 0; i < inputLength; i++)
	{
		if (input[i].x1 == input[i].x2)
		{
			if (input[i].y1 < input[i].y2)
			{
				for (int j = input[i].y1; j <= input[i].y2; j++) grid[input[i].x1][j]++;
			}
			else
			{
				for (int j = input[i].y2; j <= input[i].y1; j++) grid[input[i].x1][j]++;
			}
		}
		else
		{
			if (input[i].x1 < input[i].x2)
			{
				for (int j = input[i].x1; j <= input[i].x2; j++) grid[j][input[i].y1]++;
			}
			else
			{
				for (int j = input[i].x2; j <= input[i].x1; j++) grid[j][input[i].y1]++;
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
	Point* filteredInput = formatAndFilterInput(input, &inputLength);	// Input converted to ints and with diagonal moves removed
	// Allocating memory for the grid of the ocean floor
	int** oceanFloor = malloc(1000 * sizeof(int*));
	for (int i = 0; i < 1000; i++) oceanFloor[i] = calloc(1000, sizeof(int));

	//for (int i = 0; i < inputLength; i++) printf("%d,%d -> %d,%d\n", filteredInput[i].x1, filteredInput[i].y1, filteredInput[i].x2, filteredInput[i].y2);

	plotLines(filteredInput, inputLength, oceanFloor);
	printf("There are %d spots where 2 or more lines overlap\n", checkGrid(oceanFloor));

	getchar();
}