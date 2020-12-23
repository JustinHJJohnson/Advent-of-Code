#include <stdio.h>
#include <stdbool.h>

#define MAX_JOLT_DIF 3



typedef struct AdapterNode
{
	Adapter* adapter;
	Adapter* next;
} AdapterNode;

typedef struct Adapter
{
	int value;
	AdapterNode next;
} Adapter;

int main(int argc, char* argv[])
{
	int input[] =
    {
		153, 17, 45, 57, 16, 147, 39, 121, 75, 70, 85, 134, 128, 115, 51, 139, 44, 65, 119, 168,
		122, 72, 105, 31, 103, 89, 154, 114, 55, 25, 48, 38, 132, 157, 84, 71, 113, 143, 83, 64,
		109, 129, 120, 100, 151, 79, 125, 22, 161, 167, 19, 26, 118, 142, 4, 158, 11, 35, 56, 18,
		40, 7, 150, 99, 54, 152, 60, 27, 164, 78, 47, 82, 63, 46, 91, 32, 135, 3, 108, 10, 159, 127,
		69, 110, 126, 133, 28, 15, 104, 138, 160, 98, 90, 144, 1, 2, 92, 41, 86, 66, 95, 12,
	};
	
	int inputLength = sizeof(input) / sizeof(int);		    //The length of the input array
	int diffCount[MAX_JOLT_DIF] = {0};						//Array to store the number of times each difference occured

	//Sort the joltages into ascending order using bubblesort (too lazy to do more efficient method)
	for (int i = 0; i < inputLength - 1; i++)
	{
		for (int j = i + 1; j < inputLength; j++)
		{
			if (input[i] > input[j])
			{
				int temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}
	}
};