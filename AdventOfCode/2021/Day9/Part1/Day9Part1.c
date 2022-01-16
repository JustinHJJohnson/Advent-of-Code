#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
--- Day 9: Smoke Basin ---

These caves seem to be lava tubes. Parts are even still volcanically active; small hydrothermal vents release smoke into the caves that slowly settles like rain.

If you can model how the smoke flows through the caves, you might be able to avoid it and be that much safer. The submarine generates a heightmap of the floor of the nearby caves for you (your puzzle input).

Smoke flows to the lowest point of the area it's in. For example, consider the following heightmap:

2199943210
3987894921
9856789892
8767896789
9899965678

Each number corresponds to the height of a particular location, where 9 is the highest and 0 is the lowest a location can be.

Your first goal is to find the low points - the locations that are lower than any of its adjacent locations. Most locations have four adjacent locations (up, down, left, and right); locations on the edge or corner of the map have three or two adjacent locations, respectively. (Diagonal locations do not count as adjacent.)

In the above example, there are four low points, all highlighted: two are in the first row (a 1 and a 0), one is in the third row (a 5), and one is in the bottom row (also a 5). All other locations on the heightmap have some lower adjacent location, and so are not low points.

The risk level of a low point is 1 plus its height. In the above example, the risk levels of the low points are 2, 1, 6, and 6. The sum of the risk levels of all low points in the heightmap is therefore 15.

Find all of the low points on your heightmap. What is the sum of the risk levels of all low points on your heightmap?

Your puzzle answer was 480.
*/

char** readInput(const char* filename, int lineLength, int* numLines, bool debug)
{
	// Open File
	FILE* fp = fopen(filename, "r");

	if (!fp)
	{
		perror("getline");
		exit;
	}
	if (debug) printf("Opened file: %s\n", filename);

	// Count Lines
	char cr = 'a';
	int lines = 0;

	while (cr != EOF)
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

	int* ints = (int*)malloc(numIntsLocal * sizeof(int));
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

int** stringToIntsNoDelim(char** input, int inputLength, int lineLength, bool debug)
{
	int** intInput = malloc(inputLength * sizeof(int*));

	for (int i = 0; i < inputLength; i++)
	{
		intInput[i] = malloc(lineLength * sizeof(int));

		for (int j = 0; j < lineLength; j++) 
		{
			intInput[i][j] = input[i][j] - '0';
			if (debug) printf("%d", input[i][j] - '0');
		}
		if (debug) printf("\n");
	}

	return intInput;
}

typedef struct Node Node;

struct Node {
	int height;
	int x;
	int y;
	Node* up;
	Node* down;
	Node* left;
	Node* right;
};

Node* makeNode(int value, int x, int y)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->height = value;
	node->x = x;
	node->y = y;
	node->up = NULL;
	node->down = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int main(int argc, char* argv[])
{
	int inputLength;															// How long the input file is
	const char* filename = "..\\..\\inputs\\Day9.txt";							// Path to the input file
	char** input = readInput(filename, 105, &inputLength, false);				// Read in the input file and get it's length
	int** intInput = stringToIntsNoDelim(input, inputLength, 100, false);		// The input converted to a 2D array of ints
	int riskLevelSum = 0;

	// Check the middle
	for (int i = 1; i < 99; i++)
	{
		for (int j = 1; j < 99; j++)
		{
			int height = intInput[i][j];

			//printf("%d", height);

			if (height < intInput[i + 1][j] && height < intInput[i - 1][j] && height < intInput[i][j + 1] && height < intInput[i][j - 1])
			{
				//printf("Low point of %d at %d %d\n", height, i, j);
				riskLevelSum += 1 + height;
			}
		}
		printf("\n");
	}

	// Check left most and right most columns
	for (int i = 0; i < inputLength; i++)
	{
		int height1 = intInput[i][0];
		int height2 = intInput[i][99];

		if (i == 0)
		{
			if (height1 < intInput[1][0] && height1 < intInput[0][1])
			{
				printf("Col Low point of %d at 0 0\n", height1);
				riskLevelSum += 1 + height1;
			}
			if (height2 < intInput[1][99] && height2 < intInput[0][98])
			{
				printf("Col Low point of %d at 0 99\n", height2);
				riskLevelSum += 1 + height2;
			}
		}
		else if (i == 99)
		{
			if (height1 < intInput[99][1] && height1 < intInput[98][0])
			{
				printf("Col Low point of %d at 99 0\n", height1, inputLength - 1);
				riskLevelSum += 1 + height1;
			}
			if (height2 < intInput[99][98] && height2 < intInput[98][99])
			{
				printf("Col Low point of %d at 99 99\n", height2, inputLength - 1);
				riskLevelSum += 1 + height2;
			}
		}
		else
		{
			if (height1 < intInput[i + 1][0] && height1 < intInput[i - 1][0] && height1 < intInput[i][1])
			{
				printf("Col Low point of %d at %d 0\n", height1, i);
				riskLevelSum += 1 + height1;
			}
			if (height2 < intInput[i + 1][99] && height2 < intInput[i - 1][99] && height2 < intInput[i][98])
			{
				printf("Col Low point of %d at %d 99\n", height2, i);
				riskLevelSum += 1 + height2;
			}
		}
	}

	// Check the top and bottom row
	for (int i = 1; i < inputLength - 1; i++)
	{
		int height1 = intInput[0][i];
		int height2 = intInput[inputLength - 1][i];

		if (height1 < intInput[0][i - 1] && height1 < intInput[0][i + 1] && height1 < intInput[1][i])
		{
			printf("Row Low point of %d at 0 %d\n", height1, i);
			riskLevelSum += 1 + height1;

		}
		if (height2 < intInput[inputLength - 1][i - 1] && height2 < intInput[inputLength - 1][i + 1] && height2 < intInput[inputLength - 2][i])
		{
			printf("Row Low point of %d at %d %d\n", inputLength - 1, height2, i);
			riskLevelSum += 1 + height2;
		}
	}

	printf("The sum of the risk levels of all the low points is %d\n", riskLevelSum);

	getchar();
}

//500 too high