#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Part Two ---

Now, discard the corrupted lines. The remaining lines are incomplete.

Incomplete lines don't have any incorrect characters - instead, they're missing some closing characters at the end of the line. To repair the navigation subsystem, you just need to figure out the sequence of closing characters that complete all open chunks in the line.

You can only use closing characters (), ], }, or >), and you must add them in the correct order so that only legal pairs are formed and all chunks end up closed.

In the example above, there are five incomplete lines:

    [({(<(())[]>[[{[]{<()<>> - Complete by adding }}]])})].
    [(()[<>])]({[<{<<[]>>( - Complete by adding )}>]}).
    (((({<>}<{<{<>}{[]{[]{} - Complete by adding }}>}>)))).
    {<[[]]>}<{[{[{[]{()[[[] - Complete by adding ]]}}]}]}>.
    <{([{{}}[<[[[<>{}]]]>[]] - Complete by adding ])}>.

Did you know that autocomplete tools also have contests? It's true! The score is determined by considering the completion string character-by-character. Start with a total score of 0. Then, for each character, multiply the total score by 5 and then increase the total score by the point value given for the character in the following table:

    ): 1 point.
    ]: 2 points.
    }: 3 points.
    >: 4 points.

So, the last completion string above - ])}> - would be scored as follows:

    Start with a total score of 0.
    Multiply the total score by 5 to get 0, then add the value of ] (2) to get a new total score of 2.
    Multiply the total score by 5 to get 10, then add the value of ) (1) to get a new total score of 11.
    Multiply the total score by 5 to get 55, then add the value of } (3) to get a new total score of 58.
    Multiply the total score by 5 to get 290, then add the value of > (4) to get a new total score of 294.

The five lines' completion strings have total scores as follows:

    }}]])})] - 288957 total points.
    )}>]}) - 5566 total points.
    }}>}>)))) - 1480781 total points.
    ]]}}]}]}> - 995444 total points.
    ])}> - 294 total points.

Autocomplete tools are an odd bunch: the winner is found by sorting all of the scores and then taking the middle score. (There will always be an odd number of scores to consider.) In this example, the middle score is 288957 because there are the same number of scores smaller and larger than it.

Find the completion string for each incomplete line, score the completion strings, and sort the scores. What is the middle score?

Your puzzle answer was 820045242.
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

int main(int argc, char* argv[])
{
	int inputLength;													// How many lines are in the input file
	const char* filename = "..\\..\\inputs\\Day10.txt";					// Path to the input file
	char** input = readInput(filename, 3930, &inputLength, false);		// Read in the input file and get it's length
	char currentChunk;													// The current chunk closer we are looking for
	char unclosedChunks[100];											// Chunks that were opened before the current chunk
	int previousChunk;													// Index of the previous chunk in the array
	char currentChar;													// The current character being processed
	unsigned long long currentScore;                                    // The score for the curent line
    unsigned long long scores[100] = {[0 ... 99] = 0};                  // Scores from all the incomplete rows
	int scoreIndex = 0;													// The index of the next free space in the score array
    unsigned long long middleScore = 0;                                 // The score from the middle of the sorted scores
	bool corruptedLine = false;											// Whether the current line is corrupted or not					
	
	// Loop over every line
	for (int i = 0; i < inputLength; i++)
	{
		// Setup first chunk
		currentChunk = input[i][0];
		
		// Reset values from previous iteration
		currentScore = 0;
		previousChunk = -1;

		// Loop along a line until we hit the end
		for (int j = 1; input[i][j] != '\n'; j++)
		{
			currentChar = input[i][j];
			// Deal with a new chunk
			if (input[i][j] == '(' || input[i][j] == '[' || input[i][j] == '{' || input[i][j] == '<')
			{
				previousChunk++;
				unclosedChunks[previousChunk] = currentChunk;
				currentChunk = input[i][j];
			}
			else
			{
				// If the current character doesn't match up with the current open chunk, ignore line as it is corrupted
				if (input[i][j] - 1 != currentChunk && input[i][j] - 2 != currentChunk) 
				{
					corruptedLine = true;
					break;
				}
				
				// Start dealing with the previous chunk
				currentChunk = unclosedChunks[previousChunk];
				previousChunk--;
			
			}
		}

		if (corruptedLine)
		{
			corruptedLine = false;
			continue;
		}

		// Get the score of the current chunk
		switch (currentChunk)
		{
            case '(':
                currentScore = currentScore * 5 + 1;
                break;
            
            case '[':
                currentScore = currentScore * 5 + 2;
                break;
            
            case '{':
                currentScore = currentScore * 5 + 3;
                break;
            
            case '<':
                currentScore = currentScore * 5 + 4;
                break;
		}

		// Get the scores for all the other unclosed chunks on this line
        for (int j = previousChunk; j >= 0; j--)
        {
            switch (unclosedChunks[j])
            {
                case '(':
                	currentScore = currentScore * 5 + 1;
                	break;
            
            	case '[':
            	    currentScore = currentScore * 5 + 2;
            	    break;
	
            	case '{':
            	    currentScore = currentScore * 5 + 3;
            	    break;
	
            	case '<':
            	    currentScore = currentScore * 5 + 4;
            	    break;
            }  
        }

        scores[scoreIndex++] = currentScore;
	}

	// Sort the scores in decending order
	for (int i = 0; i < scoreIndex; i++)
	{
		for (int j = i + 1; j < scoreIndex; j++)
		{
			if (scores[i] < scores[j])
			{
				unsigned long long temp = scores[i];
				scores[i] = scores[j];
				scores[j] = temp;
			}
		}
	}

	middleScore = scores[((scoreIndex + 1) / 2) - 1];
	printf("Middle score is %llu\n", middleScore);

	getchar();
}