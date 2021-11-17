#include <stdio.h>
#include <stdlib.h>

/*
--- Part Two---

While it appears you validated the passwords correctly, they don't seem to be what the Official Toboggan Corporate Authentication System is expecting.

The shopkeeper suddenly realizes that he just accidentally explained the password policy rules from his old job at the sled rental place down the street!
The Official Toboggan Corporate Policy actually works a little differently.

Each policy actually describes two positions in the password, where 1 means the first character, 2 means the second character, and so on.
(Be careful; Toboggan Corporate Policies have no concept of "index zero"!) Exactly one of these positions must contain the given letter.
Other occurrences of the letter are irrelevant for the purposes of policy enforcement.

Given the same example list from above :

1 - 3 a : abcde is valid : position 1 contains a and position 3 does not.
1 - 3 b : cdefg is invalid : neither position 1 nor position 3 contains b.
2 - 9 c : ccccccccc is invalid : both position 2 and position 9 contain c.

How many passwords are valid according to the new interpretation of the policies?

Your puzzle answer was 482.*/

int main(int argc, char* argv[])
{
	int pos1Index = 0;				// The index of the first security character in the password string
	int pos2Index = 2;				// The index of the second security character in the password string
	int charIndex = 4;				// The index of the security character in the password string
	int numValidPasswords = 0;		// Total number of valid passwords

	const char* filename = "..\\..\\inputs\\Day2.txt";	// Path to the input file to read
	char buffer[50];												// Buffer to store the passwords from the file
	FILE* fp = fopen(filename, "r");								// Open the file and store the file

	// Make sure the file successfully opened
	if(!fp)
	{
		perror("getline");
  		exit;
	}
	//printf("Opened file: %s\n", filename);

	// Loop over every password in the input file
	while(fgets(buffer, 50, fp))
	{
		int pos1 = 0;				// The pos1 number of occurences of the security character
		int pos2 = 0;				// The pos2 number of occurences of the security character
		char c;				// The security character
		int numValidateChar = 0;	// Number of occurences of the security charater in the current string

		pos1Index = 0;
		pos2Index = 2;
		charIndex = 4;

		// Get the first position index from the string
		pos1 = buffer[pos1Index] - '0';

		// Check if the first position is two digits and make corrections to other indexes
		if (buffer[pos1Index + 1] != '-')
		{
			pos1 = pos1 * 10 + (buffer[pos1Index + 1] - '0');
			pos2Index++;
			charIndex++;
		}

		// Get the second postion index from the string
		pos2 = buffer[pos2Index] - '0';

		 // Check if the second postion is two digits and make correction to the security character index
		if (buffer[pos2Index + 1] != ' ')
		{
			pos2 = pos2 * 10 + (buffer[pos2Index + 1] - '0');
			charIndex++;
		}

		// Get the security character from the string
		c = buffer[charIndex];

		// Move the position index to the start of the password, taking into account arrays starting a 0
		pos1 += charIndex + 2;
		pos2 += charIndex + 2;

		if ((buffer[pos1] == c && buffer[pos2] != c) || (buffer[pos1] != c && buffer[pos2] == c)) numValidPasswords++;

	}

	printf("%d passwords are valid\n", numValidPasswords);
}