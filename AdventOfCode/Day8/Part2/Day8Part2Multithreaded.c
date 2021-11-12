#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

/*
--- Part Two ---

After some careful analysis, you believe that exactly one instruction is corrupted.

Somewhere in the program, either a jmp is supposed to be a nop, or a nop is supposed to be a jmp. (No acc instructions were harmed in the corruption of this boot code.)

The program is supposed to terminate by attempting to execute an instruction immediately after the last instruction in the file. By changing exactly one jmp or nop, you can repair the boot code and make it terminate correctly.

For example, consider the same program from above:

nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6

If you change the first instruction from nop +0 to jmp +0, it would create a single-instruction infinite loop, never leaving that instruction. If you change almost any of the jmp instructions, the program will still eventually find another jmp instruction and loop forever.

However, if you change the second-to-last instruction (from jmp -4 to nop -4), the program terminates! The instructions are visited in this order:

nop +0  | 1
acc +1  | 2
jmp +4  | 3
acc +3  |
jmp -3  |
acc -99 |
acc +1  | 4
nop -4  | 5
acc +6  | 6

After the last instruction (acc +6), the program terminates by attempting to run the instruction below the last instruction in the file. With this change, after the program terminates, the accumulator contains the value 8 (acc +1, acc +1, acc +6).

Fix the program so that it terminates normally by changing exactly one jmp (to nop) or nop (to jmp). What is the value of the accumulator after the program terminates?

Your puzzle answer was 733.*/

LONG solutionFound = 0;     // Variable that stores the solution when it is found

// Get the value out of an instruction
int getInstructionValue(char* input, int startIndex)
{
	// Calulate the start and end of the instruction value and how many digits it is
	int endIndex = strlen(input) - 1;
	int inputIndex = startIndex;
	int strLength = (endIndex + 1) - startIndex;

	// Allocate memory for the string using calloc so each value in the string is inialised to the string terminating character
	char* instructionValue = (char*)calloc((size_t)strLength + 1, sizeof(char));

	// Loop over the instruction value and copy it to another string
	for (int i = 0; i < strLength; i++)
	{
		instructionValue[i] = input[inputIndex];
		inputIndex++;
	}

	// Convert the value in the instruction to an int
	int output = atoi(instructionValue);

	// Free up the memory used to store the string version of the instruction value
	free(instructionValue);

	if (input[startIndex - 1] == '+') return output;
	else return output / -1;
}

// Run the input instructions, changing the instruction at the instructionChangeIndex
void changeInstruction(char* input[], int instructionChangeIndex, int inputLength, int threadID)
{
	int inputIndex = 0;																// Which index in the input array we are up to
	int accumulator = 0;															// The accumulator
	bool* instructionsRan = (bool*)calloc((size_t)inputLength - 1, sizeof(bool));	// Array of all the instructions that have already been ran

	// loop over the input array until getting back to previously ran instructions or the end of the instructions
	while (inputIndex < inputLength - 1 && instructionsRan[inputIndex] == false)
	{
		// Check if this is the instruction to change and 
		if (inputIndex == instructionChangeIndex)
		{
			if (input[inputIndex][0] == 'j')
			{
				instructionsRan[inputIndex] = true;
				inputIndex++;
			}
			else if (input[inputIndex][0] == 'n')
			{
				instructionsRan[inputIndex] = true;

				int instruction = getInstructionValue(input[inputIndex], 5);

				inputIndex += instruction;
			}
		}
		// Check which instruction to run
		else if (input[inputIndex][0] == 'a')
		{
			int instruction = getInstructionValue(input[inputIndex], 5);

			accumulator += instruction;

			instructionsRan[inputIndex] = true;
			inputIndex++;
		}
		else if (input[inputIndex][0] == 'j')
		{
			instructionsRan[inputIndex] = true;

			int instruction = getInstructionValue(input[inputIndex], 5);

			inputIndex += instruction;
		}
		else if (input[inputIndex][0] == 'n')
		{
			instructionsRan[inputIndex] = true;
			inputIndex++;
		}
	}

	free(instructionsRan);

	if (inputIndex == inputLength - 1) solutionFound = accumulator;
	return;
}

