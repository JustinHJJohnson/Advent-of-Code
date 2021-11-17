#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
--- Day 4: Passport Processing ---

You arrive at the airport only to realize that you grabbed your North Pole Credentials instead of your passport. While these documents are extremely similar, North Pole Credentials aren't issued by a country and therefore aren't actually valid documentation for travel in most of the world.

It seems like you're not the only one having problems, though; a very long line has formed for the automatic passport scanners, and the delay could upset your travel itinerary.

Due to some questionable network security, you realize you might be able to solve both of these problems at the same time.

The automatic passport scanners are slow because they're having trouble detecting which passports have all required fields. The expected fields are as follows:

	byr (Birth Year)
	iyr (Issue Year)
	eyr (Expiration Year)
	hgt (Height)
	hcl (Hair Color)
	ecl (Eye Color)
	pid (Passport ID)
	cid (Country ID)

Passport data is validated in batch files (your puzzle input). Each passport is represented as a sequence of key:value pairs separated by spaces or newlines. Passports are separated by blank lines.

Here is an example batch file containing four passports:

ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in

The first passport is valid - all eight fields are present. The second passport is invalid - it is missing hgt (the Height field).

The third passport is interesting; the only missing field is cid, so it looks like data from North Pole Credentials, not a passport at all! Surely, nobody would mind if you made the system temporarily ignore missing cid fields. Treat this "passport" as valid.

The fourth passport is missing two fields, cid and byr. Missing cid is fine, but missing any other field is not, so this passport is invalid.

According to the above rules, your improved system would report 2 valid passports.

Count the number of valid passports - those that have all required fields. Treat cid as optional. In your batch file, how many passports are valid?

Your puzzle answer was 190.*/

typedef struct Passport
{
	bool byr;
	bool iyr;
	bool eyr;
	bool hgt;
	bool hcl;
	bool ecl;
	bool pid;
	bool cid;
} Passport;

// Loop through the input counting the number of empty lines to get the number of passports in the input
int getNumPassports(const char** input, int inputLength)
{
	int inputIndex = 0;
	int numPass = 0;

	while (inputIndex < inputLength)
	{
		if (input[inputIndex][0] == '\n')
		{
			numPass++;
		}

		inputIndex++;
	}

	printf("%d lines in the array\n", inputLength);
	printf("%d passports\n\n", numPass + 1);
	return numPass + 1;
}

// Check if each passport has the right fields set (byr, iyr, eyr, hgt, hcl, ecl, pid) and return the number of valid passports
int validatePassports(Passport* passports, int numPassports) 
{
	int validPassports = 0;
	
	for (int i = 0; i < numPassports; i++)
	{
		if (passports[i].byr && passports[i].iyr && passports[i].eyr && passports[i].hgt && passports[i].hcl && passports[i].ecl && passports[i].pid) validPassports++;
	}

	return validPassports;
}

// Loop through all the passports, setting all their fields to false
void initialisePassports(Passport* passports, int numPassports)
{
	for (int i = 0; i < numPassports; i++)
	{
		passports[i].byr = false;
		passports[i].iyr = false;
		passports[i].eyr = false;
		passports[i].hgt = false;
		passports[i].hcl = false;
		passports[i].ecl = false;
		passports[i].pid = false;
		passports[i].cid = false;
	}
}

const char** readInput(const char* filename, int lineLength, int* numLines, bool debug)
{
	// Open File
	FILE* fp = fopen(filename, "r");

	if(!fp)
	{
		perror("getline");
  		exit;
	}
	if (debug) printf("Opened file: %s\n", filename); 

	// Count Lines
	char cr;
	int lines = 0;

	while(cr != EOF) 
	{
		if ( cr == '\n' ) lines++;
		cr = getc(fp);
	}
	if (debug) printf("Number of lines: %ld\n", lines); 
	rewind(fp);

	// Read data
	const char** data = (char**)malloc(lines * sizeof(char*));
	int n;

	for (int i = 0; i < lines; i++) 
	{
		data[i] = (char*)malloc(lineLength * sizeof(char));
		fgets(data[i], lineLength, fp);

		if (ferror(fp))
		{
			perror("fopen");
			exit;
		}	
	}

	if (debug)
	{
		for (int i = 0; i < lines; i++) printf("%s\n", data[i]);
	}
	
	// Close File
	fclose(fp);

	*numLines = lines;
	return data;
}

int main(int argc, char* argv[])
{
	int inputLength;													// The length of the input array
	const char* filename = "..\\..\\inputs\\Day4.txt";		// Path to the input file
	const char** input = readInput(filename, 90, &inputLength, false);	// Store the input file and get the length of the input array
	int inputIndex = 0;													// Which index in the input array we are up to
	int numPassports = getNumPassports(input, inputLength);				// The total number of passports in the input array 254
	int passportIndex = 0;												// The index of the current passport

	// Setup and initialise an array of passports
	Passport *passports = (Passport*)malloc(numPassports * sizeof(Passport));
	initialisePassports(passports, numPassports);

	// Loop over the input array
	while (inputIndex < inputLength)
	{
		// Keep moving through the array till an empty line is found, signalling the end of the current passport
		while (inputIndex < inputLength && input[inputIndex][0] != '\n')
		{
			// Loop through the passport details until the end of the line
			for (int i = 0; input[inputIndex][i] != '\n'; i++)
			{
				// Check for the : character to find a field
				if (input[inputIndex][i] == ':')
				{
					// Get which field was found
					char tempString[4] = { input[inputIndex][i - 3], input[inputIndex][i - 2], input[inputIndex][i - 1], '\0' };

					// Check with field was found and set the appropriate filed in passport struct
					if (!strcmp(tempString, "byr")) passports[passportIndex].byr = true;
					else if (!strcmp(tempString, "iyr")) passports[passportIndex].iyr = true;
					else if (!strcmp(tempString, "eyr")) passports[passportIndex].eyr = true;
					else if (!strcmp(tempString, "hgt")) passports[passportIndex].hgt = true;
					else if (!strcmp(tempString, "hcl")) passports[passportIndex].hcl = true;
					else if (!strcmp(tempString, "ecl")) passports[passportIndex].ecl = true;
					else if (!strcmp(tempString, "pid")) passports[passportIndex].pid = true;
					else if (!strcmp(tempString, "cid")) passports[passportIndex].cid = true;
				}

			}
			
			inputIndex++;
		}

		passportIndex++;
		inputIndex++;
	}

	printf("%d passports are valid.\n", validatePassports(passports, numPassports));
}