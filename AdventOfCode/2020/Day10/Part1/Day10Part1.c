#include <stdio.h>
#include <stdbool.h>

/*
--- Day 10: Adapter Array ---

Patched into the aircraft's data port, you discover weather forecasts of a massive tropical storm. Before you can figure out whether it will impact your vacation plans, however, your device suddenly turns off!

Its battery is dead.

You'll need to plug it in. There's only one problem: the charging outlet near your seat produces the wrong number of jolts. Always prepared, you make a list of all of the joltage adapters in your bag.

Each of your joltage adapters is rated for a specific output joltage (your puzzle input). Any given adapter can take an input 1, 2, or 3 jolts lower than its rating and still produce its rated output joltage.

In addition, your device has a built-in joltage adapter rated for 3 jolts higher than the highest-rated adapter in your bag. (If your adapter list were 3, 9, and 6, your device's built-in adapter would be rated for 12 jolts.)

Treat the charging outlet near your seat as having an effective joltage rating of 0.

Since you have some time to kill, you might as well test all of your adapters. Wouldn't want to get to your resort and realize you can't even charge your device!

If you use every adapter in your bag at once, what is the distribution of joltage differences between the charging outlet, the adapters, and your device?

For example, suppose that in your bag, you have adapters with the following joltage ratings:

16
10
15
5
1
11
7
19
6
12
4

With these adapters, your device's built-in joltage adapter would be rated for 19 + 3 = 22 jolts, 3 higher than the highest-rated adapter.

Because adapters can only connect to a source 1-3 jolts lower than its rating, in order to use every adapter, you'd need to choose them like this:

    The charging outlet has an effective rating of 0 jolts, so the only adapters that could connect to it directly would need to have a joltage rating of 1, 2, or 3 jolts. Of these, only one you have is an adapter rated 1 jolt (difference of 1).
    From your 1-jolt rated adapter, the only choice is your 4-jolt rated adapter (difference of 3).
    From the 4-jolt rated adapter, the adapters rated 5, 6, or 7 are valid choices. However, in order to not skip any adapters, you have to pick the adapter rated 5 jolts (difference of 1).
    Similarly, the next choices would need to be the adapter rated 6 and then the adapter rated 7 (with difference of 1 and 1).
    The only adapter that works with the 7-jolt rated adapter is the one rated 10 jolts (difference of 3).
    From 10, the choices are 11 or 12; choose 11 (difference of 1) and then 12 (difference of 1).
    After 12, only valid adapter has a rating of 15 (difference of 3), then 16 (difference of 1), then 19 (difference of 3).
    Finally, your device's built-in adapter is always 3 higher than the highest adapter, so its rating is 22 jolts (always a difference of 3).

In this example, when using every adapter, there are 7 differences of 1 jolt and 5 differences of 3 jolts.

Here is a larger example:

28
33
18
42
31
14
46
20
48
47
24
23
49
45
19
38
39
11
1
32
25
35
8
17
7
9
4
2
34
10
3

In this larger example, in a chain that uses all of the adapters, there are 22 differences of 1 jolt and 10 differences of 3 jolts.

Find a chain that uses all of your adapters to connect the charging outlet to your device's built-in adapter and count the joltage differences between the charging outlet, the adapters, and your device. What is the number of 1-jolt differences multiplied by the number of 3-jolt differences?

Your puzzle answer was 2346.*/

#define MAX_JOLT_DIF 3

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

	int inputLength = sizeof(input) / sizeof(int);		    // The length of the input array
	int diffCount[MAX_JOLT_DIF] = {0};						// Array to store the number of times each difference occured

	// Sort the joltages into ascending order using bubblesort (too lazy to do more efficient method)
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

	diffCount[input[0] - 1]++;

	for (int i = 1; i < inputLength; i++) diffCount[(input[i] - input[i - 1]) - 1]++;

	diffCount[MAX_JOLT_DIF - 1]++;

	printf("solution is %d", diffCount[0] * diffCount[2]);
};