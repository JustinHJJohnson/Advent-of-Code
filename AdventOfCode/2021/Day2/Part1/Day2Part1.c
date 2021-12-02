#include <stdio.h>
#include <stdlib.h>

/*
--- Day 2: Dive! ---

Now, you need to figure out how to pilot this thing.

It seems like the submarine can take a series of commands like forward 1, down 2, or up 3:

    forward X increases the horizontal position by X units.
    down X increases the depth by X units.
    up X decreases the depth by X units.

Note that since you're on a submarine, down and up affect your depth, and so they have the opposite result of what you might expect.

The submarine seems to already have a planned course (your puzzle input). You should probably figure out where it's going. For example:

forward 5
down 5
forward 8
up 3
down 8
forward 2

Your horizontal position and depth both start at 0. The steps above would then modify them as follows:

    forward 5 adds 5 to your horizontal position, a total of 5.
    down 5 adds 5 to your depth, resulting in a value of 5.
    forward 8 adds 8 to your horizontal position, a total of 13.
    up 3 decreases your depth by 3, resulting in a value of 2.
    down 8 adds 8 to your depth, resulting in a value of 10.
    forward 2 adds 2 to your horizontal position, a total of 15.

After following these instructions, you would have a horizontal position of 15 and a depth of 10. (Multiplying these together produces 150.)

Calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?

Your puzzle answer was 2073315.
*/

int main(int argc, char* argv[])
{
	int horizontal = 0;
    int depth = 0;
    
    const char* filename = "..\\..\\inputs\\Day2.txt";	// Path to the input file to read
	char buffer[50];									// Buffer to store the instructions from the file
	FILE* fp = fopen(filename, "r");					// Open the file and store the file

	// Make sure the file successfully opened
	if(!fp)
	{
		perror("getline");
  		exit;
	}
	//printf("Opened file: %s\n", filename);

	// Loop over every instruction in the input file
	while(fgets(buffer, 50, fp))
	{
		int numIndex = 3;                                   // The index in the string of number to move by
        while (buffer[numIndex + 1] != '\n') numIndex++;
        int num = buffer[numIndex] - '0';                   // The number to move by
        
        // Find which move to make and make it
        switch (buffer[0])
        {
            case 'f':
                horizontal += num;
                //printf("horizontal %d\n", num);
                break;
            case 'u':
                depth -= num;
                //printf("up %d\n", num);
                break;
            case 'd':
                depth += num;
                //printf("down %d\n", num);
                break;
        }
        //printf("\ndepth is %d\nhorizontal is %d\n", depth, horizontal);
	}
		
	printf("\nFinal depth is %d\nFinal horizontal is %d\n", depth, horizontal);
    printf("Final position multiplied is %d\n", horizontal * depth);
}