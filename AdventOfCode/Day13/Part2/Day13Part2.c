#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

/*
--- Part Two ---

The shuttle company is running a contest: one gold coin for anyone that can find the earliest timestamp such that the first bus ID departs at that time and each subsequent listed bus ID departs at that subsequent minute. (The first line in your input is no longer relevant.)

For example, suppose you have the same list of bus IDs as above:

7,13,x,x,59,x,31,19

An x in the schedule means there are no constraints on what bus IDs must depart at that time.

This means you are looking for the earliest timestamp (called t) such that:

    Bus ID 7 departs at timestamp t.
    Bus ID 13 departs one minute after timestamp t.
    There are no requirements or restrictions on departures at two or three minutes after timestamp t.
    Bus ID 59 departs four minutes after timestamp t.
    There are no requirements or restrictions on departures at five minutes after timestamp t.
    Bus ID 31 departs six minutes after timestamp t.
    Bus ID 19 departs seven minutes after timestamp t.

The only bus departures that matter are the listed bus IDs at their specific offsets from t. Those bus IDs can depart at other times, and other bus IDs can depart at those times. For example, in the list above, because bus ID 19 must depart seven minutes after the timestamp at which bus ID 7 departs, bus ID 7 will always also be departing with bus ID 19 at seven minutes after timestamp t.

In this example, the earliest timestamp at which this occurs is 1068781:

time     bus 7   bus 13  bus 59  bus 31  bus 19
1068773    .       .       .       .       .
1068774    D       .       .       .       .
1068775    .       .       .       .       .
1068776    .       .       .       .       .
1068777    .       .       .       .       .
1068778    .       .       .       .       .
1068779    .       .       .       .       .
1068780    .       .       .       .       .
1068781    D       .       .       .       .
1068782    .       D       .       .       .
1068783    .       .       .       .       .
1068784    .       .       .       .       .
1068785    .       .       D       .       .
1068786    .       .       .       .       .
1068787    .       .       .       D       .
1068788    D       .       .       .       D
1068789    .       .       .       .       .
1068790    .       .       .       .       .
1068791    .       .       .       .       .
1068792    .       .       .       .       .
1068793    .       .       .       .       .
1068794    .       .       .       .       .
1068795    D       D       .       .       .
1068796    .       .       .       .       .
1068797    .       .       .       .       .

In the above example, bus ID 7 departs at timestamp 1068788 (seven minutes after t). This is fine; the only requirement on that minute is that bus ID 19 departs then, and it does.

Here are some other examples:

    The earliest timestamp that matches the list 17,x,13,19 is 3417.
    67,7,59,61 first occurs at timestamp 754018.
    67,x,7,59,61 first occurs at timestamp 779210.
    67,7,x,59,61 first occurs at timestamp 1261476.
    1789,37,47,1889 first occurs at timestamp 1202161486.

However, with so many bus IDs in your list, surely the actual earliest timestamp will be larger than 100000000000000!

What is the earliest timestamp such that all of the listed bus IDs depart at offsets matching their positions in the list?*/

#define NUM_TIMESTAMP_PER_THREAD 10000000

LONG solution = 0;     // Variable that stores the solution when it is found
LONG solutionFound = 0;

void timestampCheck(char* input[], int startTimestamp, int endTimestamp, int numBuses, int busesTimes[], int firstBusTime)
{
	int currentTimestamp = startTimestamp;

	bool solutionLocated = false;

	if (currentTimestamp % firstBusTime != 0) currentTimestamp = startTimestamp + (firstBusTime - (startTimestamp % firstBusTime));

	// printf("%d\n", currentTimestamp % firstBusTime);
	
	while (!solutionLocated && currentTimestamp <= endTimestamp)
    {
        solutionLocated = true;
        // printf("current timestamp %d\n", currentTimestamp);
        
        for (int i = 0; i < numBuses; i++)
        {
            // printf("%d %d %d %d\n", currentTimestamp, currentTimestamp + busesTimes[i], atoi(input[busesTimes[i]]), busesTimes[i]);
			
			if ((currentTimestamp + busesTimes[i]) % atoi(input[busesTimes[i]]) != 0)
            {
                solutionLocated = false;
				break;
                // printf("%d %s\n", currentTimestamp + busesTimes[i], input[busesTimes[i]]);
            }
        }

        if (!solutionLocated) currentTimestamp += atoi(input[0]);
	}
	
	if (solutionFound != 0 || solution != 0 || solutionLocated == false) return;

	if (solutionLocated)
	{
		LONG solutionCheck = InterlockedExchange(&solution, currentTimestamp);

		if (solutionCheck != 0) InterlockedExchange(&solution, solutionCheck);
		InterlockedIncrement(&solutionFound);
	}
}

