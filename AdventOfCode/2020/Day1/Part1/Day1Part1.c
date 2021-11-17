#include <stdio.h>
#include <stdlib.h>

/*
--- Day 1: Report Repair ---

After saving Christmas five years in a row, you've decided to take a vacation at a nice resort on a tropical island. Surely, Christmas will go on without you.

The tropical island has its own currency and is entirely cash-only. The gold coins used there have a little picture of a starfish; the locals just call them stars. None of the currency exchanges seem to have heard of them, but somehow, you'll need to find fifty of these coins by the time you arrive so you can pay the deposit on your room.

To save your vacation, you need to get all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

Before you leave, the Elves in accounting just need you to fix your expense report (your puzzle input); apparently, something isn't quite adding up.

Specifically, they need you to find the two entries that sum to 2020 and then multiply those two numbers together.

For example, suppose your expense report contained the following:

1721
979
366
299
675
1456

In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying them together produces 1721 * 299 = 514579, so the correct answer is 514579.

Of course, your expense report is much larger. Find the two entries that sum to 2020; what do you get if you multiply them together?

Your puzzle answer was 712075.*/

int* readInput(const char *filename, int lineLength, int *numLines)
{
	// Open File
	FILE* fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}
	//printf("Opened file: %s\n", filename); 

	// Count Lines
	char cr;
	int lines = 0;

	while(cr != EOF) 
	{
		if (cr == '\n') lines++;
		cr = getc(fp);
	}
	//printf("Number of lines: %ld\n", lines); 
	rewind(fp);

	// Read data
	int* data = (int*)malloc(lines * sizeof(int));

	for (int i = 0; i < lines; i++) 
	{
		char buffer[6];
		//data[i] = (int)malloc(lineLength * sizeof(int));
		fscanf(fp, "%d", &data[i]);
		//data[i] = atoi(buffer);

		if (ferror(fp))
		{
			perror("fopen");
			exit;
		}	
	}

	/*for (int i = 0; i < lines; i++)
	{
		printf("%d\n", data[i]);
	}*/

	// Close File
	fclose(fp);

	*numLines = lines;
	return data;
}

int main(int argc, char* argv[])
{	
	int inputLength;
	const char* filename = "..\\..\\inputs\\Day1.txt";
	
	int* input = readInput(filename, 5, &inputLength);

	for (int i = 0; i <= inputLength; i++)
	{
		for (int j = i + 1; j <= inputLength; j++)
		{
			if (input[i] + input[j] == 2020)
			{
				printf("solution is %d\n", input[i] * input[j]);
			}
		}
	}

	getchar();
}