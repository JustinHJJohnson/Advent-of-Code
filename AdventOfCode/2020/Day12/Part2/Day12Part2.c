#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Part Two ---

Before you can give the destination to the captain, you realize that the actual action meanings were printed on the back of the instructions the whole time.

Almost all of the actions indicate how to move a waypoint which is relative to the ship's position:

    Action N means to move the waypoint north by the given value.
    Action S means to move the waypoint south by the given value.
    Action E means to move the waypoint east by the given value.
    Action W means to move the waypoint west by the given value.
    Action L means to rotate the waypoint around the ship left (counter-clockwise) the given number of degrees.
    Action R means to rotate the waypoint around the ship right (clockwise) the given number of degrees.
    Action F means to move forward to the waypoint a number of times equal to the given value.

The waypoint starts 10 units east and 1 unit north relative to the ship. The waypoint is relative to the ship; that is, if the ship moves, the waypoint moves with it.

For example, using the same instructions as above:

    F10 moves the ship to the waypoint 10 times (a total of 100 units east and 10 units north), leaving the ship at east 100, north 10. The waypoint stays 10 units east and 1 unit north of the ship.
    N3 moves the waypoint 3 units north to 10 units east and 4 units north of the ship. The ship remains at east 100, north 10.
    F7 moves the ship to the waypoint 7 times (a total of 70 units east and 28 units north), leaving the ship at east 170, north 38. The waypoint stays 10 units east and 4 units north of the ship.
    R90 rotates the waypoint around the ship clockwise 90 degrees, moving it to 4 units east and 10 units south of the ship. The ship remains at east 170, north 38.
    F11 moves the ship to the waypoint 11 times (a total of 44 units east and 110 units south), leaving the ship at east 214, south 72. The waypoint stays 4 units east and 10 units south of the ship.

After these operations, the ship's Manhattan distance from its starting position is 214 + 72 = 286.

Figure out where the navigation instructions actually lead. What is the Manhattan distance between that location and the ship's starting position?
*/

#define NORTH 0
#define EAST 90
#define SOUTH 180
#define WEST 270

const int directions[] = {NORTH, EAST, SOUTH, WEST};

// Mod that handles a negative a value.
//inline int mod(int a, int base)
static inline int mod(int a, int base)
{    
  	return (base + a % base) % base;
}

typedef struct
{
	int x;
	int y;
	int dIndex;	// Index into direction array
} Ship;

void shipInit(Ship* ship)
{
	*ship = *(Ship*)malloc(sizeof(Ship));
	
	ship->x = 0;
	ship->y = 0;
	ship->dIndex = 1;
}

void turnShip(Ship* ship, char direction, int degrees)
{
	if (direction == 'L') degrees *= -1;
	ship->dIndex = mod((ship->dIndex + (degrees / 90)), 4);
}

void moveShipForward(Ship* ship, int distance)
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

void moveShipInDirection(Ship* ship, char direction, int distance)
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

char** readInput(const char *filename, int lineLength, int *numLines)
{
	// Open File
	FILE* fp = fopen(filename, "r");

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
		if (cr == '\n') lines++;
		cr = getc(fp);
	}
	printf("Number of lines: %ld\n", lines); 
	rewind(fp);

	// Read data
	char** data = (char**)malloc(lines * sizeof(char*));
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

	const char* filename = "..\\..\\..\\inputs\\2020\\Day12.txt";

	FILE* fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}
	printf("Opened file: %s\n", filename);

	char buffer[6];
	int linesPrinted = 1;

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