#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Day 12: Rain Risk ---

Your ferry made decent progress toward the island, but the storm came in faster than anyone expected. The ferry needs to take evasive actions!

Unfortunately, the ship's navigation computer seems to be malfunctioning; rather than giving a route directly to safety, it produced extremely circuitous instructions. When the captain uses the PA system to ask if anyone can help, you quickly volunteer.

The navigation instructions (your puzzle input) consists of a sequence of single-character actions paired with integer input values. After staring at them for a few minutes, you work out what they probably mean:

    Action N means to move north by the given value.
    Action S means to move south by the given value.
    Action E means to move east by the given value.
    Action W means to move west by the given value.
    Action L means to turn left the given number of degrees.
    Action R means to turn right the given number of degrees.
    Action F means to move forward by the given value in the direction the ship is currently facing.

The ship starts by facing east. Only the L and R actions change the direction the ship is facing. (That is, if the ship is facing east and the next instruction is N10, the ship would move north 10 units, but would still move east if the following action were F.)

For example:

F10
N3
F7
R90
F11

These instructions would be handled as follows:

    F10 would move the ship 10 units east (because the ship starts by facing east) to east 10, north 0.
    N3 would move the ship 3 units north to east 10, north 3.
    F7 would move the ship another 7 units east (because the ship is still facing east) to east 17, north 3.
    R90 would cause the ship to turn right by 90 degrees and face south; it remains at east 17, north 3.
    F11 would move the ship 11 units south to east 17, south 8.

At the end of these instructions, the ship's Manhattan distance (sum of the absolute values of its east/west position and its north/south position) from its starting position is 17 + 8 = 25.

Figure out where the navigation instructions lead. What is the Manhattan distance between that location and the ship's starting position?

Your puzzle answer was 1177.
*/

#define NORTH 0
#define EAST 90
#define SOUTH 180
#define WEST 270

const int directions[] = {NORTH, EAST, SOUTH, WEST};

// Mod that handles a negative a value.
inline int mod(int a, int base)
{    
  	return (base + a % base) % base;
}

typedef struct 
{
	int dIndex;	// Index into direction array
	int x;
	int y;
} Ship;

void shipInit(Ship *ship)
{
	ship = (Ship *)malloc(sizeof(Ship));
	
	ship->dIndex = 1;
	ship->x = 0;
	ship->y = 0;
}

void turnShip(Ship *ship, char direction, int degrees)
{
	if (direction == 'L') degrees -= 2 * degrees;
	ship->dIndex = mod((ship->dIndex + (degrees / 90)), 4);
}

void moveShipForward(Ship *ship, int distance)
{
	switch (directions[ship->dIndex])
	{
		case NORTH:
			ship->y += distance;
			break;
		case EAST:
			ship->x += distance;
			break;
		case SOUTH:
			ship->y -= distance;
			break;
		case WEST:
			ship->x -= distance;
			break;
	}
}

void moveShipInDirection(Ship *ship, char direction, int distance)
{
	switch(direction)
    {
        case 'N':
            ship->y += distance;
            break;
        case 'E':
            ship->x += distance;
            break;
        case 'S':
            ship->y -= distance;
            break;
        case 'W':
            ship->x -= distance;
            break;
	}
}

char **readInput(const char *filename, int lineLength, int *numLines)
{
	// Open File
	FILE *fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}
	printf("Opened file: %s\n", filename); 

	// Count Lines
	char cr;
	int lines = 0;

	while(cr != EOF) 
	{
		if ( cr == '\n' ) lines++;
		cr = getc(fp);
	}
	printf("Number of lines: %ld\n", lines); 
	rewind(fp);

	// Read data
	char **data = (char**)malloc(lines * sizeof(char*));
	int n;

	for (int i = 0; i < lines; i++) 
	{
		data[i] = (char*)malloc(lineLength * sizeof(char));
		fscanf(fp, "%s", data[i]);

		if (ferror(fp))
		{
			perror("fopen");
			exit;
		}	
	}

	for (int i = 0; i < lines; i++)
	{
		printf("%s\n", data[i]);
	}

	// Close File
	fclose(fp);

	*numLines = lines;
	return data;
}

int main(int argc, char* argv[])
{
    Ship ship;
	shipInit(&ship);

	char *filename = "..\\..\\inputs\\Day12.txt";

	FILE *fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}
	printf("Opened file: %s\n", filename);

	char buffer[6];
	int linesPrinted = 1;
	
	// Weird hack because ship is not setting up y properly
    ship.x = 0;		
    ship.y = 0;		
    ship.dIndex = 1;
	//printf("Starting state %d, %d, facing %d\n", ship.x, ship.y, ship.dIndex);

	while (fgets(buffer, 10, fp))
	{
		char instruction = buffer[0];
		if (instruction == 'N' || instruction == 'E' || instruction == 'S' || instruction == 'W')
		{
			moveShipInDirection(&ship, instruction, atoi(buffer + 1));
		}
		else if (instruction == 'L' || instruction == 'R')
		{
			turnShip(&ship, instruction, atoi(buffer + 1));
		}
		else if (instruction == 'F')
		{
			moveShipForward(&ship, atoi(buffer + 1));
		}
		else
		{
			printf("Invalid command: %s\n", buffer);
			return 1;
		}
		//printf("%d Instruction: %s\n", linesPrinted++, buffer);
		//printf("Ship was at %d, %d, facing %d\n", ship.x, ship.y, ship.dIndex);
    }

	printf("Ship is at %d, %d facing %d\n", ship.x, ship.y, directions[ship.dIndex]);
	printf("Ship's Manhattan distance is %d\n", abs(ship.x) + abs(ship.y));

	getchar();
}