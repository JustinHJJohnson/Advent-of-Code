#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_JOLT_DIF 3

typedef struct Adapter Adapter;

struct Adapter
{
	int value;
	int* next;
	int numNext;
};

void initAdapter(Adapter* a, int index, int value)
{
	a[index].value = value;
	a[index].next = NULL;
}

void addNext(Adapter* a, int input[], int inputIndex)
{
	int numNext = 0;
	int nextIndex = inputIndex + 1;

	while (input[nextIndex] - input[inputIndex] <= MAX_JOLT_DIF && input[nextIndex] - input[inputIndex] > 0)
	{
		numNext++;
		nextIndex++;
	}

	a[inputIndex].next = (int*)malloc(sizeof(int) * numNext);

	a[inputIndex].numNext = numNext;

	for (int i = inputIndex + 1; i < inputIndex + numNext; i++) a[inputIndex + 1].next[i - inputIndex] = i;
}

int main(int argc, char* argv[])
{
	/*int input[] =
	{
		153, 17, 45, 57, 16, 147, 39, 121, 75, 70, 85, 134, 128, 115, 51, 139, 44, 65, 119, 168,
		122, 72, 105, 31, 103, 89, 154, 114, 55, 25, 48, 38, 132, 157, 84, 71, 113, 143, 83, 64,
		109, 129, 120, 100, 151, 79, 125, 22, 161, 167, 19, 26, 118, 142, 4, 158, 11, 35, 56, 18,
		40, 7, 150, 99, 54, 152, 60, 27, 164, 78, 47, 82, 63, 46, 91, 32, 135, 3, 108, 10, 159, 127,
		69, 110, 126, 133, 28, 15, 104, 138, 160, 98, 90, 144, 1, 2, 92, 41, 86, 66, 95, 12,
	};*/

	int input[] =
	{
		16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4
	};

	// 1, 4, 5, 6, 7, 10, 11, 12, 15, 16, 19

	int inputLength = sizeof(input) / sizeof(int);		    // The length of the input array
	int numVariations = 0;									// The number of variations found
	int currentIndex = 0;
	Adapter* adapters;
	int maxAdapter = 0;

	// Sort the joltages into ascending order using bubblesort (too lazy to do more efficient method)
	for (int i = 0; i < inputLength - 1; i++)
	{
		for (int j = i + 1; j < inputLength; j++)
		{
			if (input[i] > maxAdapter) maxAdapter = input[i];

			if (input[i] > input[j])
			{
				int temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}
	}

	// for (int i = 0; i < inputLength; i++) printf("%d\n", input[i]);

	printf("\n\n");

	// printf("inputLength %d\n", inputLength);

	adapters = (Adapter*)calloc(sizeof(Adapter), (inputLength + 2));

	initAdapter(adapters, 0, 0);

	for (int i = 1; i <= inputLength; i++) initAdapter(adapters, i, input[i - 1]);

	initAdapter(adapters, inputLength + 1, maxAdapter + MAX_JOLT_DIF);

	for (int i = 0; i <= inputLength; i++) addNext(adapters, input, i);

	// for (int i = 0; i <= inputLength; i++) printf("%d\n", adapters[i].value);

	// printf("\n\n");

	for (int i = 0; i < inputLength; i++)
	{
		printf("Adapter %d: ", adapters[i].value);
		printf("Num Next: %d ", adapters[i].numNext);
		for (int j = 0; j < adapters[i].numNext; j++) 
		{
			int nextAdapterIndex =	adapters[i].next[j];
			printf("%d ", adapters[nextAdapterIndex].value);
		}
		printf("\n");
	}
};