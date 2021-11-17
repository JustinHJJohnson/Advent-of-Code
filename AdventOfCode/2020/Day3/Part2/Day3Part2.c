#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Part Two ---

Time to check the rest of the slopes - you need to minimize the probability of a sudden arboreal stop, after all.

Determine the number of trees you would encounter if, for each of the following slopes, you start at the top-left corner and traverse the map all the way to the bottom:

	Right 1, down 1.
	Right 3, down 1. (This is the slope you already checked.)
	Right 5, down 1.
	Right 7, down 1.
	Right 1, down 2.

In the above example, these slopes would find 2, 7, 3, 4, and 2 tree(s) respectively; multiplied together, these produce the answer 336.

What do you get if you multiply together the number of trees encountered on each of the listed slopes?

Your puzzle answer was 1355323200.
*/

typedef struct Position {
	int x;
	int y;
} Position;

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
		fscanf(fp, "%s", data[i]);

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

int numTreesEncountered(char** input, int rightMove, int downMove, int width, int height)
{
	Position currentPos = { 0, 0 };		// current position in the grid
	int treeCount = 0;					// number of trees encountered

	// Keep looping until the botton of the grid
	while (currentPos.y + downMove < height)
	{
		// If the next move is greater than width, reduce it by width to simulate infinite repeating to the right
		if (currentPos.x + rightMove >= width) currentPos.x += rightMove - width;
		else currentPos.x += rightMove;

		currentPos.y += downMove;

		if (input[currentPos.y][currentPos.x] == '#') treeCount++;
	}

	printf("Encountered %d trees.\n", treeCount);
	return treeCount;
}

int main(int argc, char* argv[])
{
	int height;														// Height of the grid
	const char* filename = "..\\..\\inputs\\Day3.txt";	// Path to the input file
	char** input = readInput(filename, 35, &height, false);			// Store the input file and get the height of the grid
	const int width = strlen(input[0]);								// Width of the grid
	int treeCountTotal = 0;											// Total number of trees encountered over multiple runs

	int run1 = numTreesEncountered(input, 1, 1, width, height);
	int run2 = numTreesEncountered(input, 3, 1, width, height);
	int run3 = numTreesEncountered(input, 5, 1, width, height);
	int run4 = numTreesEncountered(input, 7, 1, width, height);
	int run5 = numTreesEncountered(input, 1, 2, width, height);

	treeCountTotal = run1 * run2 * run3 * run4 * run5;

	printf("Encountered %d trees in total.\n", treeCountTotal);
}