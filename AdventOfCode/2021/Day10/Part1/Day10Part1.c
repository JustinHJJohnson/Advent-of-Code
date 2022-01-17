#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Day 10: Syntax Scoring ---

You ask the submarine to determine the best route out of the deep-sea cave, but it only replies:

Syntax error in navigation subsystem on line: all of them

All of them?! The damage is worse than you thought. You bring up a copy of the navigation subsystem (your puzzle input).

The navigation subsystem syntax is made of several lines containing chunks. There are one or more chunks on each line, and chunks contain zero or more other chunks. Adjacent chunks are not separated by any delimiter; if one chunk stops, the next chunk (if any) can immediately start. Every chunk must open and close with one of four legal pairs of matching characters:

    If a chunk opens with (, it must close with ).
    If a chunk opens with [, it must close with ].
    If a chunk opens with {, it must close with }.
    If a chunk opens with <, it must close with >.

So, () is a legal chunk that contains no other chunks, as is []. More complex but valid chunks include ([]), {()()()}, <([{}])>, [<>({}){}[([])<>]], and even (((((((((()))))))))).

Some lines are incomplete, but others are corrupted. Find and discard the corrupted lines first.

A corrupted line is one where a chunk closes with the wrong character - that is, where the characters it opens and closes with do not form one of the four legal pairs listed above.

Examples of corrupted chunks include (], {()()()>, (((()))}, and <([]){()}[{}]). Such a chunk can appear anywhere within a line, and its presence causes the whole line to be considered corrupted.

For example, consider the following navigation subsystem:

[({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]

Some of the lines aren't corrupted, just incomplete; you can ignore these lines for now. The remaining five lines are corrupted:

    {([(<{}[<>[]}>{[]{[(<()> - Expected ], but found } instead.
    [[<[([]))<([[{}[[()]]] - Expected ], but found ) instead.
    [{[{({}]{}}([{[{{{}}([] - Expected ), but found ] instead.
    [<(<(<(<{}))><([]([]() - Expected >, but found ) instead.
    <{([([[(<>()){}]>(<<{{ - Expected ], but found > instead.

Stop at the first incorrect closing character on each corrupted line.

Did you know that syntax checkers actually have contests to see who can get the high score for syntax errors in a file? It's true! To calculate the syntax error score for a line, take the first illegal character on the line and look it up in the following table:

    ): 3 points.
    ]: 57 points.
    }: 1197 points.
    >: 25137 points.

In the above example, an illegal ) was found twice (2*3 = 6 points), an illegal ] was found once (57 points), an illegal } was found once (1197 points), and an illegal > was found once (25137 points). So, the total syntax error score for this file is 6+57+1197+25137 = 26397 points!

Find the first illegal character in each corrupted line of the navigation subsystem. What is the total syntax error score for those errors?

Your puzzle answer was 288291.
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
	int inputLength;													// How long the input file is
	const char* filename = "..\\..\\inputs\\Day10.txt";					// Path to the input file
	char** input = readInput(filename, 3930, &inputLength, false);		// Read in the input file and get it's length
	char currentChunk;													// The current chunk closer we are looking for
	char unclosedChunks[100];											// Chunks that were opened before the current chunk
	int previousChunk = -1;												// Index of the previous chunk in the array
	int score = 0;														// The total score from the corrupted chunks

	// Loop over every line
	for (int i = 0; i < inputLength; i++)
	{
		// Setup first chunk
		currentChunk = input[i][0];

		// Loop along a line until we hit the end
		for (int j = 1; input[i][j] != '\n'; j++)
		{
			// Deal with a new chunk
			if (input[i][j] == '(' || input[i][j] == '[' || input[i][j] == '{' || input[i][j] == '<')
			{
				previousChunk++;
				unclosedChunks[previousChunk] = currentChunk;
				currentChunk = input[i][j];
			}
			else
			{
				// If the current character doesn't match up with the current open chunk, add the score
				if (input[i][j] - 1 != currentChunk && input[i][j] - 2 != currentChunk)
				{
					switch (input[i][j])
					{
						case ')':
							score += 3;
							break;
						
						case ']':
							score += 57;
							break;
						
						case '}':
							score += 1197;
							break;
						
						case '>':
							score += 25137;
							break;
					}
				}
				
				// Start dealing with the previous chunk
				currentChunk = unclosedChunks[previousChunk];
				previousChunk--;
			}
		}

		previousChunk = -1;	// Reset for the next line
	}

	printf("Final score is %d\n", score);

	getchar();
}