// Struct to store the information for each thread
typedef struct ThreadData
{
	char** input;
	int startTimestamp;
	int endTimestamp;
	int numBuses;
	int* busesTimes;
	int firstBusTime;
} ThreadData;

DWORD __stdcall changeInstructionStart(LPVOID threadData)
{
	// cast the pointer to void (i.e. an untyped pointer) into something we can use
	ThreadData* data = (ThreadData*)threadData;

	// pass parameters through
	timestampCheck(data->input, data->startTimestamp, data->endTimestamp, data->numBuses, data->busesTimes, data->firstBusTime);

	ExitThread(NULL);
}

int main(int argc, char* argv[])
{
	char* input[] =
    {
		"17",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"37",
		"x",
		"x",
		"x",
		"x",
		"x",
		"739",
		"x",
		"29",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"13",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"23",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"971",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"41",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"x",
		"19",
	};

	int inputSelect = 5;

	// char* input[] = {"17", "x", "13", "19"}; int inputSelect = 0;
	// char* input[] = {"67", "7", "59", "61"}; int inputSelect = 1;
	// char* input[] = {"67", "x", "7", "59", "61"}; int inputSelect = 2;
	// char* input[] = {"67", "7", "x", "59", "61"}; int inputSelect = 3;
	// char* input[] = {"1789", "37", "47", "1889"}; int inputSelect = 4;

	int threads = 12;
	int inputLength = sizeof(input) / sizeof(char*);	// The length of the input array
    int firstBusTimestamp = atoi(input[0]);
    int numBuses = 0;
    int* busesTimes;

	/*int test1 = 24;
	int test2 = test1 + (17 - (test1 % 17));

	printf("%d %d %f\n%d %d %f", test1, test1 % 17, (float)test1 / 17, test2, test2 % 17, (float)test2 / 17);

	return 0;*/
	
    for (int i = 1; i < inputLength; i++) if (input[i][0] != 'x') numBuses++;

    busesTimes = (int*)malloc(sizeof(int) * numBuses);

    int currentIndex = 0;

    for (int i = 1; i < inputLength; i++)
    {
        if (input[i][0] != 'x')
        {
            busesTimes[currentIndex] = i;
            currentIndex++;
        }
    }

    // for (int i = 0; i < numBuses; i++) printf("%d %d\n", atoi(input[busesTimes[i]]), busesTimes[i]);

	int numThreadsRan = 0;
	
	while (solution == 0)
	{
		// Setup the thread handles and thread data
		HANDLE* threadHandles = (HANDLE*)malloc(threads * sizeof(HANDLE));
		ThreadData* threadData = (ThreadData*)malloc(threads * sizeof(ThreadData));

		// Create and run the specified number of threads
		for (int i = 0; i < threads; i++)
		{
			threadData[i].input = input;
			threadData[i].startTimestamp = numThreadsRan * NUM_TIMESTAMP_PER_THREAD;
			threadData[i].endTimestamp = threadData[i].startTimestamp + NUM_TIMESTAMP_PER_THREAD;
			threadData[i].numBuses = numBuses;
			threadData[i].busesTimes = busesTimes;
			threadData[i].firstBusTime = firstBusTimestamp;
			numThreadsRan++;

			threadHandles[i] = CreateThread(NULL, 0, changeInstructionStart, (void*)&threadData[i], 0, NULL);
		}

		// wait for threads to finish
		WaitForMultipleObjects(threads, threadHandles, true, INFINITE);

		// Free up memory
		free(threadHandles);
		free(threadData);
	}

    switch(inputSelect)
	{
		case 0: 
			printf("solution should be 3417, got %d", solution);
			break;
		case 1: 
			printf("solution should be 754018, got %d", solution);
			break;
		case 2: 
			printf("solution should be 779210, got %d", solution);
			break;
		case 3: 
			printf("solution should be 1261476, got %d", solution);
			break;
		case 4: 
			printf("solution should be 1202161486, got %d", solution);
			break;
		case 5: 
			printf("solution is %d", solution);
			break;
	}
	
	// printf("solution is %d", solution);
    

	// printf("Earliest bus is bus %d, with a wait of %d minutes. So the solution is %d", earliestBus, shortestWait, earliestBus * shortestWait);
};