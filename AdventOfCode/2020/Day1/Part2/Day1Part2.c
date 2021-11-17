#include <stdio.h>
#include <stdlib.h>

/*
--- Part Two ---

The Elves in accounting are thankful for your help; one of them even offers you a starfish coin they had left over from a past vacation. They offer you a second one if you can find three numbers in your expense report that meet the same criteria.

Using the above example again, the three entries that sum to 2020 are 979, 366, and 675. Multiplying them together produces the answer, 241861950.

In your expense report, what is the product of the three entries that sum to 2020?

Your puzzle answer was 145245270.*/

int* readInput(const char* filename, int lineLength, int *numLines)
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
			for (int k = j + 1; k <= inputLength; k++)
			{
				if (input[i] + input[j] + input[k] == 2020)
				{
					printf("solution is %d\n", input[i] * input[j] * input[k]);
				}
			}
		}
	}
}