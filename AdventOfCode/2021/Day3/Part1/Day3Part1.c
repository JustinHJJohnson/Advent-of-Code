#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
--- Day 3: Binary Diagnostic ---

The submarine has been making some odd creaking noises, so you ask it to produce a diagnostic report just in case.

The diagnostic report (your puzzle input) consists of a list of binary numbers which, when decoded properly, can tell you many useful things about the conditions of the submarine. The first parameter to check is the power consumption.

You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.

Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all numbers in the diagnostic report. For example, given the following diagnostic report:

00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010

Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is 1, the first bit of the gamma rate is 1.

The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.

The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits of the gamma rate are 110.

So, the gamma rate is the binary number 10110, or 22 in decimal.

The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)

Your puzzle answer was 2583164.
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

int main(int argc, char* argv[])
{	
	int inputLength;												//How long the input file is
	const char* filename = "..\\..\\inputs\\Day3.txt";				//Path to the input file
	char** input = readInput(filename, 15, &inputLength, false);	//Read in the input file and get it's length

    char gammaBinary[13];
    char epsilonBinary[13];
	int gamma = 0;
	int epsilon = 0;

    //Loop through every 
	for (int i = 0; i < 13; i++)
    {
        int num1s = 0;
        int num0s = 0;

        for (int j = 0; j < inputLength; j++)
        {
            if (input[j][i] == '1') num1s++;
            else num0s++;
        }

        if (num1s < num0s) gammaBinary[i] = '0';
        else gammaBinary[i] = '1';
    }

	gammaBinary[12] = '\0';
	for (int i = 0; i < 13; i++)
	{
		if (gammaBinary[i] == '0') epsilonBinary[i] = '1';
		else if (gammaBinary[i] == '1') epsilonBinary[i] = '0';
		else epsilonBinary[i] = '\0';
	}

	for (int i = 0; i < 12; i++)
	{
		if (gammaBinary[11 - i] == '1') gamma += pow(2, i);
		else epsilon += pow(2, i);
	}
		
	printf("\nGamma binary is %s\nEpsilon binary is %s\n", gammaBinary, epsilonBinary);
	printf("\nGamma is %d\nEpsilon is %d\n", gamma, epsilon);
	printf("Power usage is %d\n", gamma * epsilon);
    getchar();
}