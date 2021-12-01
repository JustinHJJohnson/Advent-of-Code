#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/*
--- Part Two ---

The line is moving more quickly now, but you overhear airport security talking about how passports with invalid data are getting through. Better add some data validation, quick!

You can continue to ignore the cid field, but each other field has strict rules about what values are valid for automatic validation:

	byr (Birth Year) - four digits; at least 1920 and at most 2002.
	iyr (Issue Year) - four digits; at least 2010 and at most 2020.
	eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
	hgt (Height) - a number followed by either cm or in:
		If cm, the number must be at least 150 and at most 193.
		If in, the number must be at least 59 and at most 76.
	hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
	ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
	pid (Passport ID) - a nine-digit number, including leading zeroes.
	cid (Country ID) - ignored, missing or not.

Your job is to count the passports where all required fields are both present and valid according to the above rules. Here are some example values:

byr valid:   2002
byr invalid: 2003

hgt valid:   60in
hgt valid:   190cm
hgt invalid: 190in
hgt invalid: 190

hcl valid:   #123abc
hcl invalid: #123abz
hcl invalid: 123abc

ecl valid:   brn
ecl invalid: wat

pid valid:   000000001
pid invalid: 0123456789

Here are some invalid passports:

eyr:1972 cid:100
hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926

iyr:2019
hcl:#602927 eyr:1967 hgt:170cm
ecl:grn pid:012533040 byr:1946

hcl:dab227 iyr:2012
ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277

hgt:59cm ecl:zzz
eyr:2038 hcl:74454a iyr:2023
pid:3556412378 byr:2007

Here are some valid passports:

pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
hcl:#623a2f

eyr:2029 ecl:blu cid:129 byr:1989
iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

hcl:#888785
hgt:164cm byr:2001 iyr:2015 cid:88
pid:545766238 ecl:hzl
eyr:2022

iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719

Count the number of valid passports - those that have all required fields and valid values. Continue to treat cid as optional. In your batch file, how many passports are valid?

Your puzzle answer was 121.*/

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

#define BYR_MIN 1920
#define BYR_MAX 2002
#define IYR_MIN 2010
#define IYR_MAX 2020
#define EYR_MIN 2020
#define EYR_MAX 2030
#define HGT_MIN_CM 150
#define HGT_MAX_CM 193
#define HGT_MIN_IN 59
#define HGT_MAX_IN 76
#define NUM_EYE_COLOURS 7
#define LENGTH_EYE_COLOURS 4	

const char eyeColours[NUM_EYE_COLOURS][LENGTH_EYE_COLOURS] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

