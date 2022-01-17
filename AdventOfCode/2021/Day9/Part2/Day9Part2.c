#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
--- Part Two ---

Next, you need to find the largest basins so you know what areas are most important to avoid.

A basin is all locations that eventually flow downward to a single low point. Therefore, every low point has a basin, although some basins are very small. Locations of height 9 do not count as being in any basin, and all other locations will always be part of exactly one basin.

The size of a basin is the number of locations within the basin, including the low point. The example above has four basins.

The top-left basin, size 3:

2199943210
3987894921
9856789892
8767896789
9899965678

The top-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678

The middle basin, size 14:

2199943210
3987894921
9856789892
8767896789
9899965678

The bottom-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678

Find the three largest basins and multiply their sizes together. In the above example, this is 9 * 14 * 9 = 1134.

What do you get if you multiply together the sizes of the three largest basins?

Your puzzle answer was 1045660.
*/

void green() 
{
	printf("\033[0;32m");
}

void purple() 
{
	printf("\033[0;35m");
}

void red() 
{
	printf("\033[0;31m");
}

void reset() 
{
	printf("\033[0m");
}

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

typedef struct {
	int depth;
	bool visited;
} Tile;

// Convert a string of ints into tiles
Tile** stringToTiles(char** input, int inputLength, int lineLength, bool debug)
{
	// Adding an extra layer to the grid so we can skip edge checks
	Tile** tileInput = malloc(inputLength * sizeof(Tile*) + 2 * sizeof(Tile));

	for (int i = 0; i <= inputLength + 1; i++)
	{
		tileInput[i] = malloc(lineLength * sizeof(Tile) + 2 * sizeof(Tile));

		for (int j = 0; j <= lineLength + 1; j++) 
		{
			if (i == 0 || i == inputLength + 1 || j == 0 || j == lineLength + 1)
			{
				tileInput[i][j].depth = 9;
				tileInput[i][j].visited = false;
				if (debug) printf("%d", tileInput[i][j].depth);
				continue;
			}
			
			tileInput[i][j].depth = input[i - 1][j - 1] - '0';
			tileInput[i][j].visited = false;
			if (debug) printf("%d", input[i - 1][j - 1] - '0');
		}
		if (debug) printf("\n");
	}

	return tileInput;
}

// Find the size of a basin by recursing out from a tile til all instances hit a high point
int checkBasin(Tile** tileInput, int x, int y)
{
	if (tileInput[x][y].visited || tileInput[x][y].depth == 9) return 0;

	tileInput[x][y].visited = true;

	return 1 + checkBasin(tileInput, x, y + 1) + checkBasin(tileInput, x, y - 1) + checkBasin(tileInput, x + 1, y) + checkBasin(tileInput, x - 1, y);
}

// Check if a new basin is bigger than the current biggests and check if a replaced basin is still one of the biggest
void checkBiggestBasin(int currentBiggest[3], int numToCompare)
{
	for (int i = 0; i < 3; i++)
	{
		if (currentBiggest[i] < numToCompare) 
		{
			int temp = currentBiggest[i];
			currentBiggest[i] = numToCompare;
			checkBiggestBasin(currentBiggest, temp);
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	int inputLength;													// How long the input file is
	const char* filename = "..\\..\\inputs\\Day9.txt";					// Path to the input file
	char** input = readInput(filename, 105, &inputLength, false);		// Read in the input file and get it's length
	Tile** tileInput = stringToTiles(input, inputLength, 100, false);	// The input converted to a 2D array of Tiles
	int biggestBasins[3] = {0, 0, 0};									// The three largest basins found so far

	// Loop through all the tiles
	for (int i = 1; i < 101; i++)
	{
		for (int j = 1; j < 101; j++)
		{
			int height = tileInput[i][j].depth;

			//if (height < tileInput[i + 1][j].depth && height < tileInput[i - 1][j].depth && height < tileInput[i][j + 1].depth && height < tileInput[i][j - 1].depth)
			// If the current tile hasn't been visited, it is part of a new basin
			if (!tileInput[i][j].visited)
			{
				int basinSize = checkBasin(tileInput, i, j);
				checkBiggestBasin(biggestBasins, basinSize);
				/*if (basinSize > 90)
				{
					red();
					printf("Basin at %d %d is %d tiles big\n", i, j, basinSize);
					reset();
				}
				else printf("Basin at %d %d is %d tiles big\n", i, j, basinSize);*/
			}
		}
	}

	/*for (int i = 1; i < 101; i++)
	{
		for (int j = 1; j < 101; j++)
		{
			if (tileInput[i][j].visited)
			{
				green();
				printf("%d", tileInput[i][j].depth);
				reset();
			}
			else 
			{
				purple();
				printf("%d", tileInput[i][j].depth);
				reset();
			}
		}
		printf("\n");
	}*/

	int basinSum = biggestBasins[0] * biggestBasins[1] * biggestBasins[2];
	printf("Biggest basins were %d %d %d\n", biggestBasins[0], biggestBasins[1], biggestBasins[2]);
	printf("The sum of the three largest basins is %d\n", basinSum);

	getchar();
}