// Struct to store the information for each thread
typedef struct ThreadData
{
	char** input;
	int instructionChangeIndex;
	int inputLength;
	int threadID;
} ThreadData;

DWORD __stdcall changeInstructionStart(LPVOID threadData)
{
	// cast the pointer to void (i.e. an untyped pointer) into something we can use
	ThreadData* data = (ThreadData*)threadData;

	// pass parameters through
	changeInstruction(data->input, data->instructionChangeIndex, data->inputLength, data->threadID);

	ExitThread(NULL);
}

int main(int argc, char* argv[])
{
	char* input[] =
	{
		"acc +29",
		"acc +0",
		"acc +36",
		"jmp +292",
		"acc +11",
		"acc +16",
		"nop +280",
		"nop +320",
		"jmp +310",
		"acc +15",
		"jmp +76",
		"acc +31",
		"acc +6",
		"acc +29",
		"acc +35",
		"jmp +524",
		"acc +4",
		"acc +12",
		"jmp +162",
		"acc +14",
		"acc -10",
		"jmp +312",
		"acc +19",
		"jmp +385",
		"acc +46",
		"acc +13",
		"acc -19",
		"jmp +366",
		"jmp +56",
		"acc -9",
		"nop +74",
		"jmp +357",
		"acc +28",
		"jmp +223",
		"acc -12",
		"jmp +292",
		"nop +385",
		"acc +45",
		"jmp +255",
		"jmp +337",
		"nop +465",
		"acc +43",
		"jmp +555",
		"acc +20",
		"acc +23",
		"acc +39",
		"jmp -6",
		"acc -4",
		"jmp -39",
		"acc +7",
		"acc -13",
		"acc +41",
		"acc +4",
		"jmp +80",
		"jmp +1",
		"jmp +484",
		"acc -16",
		"acc +2",
		"acc +20",
		"jmp +244",
		"jmp +258",
		"acc +27",
		"acc -7",
		"acc +40",
		"nop +490",
		"jmp +247",
		"nop +363",
		"acc +46",
		"acc +27",
		"acc -4",
		"jmp +379",
		"jmp +62",
		"acc -15",
		"acc +38",
		"acc -4",
		"acc +4",
		"jmp +312",
		"acc +37",
		"jmp +271",
		"acc +3",
		"jmp +538",
		"jmp +1",
		"acc +33",
		"jmp +99",
		"jmp +107",
		"jmp -38",
		"jmp +359",
		"jmp +1",
		"acc +11",
		"acc -3",
		"jmp +109",
		"acc +17",
		"jmp +146",
		"acc +34",
		"acc -5",
		"jmp +174",
		"jmp +482",
		"acc +43",
		"acc +35",
		"acc +8",
		"acc +36",
		"jmp -41",
		"jmp +260",
		"jmp -49",
		"acc +30",
		"nop -33",
		"acc +49",
		"acc +40",
		"jmp +157",
		"acc -11",
		"acc -11",
		"acc +21",
		"acc +35",
		"jmp +489",
		"jmp +219",
		"acc +33",
		"acc +22",
		"jmp +224",
		"jmp +1",
		"jmp +278",
		"acc +0",
		"acc +31",
		"jmp +271",
		"acc -19",
		"acc +38",
		"acc -15",
		"acc +0",
		"jmp +81",
		"acc +7",
		"acc +50",
		"nop +55",
		"nop +2",
		"jmp +195",
		"acc -18",
		"acc +14",
		"jmp +1",
		"jmp -57",
		"acc -17",
		"nop +495",
		"jmp -21",
		"jmp +1",
		"acc +39",
		"acc +35",
		"acc +27",
		"jmp +301",
		"acc +6",
		"acc +11",
		"acc -10",
		"jmp +1",
		"jmp +56",
		"acc +38",
		"jmp +333",
		"acc +26",
		"acc -15",
		"acc +32",
		"acc -9",
		"jmp +412",
		"acc -17",
		"acc +9",
		"jmp +110",
		"nop +298",
		"acc +4",
		"acc +25",
		"acc +0",
		"jmp -136",
		"acc +24",
		"jmp +418",
		"acc -2",
		"acc +38",
		"jmp +92",
		"acc +5",
		"acc +22",
		"acc -4",
		"acc -12",
		"jmp +241",
		"acc +19",
		"nop -6",
		"acc -11",
		"acc +24",
		"jmp +236",
		"jmp +106",
		"jmp +343",
		"jmp -17",
		"acc +5",
		"jmp +143",
		"nop +354",
		"acc +20",
		"acc -11",
		"jmp +63",
		"nop +252",
		"jmp +96",
		"acc -11",
		"acc +35",
		"nop +409",
		"acc +2",
		"jmp +83",
		"acc +0",
		"acc -1",
		"jmp +299",
		"acc +46",
		"jmp +426",
		"acc +8",
		"acc +50",
		"acc +33",
		"jmp +384",
		"nop -20",
		"jmp -152",
		"jmp +283",
		"nop -161",
		"nop -76",
		"acc +34",
		"nop -202",
		"jmp -98",
		"acc +11",
		"jmp +194",
		"acc +12",
		"acc +32",
		"acc -18",
		"acc +4",
		"jmp +202",
		"acc -12",
		"acc +43",
		"acc -11",
		"jmp +70",
		"acc +8",
		"acc -5",
		"acc +9",
		"jmp -187",
		"acc +49",
		"acc +42",
		"acc +10",
		"jmp +274",
		"jmp -216",
		"acc -11",
		"acc -8",
		"acc +49",
		"nop -56",
		"jmp -197",
		"nop -33",
		"nop -167",
		"jmp -174",
		"acc +41",
		"acc +19",
		"acc +13",
		"jmp +334",
		"acc +48",
		"acc +37",
		"acc +35",
		"jmp +323",
		"jmp +1",
		"jmp -184",
		"nop +76",
		"acc +47",
		"acc +5",
		"jmp -150",
		"jmp +133",
		"acc -1",
		"jmp +197",
		"nop +175",
		"acc +28",
		"jmp +328",
		"jmp +209",
		"nop -190",
		"jmp +1",
		"jmp +181",
		"acc +33",
		"acc +34",
		"jmp +345",
		"jmp -118",
		"acc +40",
		"acc +36",
		"nop +32",
		"jmp +261",
		"acc +38",
		"acc +1",
		"acc -19",
		"acc +48",
		"jmp +320",
		"acc +32",
		"acc -7",
		"acc +34",
		"jmp +64",
		"acc +6",
		"acc +3",
		"acc -11",
		"jmp +293",
		"acc +49",
		"acc +23",
		"acc +46",
		"jmp +231",
		"jmp +1",
		"acc -17",
		"jmp +35",
		"jmp -78",
		"jmp +82",
		"acc +31",
		"nop +31",
		"acc +35",
		"acc +42",
		"jmp -208",
		"acc +2",
		"acc -16",
		"jmp +139",
		"nop -170",
		"acc -4",
		"acc +22",
		"acc +9",
		"jmp +295",
		"nop -248",
		"acc +33",
		"acc +32",
		"jmp +186",
		"acc -11",
		"jmp +151",
		"acc +15",
		"acc -7",
		"acc +20",
		"jmp -215",
		"acc +43",
		"acc +12",
		"acc +6",
		"acc +5",
		"jmp +225",
		"acc +15",
		"jmp +1",
		"nop +263",
		"jmp -317",
		"acc +34",
		"jmp +1",
		"jmp -275",
		"acc -15",
		"acc -12",
		"jmp +165",
		"nop -254",
		"acc +12",
		"nop +277",
		"jmp +105",
		"acc +35",
		"jmp +1",
		"acc +34",
		"jmp +93",
		"acc +9",
		"jmp -282",
		"acc +43",
		"jmp -335",
		"acc +21",
		"jmp -114",
		"acc +30",
		"jmp -246",
		"acc -17",
		"acc +10",
		"nop -211",
		"nop +202",
		"jmp +76",
		"acc +34",
		"acc +23",
		"acc +9",
		"acc +48",
		"jmp -208",
		"jmp -241",
		"acc +37",
		"jmp +97",
		"acc +10",
		"acc +47",
		"nop -292",
		"acc -13",
		"jmp +27",
		"acc -18",
		"nop -56",
		"jmp +33",
		"acc +7",
		"jmp -12",
		"acc -11",
		"acc -2",
		"acc +13",
		"jmp -328",
		"acc +21",
		"acc +30",
		"jmp -208",
		"acc -7",
		"jmp -87",
		"acc +41",
		"nop +76",
		"acc +22",
		"jmp +222",
		"acc +48",
		"acc +4",
		"jmp +225",
		"jmp +200",
		"acc -14",
		"acc -12",
		"nop -79",
		"jmp +192",
		"acc +41",
		"acc +3",
		"jmp -355",
		"jmp -292",
		"acc -18",
		"jmp -174",
		"acc +44",
		"acc +23",
		"jmp -163",
		"acc +5",
		"nop -125",
		"nop -7",
		"acc +41",
		"jmp -266",
		"jmp +90",
		"acc +5",
		"jmp +213",
		"acc +10",
		"acc -11",
		"nop -403",
		"jmp +1",
		"jmp -386",
		"acc -18",
		"acc +9",
		"nop +107",
		"acc +0",
		"jmp -383",
		"jmp +104",
		"acc +30",
		"acc -3",
		"nop -208",
		"acc -15",
		"jmp +211",
		"acc -12",
		"acc +18",
		"jmp -392",
		"acc +25",
		"acc +30",
		"jmp -170",
		"jmp -282",
		"acc +38",
		"acc -16",
		"jmp -108",
		"acc +29",
		"acc +31",
		"acc +29",
		"acc +32",
		"jmp -258",
		"acc -16",
		"jmp -40",
		"acc +41",
		"jmp -365",
		"acc +17",
		"acc +20",
		"jmp -77",
		"jmp -55",
		"acc +3",
		"acc +28",
		"nop -227",
		"jmp +116",
		"jmp +165",
		"acc +16",
		"jmp -74",
		"acc -4",
		"jmp -275",
		"acc +28",
		"jmp -254",
		"acc +13",
		"acc -12",
		"acc -16",
		"jmp -5",
		"acc +17",
		"nop -369",
		"nop -375",
		"nop +66",
		"jmp -173",
		"jmp -40",
		"jmp -448",
		"acc -10",
		"nop -332",
		"acc +39",
		"acc -8",
		"jmp +64",
		"acc -19",
		"acc +14",
		"jmp -376",
		"acc +20",
		"acc +25",
		"acc +11",
		"acc +29",
		"jmp -392",
		"acc +33",
		"acc +28",
		"nop -241",
		"acc -6",
		"jmp +2",
		"jmp -410",
		"acc +15",
		"nop -351",
		"jmp -254",
		"acc -2",
		"acc +15",
		"acc +11",
		"jmp -103",
		"acc +29",
		"acc +7",
		"jmp +21",
		"acc +20",
		"acc +3",
		"acc -4",
		"acc +31",
		"jmp -7",
		"acc -1",
		"jmp +1",
		"jmp -158",
		"acc +11",
		"acc -8",
		"jmp +123",
		"acc -9",
		"acc +42",
		"acc +6",
		"acc -18",
		"jmp -483",
		"nop -507",
		"acc +37",
		"acc -10",
		"jmp -61",
		"jmp +98",
		"acc +38",
		"acc +36",
		"jmp -358",
		"nop -231",
		"acc +23",
		"acc +49",
		"jmp -151",
		"acc +48",
		"acc +2",
		"acc +19",
		"acc +34",
		"jmp -8",
		"acc -14",
		"acc -16",
		"jmp -439",
		"acc -7",
		"acc -14",
		"jmp -466",
		"acc +1",
		"nop -254",
		"acc +11",
		"jmp -72",
		"acc +33",
		"acc +11",
		"acc +40",
		"jmp -428",
		"acc +26",
		"acc +8",
		"acc +19",
		"jmp -305",
		"nop +71",
		"acc +3",
		"jmp -457",
		"acc -6",
		"acc +36",
		"jmp +77",
		"acc +11",
		"nop +68",
		"jmp -69",
		"acc +7",
		"acc -8",
		"acc +50",
		"jmp -516",
		"acc +11",
		"acc +46",
		"acc +4",
		"jmp -179",
		"jmp -265",
		"nop -64",
		"jmp +63",
		"acc +27",
		"nop -340",
		"jmp -62",
		"acc +15",
		"acc +42",
		"acc -9",
		"jmp -549",
		"acc +3",
		"acc -10",
		"acc +28",
		"jmp -376",
		"jmp +1",
		"jmp -78",
		"jmp -87",
		"acc +34",
		"acc -17",
		"jmp -275",
		"acc +50",
		"acc +17",
		"acc +39",
		"jmp -133",
		"nop -331",
		"acc +33",
		"acc +38",
		"acc +25",
		"jmp -215",
		"acc +0",
		"acc -9",
		"jmp -258",
		"acc +25",
		"jmp -81",
		"jmp -574",
		"acc +37",
		"acc +48",
		"jmp -327",
		"acc +34",
		"nop -493",
		"acc +42",
		"jmp -459",
		"jmp +1",
		"jmp -135",
		"jmp -489",
		"acc +33",
		"acc +19",
		"acc +17",
		"acc +7",
		"jmp -106",
		"nop -164",
		"jmp -462",
		"acc +27",
		"jmp -612",
		"acc +15",
		"jmp -438",
		"acc +35",
		"jmp -171",
		"acc +10",
		"acc +4",
		"acc +34",
		"jmp -496",
		"nop -4",
		"acc +16",
		"jmp -541",
		"acc +13",
		"jmp -201",
		"jmp -551",
		"acc +40",
		"acc +9",
		"acc +0",
		"acc +33",
		"jmp +1",
	};

	int threads = 12;									// Number of threads to use											
	int inputLength = sizeof(input) / sizeof(char*);	// The length of the input array
	int numInstructionsChange = 0;                      // The number of instructions that can be changed to try to stop the halting problem
	int currentIndex = 0;                               // The current index in the instructionChangeIndexes array                
	int* instructionChangeIndexes;                      // Stores the indexes of all the instructions that can be changed

	// Find the number of instructions that can be changed
    for (int i = 0; i < inputLength; i++)
	{
		char instruction[] = { input[i][0], input[i][1], input[i][2], '\0' };

		if (!strcmp(instruction, "jmp") || !strcmp(instruction, "nop")) numInstructionsChange++;
	}

    // Create an array to store the indexes of every instruction that can be changed
	instructionChangeIndexes = (int*)malloc(numInstructionsChange * sizeof(int*));

	// Fill the instructionChangeIndexes array
    for (int i = 0; i < inputLength; i++)
	{
		char instruction[] = { input[i][0], input[i][1], input[i][2], '\0' };

		if (!strcmp(instruction, "jmp") || !strcmp(instruction, "nop"))
		{
			instructionChangeIndexes[currentIndex] = i;
			currentIndex++;
		}
	}

	currentIndex = 0;

	// try changing each instruction in the instructionChangeIndexes array until the code gets to the end of the instruction array
	while (solutionFound == 0 && currentIndex < numInstructionsChange)
	{
		// Make sure that the threads don't go past the end of the instructionChangeIndexes array
		if (currentIndex + threads > numInstructionsChange) threads = numInstructionsChange - currentIndex;
		
		// Setup the thread handles and thread data
		HANDLE* threadHandles = (HANDLE*)malloc(threads * sizeof(HANDLE));
		ThreadData* threadData = (ThreadData*)malloc(threads * sizeof(ThreadData));

		// Create and run the specified number of threads
		for (int i = 0; i < threads && currentIndex < numInstructionsChange; i++)
		{
			threadData[i].input = input;
			threadData[i].instructionChangeIndex = instructionChangeIndexes[currentIndex];
			threadData[i].inputLength = inputLength;
			threadData[i].threadID = i;
			currentIndex++;

			threadHandles[i] = CreateThread(NULL, 0, changeInstructionStart, (void*)&threadData[i], 0, NULL);
		}

		// wait for threads to finish
		WaitForMultipleObjects(threads, threadHandles, true, INFINITE);

		// Free up memory
		free(threadHandles);
		free(threadData);
	}

	printf("\naccumulator is %d\n", solutionFound);
};