// Loop through the input counting the number of empty lines to get the number of passports in the input
int getNumPassports(char* input[], int inputLength)
{
	int inputIndex = 0;
	int numPass = 0;

	while (inputIndex < inputLength)
	{
		if (input[inputIndex][0] == 0)
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

static inline int getEndIndex(char* input)
{
	int index = 0;
	for (int i = 0; input[i] != '\n'; i++) index++;

	return index;
}

// Get the value out of a passport field
char* getFieldValue(char* input, int startIndex)
{
	int endIndex = 0;
	int strlength = 0;
	int inputIndex = startIndex;
	
	//for (int i = startIndex; i < strlen(input); i++)
	for (int i = startIndex; input[i] != '\n'; i++)
	{
		if (input[i] == ' ')
		{
			endIndex = i;
			break;
		}
	}

	//if (endIndex == 0) endIndex = strlen(input);
	if (endIndex == 0) endIndex = getEndIndex(input);

	strlength = endIndex - startIndex;

	char* fieldValue = (char*)malloc((strlength + 1) * sizeof(char));

	for (int i = 0; i < strlength; i++)
	{
		fieldValue[i] = input[inputIndex];
		inputIndex++;
	}

	fieldValue[strlength] = '\0';

	return fieldValue;
}

// Check that the hair colour is in the right format
bool checkHairColour(char* colour)
{
	bool valid = false;

	if (strlen(colour) == 7)
	{
		if (colour[0] == '#')
		{
			int validHex = 0;
			for (int i = 1; i < 7; i++)
			{
				if (colour[i] <= 57 && 48 <= colour[i] || colour[i] <= 102 && 97 <= colour[i])
				{
					validHex++;
				}
			}

			if (validHex == 6) valid = true;
		}
	}

	return valid;
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
	const char* filename = "..\\..\\inputs\\Day4.txt";					// Path to the input file
	const char** input = readInput(filename, 90, &inputLength, false);	// Store the input file and get the length of the input array
	int inputIndex = 0;													// Which index in the input array we are up to
	int numPassports = getNumPassports(input, inputLength);				// The total number of passports in the input array
	int passportIndex = 0;												// The index of the current passport

	// Setup and initialise an array of passports
	Passport* passports = (Passport*)malloc(numPassports * sizeof(Passport));
	initialisePassports(passports, numPassports);

	// loop over the input array
	while (inputIndex < inputLength)
	{
		// Keep moving through the array till an empty line is found, signalling the end of the current passport
		while (inputIndex < inputLength && input[inputIndex][0] != '\n')
		{
			// Loop through the passport details
			for (int i = 0; input[inputIndex][i] != '\n'; i++)
			{
				// Check for the : character to find a field
				if (input[inputIndex][i] == ':')
				{
					// Get which field was found
					char fieldName[] = { input[inputIndex][i - 3], input[inputIndex][i - 2], input[inputIndex][i - 1], '\0' };

					// Check with field was found and set the appropriate filed in passport struct
					if (strcmp(fieldName, "byr") == 0) 
					{
						int byr = atoi(getFieldValue(input[inputIndex], i + 1));	// Value in the birth year field, converted to an int

						if (BYR_MIN <= byr && byr <= BYR_MAX) passports[passportIndex].byr = true;
					}
					else if (strcmp(fieldName, "iyr") == 0) 
					{
						int iyr = atoi(getFieldValue(input[inputIndex], i + 1));	// Value in the issue year field, converted to an int

						if (IYR_MIN <= iyr && iyr <= IYR_MAX) passports[passportIndex].iyr = true;
					}
					else if (strcmp(fieldName, "eyr") == 0)
					{
						int eyr = atoi(getFieldValue(input[inputIndex], i + 1));	// Value in the expiry year field, converted to an int

						if (EYR_MIN <= eyr && eyr <= EYR_MAX) passports[passportIndex].eyr = true;
					}
					else if (strcmp(fieldName, "hgt") == 0)
					{
						char* hgt = getFieldValue(input[inputIndex], i + 1);					// Value in the height field
						char unit[] = { hgt[strlen(hgt) - 2], hgt[strlen(hgt) - 1], '\0' };		// Get the unit from the end of the string
						char* fieldName = (char*)malloc((strlen(hgt) + 1) * sizeof(char));		// A temporary version of hgt to store the value without the unit
						
						strcpy(fieldName, hgt);
						
						fieldName[strlen(hgt) - 2] = '\0';		// Cut the unit off the height string
						int hgtValue = atoi(fieldName);			// Convert height string to an int

						// Check which unit height was entered in and check against appropriate bounds
						if (strcmp(unit, "cm") == 0)
						{
							if (HGT_MIN_CM <= hgtValue && hgtValue <= HGT_MAX_CM) passports[passportIndex].hgt = true;
						}
						else if (strcmp(unit, "in") == 0)
						{
							if (HGT_MIN_IN <= hgtValue && hgtValue <= HGT_MAX_IN) passports[passportIndex].hgt = true;
						}
					}
					else if (strcmp(fieldName, "hcl") == 0)
					{
						char* hcl = getFieldValue(input[inputIndex], i + 1);	// Value in the hair colour field
						int temp = 0;											// Variable to fill out regex function

						// Validate hair colour value with regex
						if (checkHairColour(hcl)) passports[passportIndex].hcl = true;
					}
					else if (strcmp(fieldName, "ecl") == 0) 
					{
						char* ecl = getFieldValue(input[inputIndex], i + 1);	// Value in the eye colour field
						int temp = 0;											// Variable to fill out regex function

						// Loop over all eye colours and check if ecl stores a valid eye colour
						for (int j = 0; j < NUM_EYE_COLOURS; j++)
						{
							if (strcmp(ecl, eyeColours[j]) == 0)
							{
								passports[passportIndex].ecl = true;
								break;
							}
						}

						// if(passports[passportIndex].ecl == false) printf("\nInvalid eye colour %s on passport %d\n", ecl, passportIndex + 1);
					}
					else if (strcmp(fieldName, "pid") == 0)
					{
						char* pid = getFieldValue(input[inputIndex], i + 1);	// Value in the passport ID field

						// Validate passport ID length
						if (strlen(pid) == 9)
						{
							passports[passportIndex].pid = true;

							// Validate passport ID doesn't contain any illegal characters
							for (int j = 0; j < strlen(pid); j++)
							{
								if (!isdigit(pid[j])) 
								{
									passports[passportIndex].pid = false;
									break;
								}
							}
						}
					}
				}

			}

			inputIndex++;
		}

		passportIndex++;
		inputIndex++;
	}
	printf("\n");
	printf("%d passports are valid.\n", validatePassports(passports, numPassports));
}

pid:826827136 eyr:2030 ecl:brn byr:1946 hcl:#a97842 iyr:2018\n