#include <stdio.h>
#include <stdlib.h>

/*
--- Day 2: Password Philosophy---

Your flight departs in a few days from the coastal airport; the easiest way down to the coast from here is via toboggan.

The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. "Something's wrong with our computers; we can't log in!" You ask if you can take a look.

Their password database seems to be a little corrupted : some of the passwords wouldn't have been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.

To try to debug the problem, they have created a list(your puzzle input) of passwords(according to the corrupted database) and the corporate policy when that password was set.

For example, suppose you have the following list :

1 - 3 a : abcde
1 - 3 b : cdefg
2 - 9 c : ccccccccc

Each line gives the password policy and then the password.The password policy indicates the lowest and highest number of times a given letter must appear for the password to be valid.For example, 1 - 3 a means that the password must contain a at least 1 time and at most 3 times.

In the above example, 2 passwords are valid.The middle password, cdefg, is not; it contains no instances of b, but needs at least 1. The first and third passwords are valid : they contain one a or nine c, both within the limits of their respective policies.

How many passwords are valid according to their policies?

Your puzzle answer was 483*/

int main(int argc, char* argv[])
{
	int minIndex = 0;				// The index of the minimum value in the password string
	int maxIndex = 2;				// The index of the maximum value in the password string
	int charIndex = 4;				// The index of the security character in the password string
	int numValidPasswords = 0;		// Total number of valid passwords

	const char* filename = "..\\..\\inputs\\Day2.txt";	// Path to the input file to read
	char buffer[50];									// Buffer to store the passwords from the file
	FILE* fp = fopen(filename, "r");					// Open the file and store the file

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
		int min = 0;				// The min number of occurences of the security character
		int max = 0;				// The max number of occurences of the security character
		char c;						// The security character
		int numValidateChar = 0;	// Number of occurences of the security charater in the current string

		minIndex = 0;
		maxIndex = 2;
		charIndex = 4;

		// Get the minimum value from the string
		min = buffer[minIndex] - '0';

		// Check if the minimum value is two digits and make corrections to other indexes
		if (buffer[minIndex + 1] != '-')
		{
			min = min * 10 + (buffer[minIndex + 1] - '0');
			maxIndex++;
			charIndex++;
		}

		// Get the maximum value from the string
		max = buffer[maxIndex] - '0';

		// Check if the maximum value is two digits and make correction to the security character index
		if (buffer[maxIndex + 1] != ' ')
		{
			max = max * 10 + (buffer[maxIndex + 1] - '0');
			charIndex++;
		}

		// Get the security character from the string
		c = buffer[charIndex];

		// Loop through the password and count number of occurences of the security character
		for (int j = charIndex + 3; buffer[j] != '\n'; j++)
		{
			if (buffer[j] == c) numValidateChar++;
		}

		if (min <= numValidateChar && numValidateChar <= max) numValidPasswords++;
	}
		
	printf("%d passwords are valid\n", numValidPasswords);
}