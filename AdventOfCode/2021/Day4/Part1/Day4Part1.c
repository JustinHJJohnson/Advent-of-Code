#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Day 4: Giant Squid ---

You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For example:

7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7

After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as follows (shown here adjacent to each other to save space):

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

Finally, 24 is drawn:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

At this point, the third board wins because it has at least one complete row or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board; in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to get the final score, 188 * 24 = 4512.

To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?

Your puzzle answer was 33348.
*/

typedef struct
{
	int number;
	bool drawn;
} BingoSpace;

typedef struct
{
	BingoSpace spaces[5][5];
} BingoBoard;

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

// Load all the data for each board in the input into a board struct
BingoBoard* initBoards(char** input, int inputLength, int* numBoards)
{
	*numBoards = (inputLength - 2) / 6;

	BingoBoard* boards = malloc(*numBoards * sizeof(*boards));
	
	int currentBoard = 0;
	
	for (int i = 2; i < inputLength; i += 6)
	{
		for (int j = 0; j < 5; j++)	
		{
			int* numbers = stringToInts(input[i + j], ' ', NULL, false);
			
			for (int k = 0; k < 5; k++)
			{
				boards[currentBoard].spaces[j][k].number = numbers[k];
				boards[currentBoard].spaces[j][k].drawn = false;
			}
			
		}
		currentBoard++;
	}

	return boards;
}

// Check if the passed in board has won
bool checkIfWinner(BingoBoard board)
{
	bool winner = true;
	for (int i = 0; i < 5; i++)	
	{
		winner = true;
		for (int j = 0; j < 5; j++)
		{
			if (!board.spaces[i][j].drawn) winner = false;
		}
		if (winner) return true;
	}

	winner = true;

	for (int i = 0; i < 5; i++)	
	{
		winner = true;
		for (int j = 0; j < 5; j++)
		{
			if (!board.spaces[j][i].drawn) winner = false;
		}
		if (winner) return true;
	}

	return false;
}

// Mark off the input number from every board then call the checkIfWinner function on each
bool drawAndCheck(int number, BingoBoard* boards, int numBoards, BingoBoard* winner)
{
	for (int i = 0; i < numBoards; i++)
	{
		for (int j = 0; j < 5; j++)	
		{
			for (int k = 0; k < 5; k++)
			{
				if (boards[i].spaces[j][k].number == number) 
				{
					boards[i].spaces[j][k].drawn = true;
					goto numFound;
				}
			}
		}
		numFound:
		if (checkIfWinner(boards[i]))
		{
			*winner = boards[i];
			return true;
		}
	}

	return false;
}

// Calculate the final score of the winning board
int calcScore(BingoBoard board, int lastNumber)
{
	int score = 0;

	for (int i = 0; i < 5; i++)	
	{
		for (int j = 0; j < 5; j++)
		{
			if (!board.spaces[i][j].drawn) score += board.spaces[i][j].number;
		}
	}

	return score * lastNumber;
}

int main(int argc, char* argv[])
{	
	int inputLength;													// How long the input file is
	const char* filename = "..\\..\\inputs\\Day4.txt";					// Path to the input file
	char** input = readInput(filename, 300, &inputLength, false);		// Read in the input file and get it's length
	int numNumbers;														// The amount of bingo numbers to call
	int* numbers = stringToInts(input[0], ',', &numNumbers, false);		// The bingo numbers to be called
	int numBoards;														// Number of boards in the input
	BingoBoard* boards = initBoards(input, inputLength, &numBoards);	// Load the data into all the spaces
	BingoBoard winner;

	for (int i = 0; i < numNumbers; i++)
	{
		if (drawAndCheck(numbers[i], boards, numBoards, &winner))
		{
			printf("The score is %d\n", calcScore(winner, numbers[i]));
			break;
		}
	}
    
    getchar();
}