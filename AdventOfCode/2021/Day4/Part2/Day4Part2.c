#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Part Two ---

On the other hand, it might be wise to try a different strategy: let the giant squid win.

You aren't sure how many bingo boards a giant squid could play at once, so rather than waste time counting its arms, the safe thing to do is to figure out which board will win last and choose that one. That way, no matter which boards it picks, it will win for sure.

In the above example, the second board is the last to win, which happens after 13 is eventually called and its middle column is completely marked. If you were to keep playing until this point, the second board would have a sum of unmarked numbers equal to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score be?

Your puzzle answer was 8112.
*/

typedef struct
{
	int number;
	bool drawn;
} BingoSpace;

typedef struct
{
	BingoSpace spaces[5][5];
	int winningNumber;
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
		boards[currentBoard].winningNumber = -1;
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
void drawAndCheck(int number, BingoBoard* boards, int numBoards, BingoBoard* winner)
{
	for (int i = 0; i < numBoards; i++)
	{
		if (boards[i].winningNumber != -1) continue;
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
			boards[i].winningNumber = number;
			*winner = boards[i];
		}
	}
}

// Calculate the final score of the winning board
int calcScore(BingoBoard board)
{
	int score = 0;

	for (int i = 0; i < 5; i++)	
	{
		for (int j = 0; j < 5; j++)
		{
			if (!board.spaces[i][j].drawn) score += board.spaces[i][j].number;
		}
	}

	return score * board.winningNumber;
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

	for (int i = 0; i < numNumbers; i++) drawAndCheck(numbers[i], boards, numBoards, &winner);

	printf("The score is %d, winning number was %d\n", calcScore(winner), winner.winningNumber);
    getchar();
}