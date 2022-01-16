import os

scriptDir = os.path.dirname(os.path.realpath(__file__))

year = 2021
day = input("Enter day: ")

if not os.path.isdir(f"{scriptDir}/AdventOfCode/{year}/Day{day}"):
    os.mkdir(f"{scriptDir}/AdventOfCode/{year}/Day{day}")
    os.mkdir(f"{scriptDir}/AdventOfCode/{year}/Day{day}/Part1")
    os.mkdir(f"{scriptDir}/AdventOfCode/{year}/Day{day}/Part2")
outputFile = open(f"{scriptDir}/AdventOfCode/{year}/Day{day}/Part1/Day{day}Part1.c", "w")
open(f"{scriptDir}/AdventOfCode/{year}/Day{day}/Part2/Day{day}Part2.c", "w")

outputFile.write(r'''#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*

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

int main(int argc, char* argv[])
{
	int inputLength;													// How long the input file is
	const char* filename = "..\\..\\inputs\\Day.txt"				// Path to the input file
	char** input = readInput(filename, 3930, &inputLength, false);		// Read in the input file and get it's length
	int* intInput = stringToInts(input[0], ',', &inputLength, false);	// The input converted to an array of ints

	getchar();
}''')

outputFile.close()