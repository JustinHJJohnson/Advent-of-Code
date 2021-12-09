#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Day 6: Lanternfish ---

The sea floor is getting steeper. Maybe the sleigh keys got carried this way?

A massive school of glowing lanternfish swims past. They must spawn quickly to reach such large numbers - maybe exponentially quickly? You should model their growth rate to be sure.

Although you know nothing about this specific species of lanternfish, you make some guesses about their attributes. Surely, each lanternfish creates a new lanternfish once every 7 days.

However, this process isn't necessarily synchronized between every lanternfish - one lanternfish might have 2 days left until it creates another lanternfish, while another might have 4. So, you can model each fish as a single number that represents the number of days until it creates a new lanternfish.

Furthermore, you reason, a new lanternfish would surely need slightly longer before it's capable of producing more lanternfish: two more days for its first cycle.

So, suppose you have a lanternfish with an internal timer value of 3:

	After one day, its internal timer would become 2.
	After another day, its internal timer would become 1.
	After another day, its internal timer would become 0.
	After another day, its internal timer would reset to 6, and it would create a new lanternfish with an internal timer of 8.
	After another day, the first lanternfish would have an internal timer of 5, and the second lanternfish would have an internal timer of 7.

A lanternfish that creates a new fish resets its timer to 6, not 7 (because 0 is included as a valid timer value). The new lanternfish starts with an internal timer of 8 and does not start counting down until the next day.

Realizing what you're trying to do, the submarine automatically produces a list of the ages of several hundred nearby lanternfish (your puzzle input). For example, suppose you were given the following list:

3,4,3,1,2

This list means that the first fish has an internal timer of 3, the second fish has an internal timer of 4, and so on until the fifth fish, which has an internal timer of 2. Simulating these fish over several days would proceed as follows:

Initial state: 3,4,3,1,2
After  1 day:  2,3,2,0,1
After  2 days: 1,2,1,6,0,8
After  3 days: 0,1,0,5,6,7,8
After  4 days: 6,0,6,4,5,6,7,8,8
After  5 days: 5,6,5,3,4,5,6,7,7,8
After  6 days: 4,5,4,2,3,4,5,6,6,7
After  7 days: 3,4,3,1,2,3,4,5,5,6
After  8 days: 2,3,2,0,1,2,3,4,4,5
After  9 days: 1,2,1,6,0,1,2,3,3,4,8
After 10 days: 0,1,0,5,6,0,1,2,2,3,7,8
After 11 days: 6,0,6,4,5,6,0,1,1,2,6,7,8,8,8
After 12 days: 5,6,5,3,4,5,6,0,0,1,5,6,7,7,7,8,8
After 13 days: 4,5,4,2,3,4,5,6,6,0,4,5,6,6,6,7,7,8,8
After 14 days: 3,4,3,1,2,3,4,5,5,6,3,4,5,5,5,6,6,7,7,8
After 15 days: 2,3,2,0,1,2,3,4,4,5,2,3,4,4,4,5,5,6,6,7
After 16 days: 1,2,1,6,0,1,2,3,3,4,1,2,3,3,3,4,4,5,5,6,8
After 17 days: 0,1,0,5,6,0,1,2,2,3,0,1,2,2,2,3,3,4,4,5,7,8
After 18 days: 6,0,6,4,5,6,0,1,1,2,6,0,1,1,1,2,2,3,3,4,6,7,8,8,8,8

Each day, a 0 becomes a 6 and adds a new 8 to the end of the list, while each other number decreases by 1 if it was present at the start of the day.

In this example, after 18 days, there are a total of 26 fish. After 80 days, there would be a total of 5934.

Find a way to simulate lanternfish. How many lanternfish would there be after 80 days?

Your puzzle answer was 388739.
*/

/*typedef struct Node Node;

struct Node {
	int timer;
	Node* next;
};

Node* makeNode(int value)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->timer = value;
	node->next = NULL;
	return node;
}

void insertEnd(int value, Node** head)
{
	Node* node = makeNode(value);

	Node* currentNode = *head;

	if (*head == NULL)
	{
		*head = node;
		return;
	}

	while (currentNode->next != NULL) currentNode = currentNode->next;

	currentNode->next = node;
}

void printList(Node* head)
{
	Node* current = head;
	if (current == NULL) return;

	while (current != NULL)
	{
		printf("%d, ", current->timer);
		current = current->next;
	}
	printf("\n");
}*/

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

int simulateDays(int fish[], int numDays)
{
	int newFish[9];
	int numFish = 0;
	
	for (int i = 0; i < numDays; i++)
	{
		newFish[0] = fish[1];
		newFish[1] = fish[2];
		newFish[2] = fish[3];
		newFish[3] = fish[4];
		newFish[4] = fish[5];
		newFish[5] = fish[6];
		newFish[6] = fish[7] + fish[0];
		newFish[7] = fish[8];
		newFish[8] = fish[0];

		for (int i = 0; i < 9; i++) fish[i] = newFish[i];
	}

	for (int i = 0; i < 9; i++) numFish += newFish[i];

	return numFish;
}

int main(int argc, char* argv[])
{
	int inputLength;													// How long the input file is
	const char* filename = "..\\..\\inputs\\Day6.txt";					// Path to the input file
	char** input = readInput(filename, 610, &inputLength, false);		// Read in the input file and get it's length
	int* intInput = stringToInts(input[0], ',', &inputLength, false);	// The input converted to an array of ints
	int fishCounts[9] = {0,0,0,0,0,0,0,0,0};							// The number of fish grouped by time till they create another lanternfish
	for (int i = 0; i < inputLength; i++) fishCounts[intInput[i]]++;

	//for (int i = 0; i < 9; i++) printf("%d fish with %d on their timer\n", fishCounts[i], i);
	
	printf("There is %d lanternfish after 80 days\n", simulateDays(fishCounts, 80));

	getchar();
}