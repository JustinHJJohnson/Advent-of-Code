#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Part Two ---

Suppose the lanternfish live forever and have unlimited food and space. Would they take over the entire ocean?

After 256 days in the example above, there would be a total of 26984457539 lanternfish!

How many lanternfish would there be after 256 days?

Your puzzle answer was 1741362314973.
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

long long int simulateDays(long long int fish[], int numDays)
{
	long long int newFish[9];
	long long int numFish = 0;
	
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
	long long int fishCounts[9] = {0,0,0,0,0,0,0,0,0};					// The number of fish grouped by time till they create another lanternfish
	for (int i = 0; i < inputLength; i++) fishCounts[intInput[i]]++;

	//for (int i = 0; i < 9; i++) printf("%d fish with %d on their timer\n", fishCounts[i], i);
	
	printf("There is %lld lanternfish after 256 days\n", simulateDays(fishCounts, 256));

	getchar();
}