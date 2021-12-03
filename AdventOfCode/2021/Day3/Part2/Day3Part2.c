#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
--- Part Two ---

Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

    Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
    If you only have one number left, stop; this is the rating value for which you are searching.
    Otherwise, repeat the process, considering the next bit to the right.

The bit criteria depends on which type of rating value you want to find:

    To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
    To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.

For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

    Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
    Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
    In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
    In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
    In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
    As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.

Then, to determine the CO2 scrubber rating value from the same example above:

    Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
    Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
    In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
    As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.

Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)

Your puzzle answer was 2784375.
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

bool filterInput(char** input, int** filteredInput, int* filteredLength, int column, bool mostCommon)
{
	if (*filteredLength == 1) return true;

	char digit;						// The most/least common digit
	int* temp = *filteredInput;		// A derefernced version of the filtered input
	int num1s = 0;					// The number of 1s in this column
    int num0s = 0;					// The number of 0s in this column

    // Find the most common value in the input column
	for (int i = 0; i < *filteredLength; i++)
    {
        if (input[temp[i]][column] == '1') num1s++;
        else num0s++;
    }

	// Filter the list based on the most common value in this column
	if (num1s < num0s)
	{
		if (mostCommon) digit = '0';
		else digit = '1';
	}
    else 
	{
		if (mostCommon) digit = '1';
		else digit = '0';
	}

	int newLength = 0;	// The new length of the filtered list after filtering
		
	for (int i = 0; i < *filteredLength; i++)
	{
		if (input[temp[i]][column] == digit)
		{
			temp[newLength] = temp[i];
			newLength++;
		}
	}

	*filteredLength = newLength;
	return false;
}

int main(int argc, char* argv[])
{	
	int inputLength;												//	How long the input file is
	const char* filename = "..\\..\\inputs\\Day3.txt";				//	Path to the input file
	char** input = readInput(filename, 15, &inputLength, false);	//	Read in the input file and get it's length
	int* oxyList = NULL;											//	An array of inputs that match the current filter for oxygen generator rating
	int* c02List = NULL;											//	An array of inputs that match the current filter for CO2 scrubber rating
	int oxyLength = inputLength;									//	Length of the oxyList array
	int c02Length = inputLength;									//	Length of the oxyList array
	bool oxyFound = false;											//	Whether or not the oxygen generator rating has been found
	bool c02Found = false;											//	Whether or not the CO2 scrubber rating has been found

	// Setup the filtered lists
	oxyList = (int*)malloc(inputLength * sizeof(int));
	c02List = (int*)malloc(inputLength * sizeof(int));
	for (int i = 0; i < inputLength; i++)
	{
		oxyList[i] = i;
		c02List[i] = i;
	}

    // Loop through each column in the diagnostics report
	for (int i = 0; i < 13; i++)
    {
        // Filter the list based on the most/least common value in this column of the filtered lists
		oxyFound = filterInput(input, &oxyList, &oxyLength, i, true);
        c02Found = filterInput(input, &c02List, &c02Length, i, false);

		if (oxyFound && c02Found) break;
    }

	// The two ratings in binary
	char* oxyGeneRatingBin = input[oxyList[0]];
	char* c02ScrubRatingBin = input[c02List[0]];

	free(oxyList);
	free(c02List);

	// The two ratings in decimal
	int oxyGeneRating = 0;
	int c02ScrubRating = 0;

	// Convert the binary to decimal
	for (int i = 0; i < 12; i++)
	{
		if (oxyGeneRatingBin[11 - i] == '1') oxyGeneRating += pow(2, i);
		if (c02ScrubRatingBin[11 - i] == '1') c02ScrubRating += pow(2, i);
	}

	printf("\nOxygen generator rating binary is %s\nCO2 scrubber rating binary is %s\n", oxyGeneRatingBin, c02ScrubRatingBin);
	printf("Oxygen generator rating is %d\nCO2 scrubber rating is %d\n", oxyGeneRating, c02ScrubRating);
	printf("The life support rating is %d\n", oxyGeneRating * c02ScrubRating);
    getchar();
}