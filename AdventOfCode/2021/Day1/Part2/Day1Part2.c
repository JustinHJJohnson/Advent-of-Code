#include <stdio.h>
#include <stdlib.h>

/*
--- Part Two ---

Considering every single measurement isn't as useful as you expected: there's just too much noise in the data.

Instead, consider sums of a three-measurement sliding window. Again considering the above example:

199  A      
200  A B    
208  A B C  
210    B C D
200  E   C D
207  E F   D
240  E F G  
269    F G H
260      G H
263        H

Start by comparing the first and second three-measurement windows. The measurements in the first window are marked A (199, 200, 208); their sum is 199 + 200 + 208 = 607. The second window is marked B (200, 208, 210); its sum is 618. The sum of measurements in the second window is larger than the sum of the first, so this first comparison increased.

Your goal now is to count the number of times the sum of measurements in this sliding window increases from the previous sum. So, compare A with B, then compare B with C, then C with D, and so on. Stop when there aren't enough measurements left to create a new three-measurement sum.

In the above example, the sum of each three-measurement window is as follows:

A: 607 (N/A - no previous sum)
B: 618 (increased)
C: 618 (no change)
D: 617 (decreased)
E: 647 (increased)
F: 716 (increased)
G: 769 (increased)
H: 792 (increased)

In this example, there are 5 sums that are larger than the previous sum.

Consider sums of a three-measurement sliding window. How many sums are larger than the previous sum?

Your puzzle answer was 1567.
*/

int* readInput(const char *filename, int lineLength, int *numLines)
{
	// Open File
	FILE* fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}

	// Count Lines
	char cr;
	int lines = 0;

	while(cr != EOF) 
	{
		if (cr == '\n') lines++;
		cr = getc(fp);
	}
	rewind(fp);

	// Read data
	int* data = (int*)malloc(lines * sizeof(int));

	for (int i = 0; i < lines; i++) 
	{
		char buffer[6];
		fscanf(fp, "%d", &data[i]);

		if (ferror(fp))
		{
			perror("fopen");
			exit;
		}	
	}

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
	int answer = 0;
	int window1;
	int window2;

	for (int i = 1; i <= inputLength - 4; i++)
	{
		window1 = input[i] + input[i+1] + input[i+2];
		window2 = input[i+1] + input[i+2] + input[i+3];

		if (window1 < window2) answer++;
	}

	printf("%d sliding window measurements were larger than the previous one\n", answer);
}