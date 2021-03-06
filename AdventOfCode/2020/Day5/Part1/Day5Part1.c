#include <stdio.h>
#include <stdbool.h>

/*
--- Day 5: Binary Boarding ---

You board your plane only to discover a new problem: you dropped your boarding pass! You aren't sure which seat is yours, and all of the flight attendants are busy with the flood of people that suddenly made it through passport control.

You write a quick program to use your phone's camera to scan all of the nearby boarding passes (your puzzle input); perhaps you can find your seat through process of elimination.

Instead of zones or groups, this airline uses binary space partitioning to seat people. A seat might be specified like FBFBBFFRLR, where F means "front", B means "back", L means "left", and R means "right".

The first 7 characters will either be F or B; these specify exactly one of the 128 rows on the plane (numbered 0 through 127). Each letter tells you which half of a region the given seat is in. Start with the whole list of rows; the first letter indicates whether the seat is in the front (0 through 63) or the back (64 through 127). The next letter indicates which half of that region the seat is in, and so on until you're left with exactly one row.

For example, consider just the first seven characters of FBFBBFFRLR:

	Start by considering the whole range, rows 0 through 127.
	F means to take the lower half, keeping rows 0 through 63.
	B means to take the upper half, keeping rows 32 through 63.
	F means to take the lower half, keeping rows 32 through 47.
	B means to take the upper half, keeping rows 40 through 47.
	B keeps rows 44 through 47.
	F keeps rows 44 through 45.
	The final F keeps the lower of the two, row 44.

The last three characters will be either L or R; these specify exactly one of the 8 columns of seats on the plane (numbered 0 through 7). The same process as above proceeds again, this time with only three steps. L means to keep the lower half, while R means to keep the upper half.

For example, consider just the last 3 characters of FBFBBFFRLR:

	Start by considering the whole range, columns 0 through 7.
	R means to take the upper half, keeping columns 4 through 7.
	L means to take the lower half, keeping columns 4 through 5.
	The final R keeps the upper of the two, column 5.

So, decoding FBFBBFFRLR reveals that it is the seat at row 44, column 5.

Every seat also has a unique seat ID: multiply the row by 8, then add the column. In this example, the seat has ID 44 * 8 + 5 = 357.

Here are some other boarding passes:

	BFFFBBFRRR: row 70, column 7, seat ID 567.
	FFFBBBFRRR: row 14, column 7, seat ID 119.
	BBFFBBFRLL: row 102, column 4, seat ID 820.

As a sanity check, look through your list of boarding passes. What is the highest seat ID on a boarding pass?

Your puzzle answer was 933.*/

int calculateSeatID(char* input)
{
	int seatID = 0;
	int j = 0;

	for (int i = strlen(input) - 1; 0 <= i; i--)
	{
		if (input[i] == 'B' || input[i] == 'R') seatID = seatID | (1 << j);
		j++;
	}

	return seatID;
}

int main(int argc, char* argv[])
{
	char* input[] =
	{
		"BBFBFFBRLL",
		"FBFBFFBRRR",
		"BBBFBFFLLR",
		"BFBBFFBRRL",
		"BBFFBBBRRL",
		"BFFFFFBLRR",
		"FBBBFBFLLL",
		"FBBFBFFLRR",
		"FBFFFFBRLR",
		"FBFBFBFLRL",
		"FFBBFFFLRR",
		"BFFBBBFRRL",
		"FFBBFBBRRR",
		"BFFBBFFRRR",
		"FBBFBBFRLR",
		"BFFFFBBLRL",
		"BFFBFFBRLL",
		"BFFFBFFRLL",
		"BBFFFBFRLL",
		"FFFFBFBLLR",
		"FBFBFFBLRR",
		"FBBFFFFRRL",
		"FBBFFFFLRL",
		"BBFBFFFLRR",
		"FFBFBBFLLR",
		"FFFFBFBRRL",
		"BFFFBBBLRR",
		"BBFBFBFRRL",
		"FFBFBFBRRL",
		"FFFBBBBRRL",
		"FBBBBBBLLR",
		"FFFFFBFRLR",
		"FBBFBBBRRL",
		"FBBBBFFRLR",
		"FFBBBFFRLR",
		"FFBBBFFLRR",
		"FFBBBBBRLR",
		"FFBFFFBRLR",
		"FBFBFFBLRL",
		"BFBBBBFRRR",
		"FBFFBFFRRL",
		"BFFFBFFLRL",
		"BBFBFBBRRR",
		"BFBFBFFLRR",
		"BFFFBBBRRR",
		"FBBFFBFLRR",
		"BFFBFBFLRL",
		"BFBBBFBRRL",
		"BFBFBFBRRR",
		"FFFBBFFRLR",
		"FFFFBBBLRR",
		"BFBFFBBRLL",
		"BBFFBBBLLR",
		"FBFFFBFLLL",
		"FFBFBBFRRL",
		"FFFBBFFLLR",
		"FBBFFFBRRL",
		"FBFFBBBLRL",
		"FFBBFBBLLL",
		"FBBBBBBRRR",
		"FBBBBFFLRR",
		"FBFFFFFLLL",
		"FBFBFBFLLL",
		"BBFFBFBLRL",
		"FBFBBFFRLR",
		"FFFBFFBRLL",
		"FFBFFBFRRL",
		"FBBFFFFLRR",
		"FBFFFFFRLR",
		"FFFBFBBLLR",
		"FBBBFFBRLL",
		"BBFFBBFLRR",
		"FBBFBBFLLL",
		"FFBFBBBLRR",
		"FFFFFFBLLL",
		"BFFFBBFLLR",
		"FFFFBBFLLL",
		"BFBFBFBLRL",
		"BFBBFFBRRR",
		"BFBBFBBRLR",
		"FFFBFFFLRL",
		"BBFBBBBLRL",
		"FFBFBBBRRR",
		"BFFFBFBRLL",
		"BBFFFBFRRR",
		"BFFFFFFRRL",
		"BFBBFFFRLR",
		"FFFFBFBLRL",
		"FBFBFFBLLR",
		"BBFFFBFRLR",
		"FFBBFFFRLL",
		"FBBBFBFRRR",
		"BFFBBFFLLR",
		"FFFFBFBRRR",
		"FBFFFBBRLL",
		"FBBFFFBRLR",
		"BFBFBBFLLL",
		"BFFBFFBRRR",
		"FFBBBFBRLL",
		"BFBFFBBLLL",
		"FFBFFBBLLL",
		"FFBBFBFRLL",
		"BFFFBBFLRL",
		"BBFBBFFLRL",
		"BFBBFFFRLL",
		"BBFFFFFRLR",
		"FFFBBFBLRR",
		"BBFFBBBRRR",
		"FBFFFBFRRL",
		"BFBFFBFRRR",
		"FBFBBFFLRR",
		"FBBFFBFLRL",
		"FBBBBFBLLL",
		"BFBFFBFLRR",
		"BFFBFBBRLR",
		"FFBBBFBRRR",
		"FBBBBBFLRL",
		"BFBBFFBRLL",
		"BFFBFBBRRL",
		"BBBFFBFRRR",
		"FBBFFBBRLL",
		"BFFFFBBLLL",
		"BFBBBFBRLL",
		"BFFFBBFRLR",
		"FFBFFFBLLR",
		"BFBBFFFRRL",
		"BFFBFBFRRR",
		"FBFFBFBRLR",
		"FBFFBBFLLR",
		"BFFFFFBRRR",
		"FFFFFBBRLR",
		"FBBFFFBLLL",
		"BFFFFFBRRL",
		"BBBFFFFLRR",
		"BFFFBBBRLL",
		"BFFFFFBRLR",
		"FFFBBBBLRL",
		"FBBFFBBLRL",
		"FBBBBFFLLR",
		"BFBFBFBRLL",
		"FBFBBFFLLR",
		"FFFFFBFLLL",
		"FBBBFFFRLL",
		"BFBBFFFLLR",
		"FBFBBFFRLL",
		"FBFBBFBLLL",
		"FBFBFFBRLL",
		"BBBFFFBRRL",
		"FFBBFBFLLR",
		"FFFFFFBRLL",
		"BFBFBFBRRL",
		"BFFBFFBLLL",
		"FBBFFFBRLL",
		"FFFFBBBLLR",
		"FFBFFFBLRL",
		"FBFBBBBRRR",
		"FFBFBBBRLL",
		"BFBFBFFRRR",
		"FBBFBFFRRR",
		"FBBFFFBLLR",
		"FBBBFFFLRR",
		"BBFFFFFRLL",
		"FBBBBBBRLR",
		"BFBFBBBRLL",
		"BBFFBBFRRL",
		"BBFFFFFLLR",
		"FFBFFFBRLL",
		"BBFBBFBLLL",
		"FFBFFBFLRR",
		"FBBBFFBRRR",
		"FBFBFBFRRL",
		"FBFBFBBRLL",
		"FFFFFFBRRL",
		"FBBFFBFRLR",
		"FBFFFBFRLL",
		"FFBBFFBRRL",
		"FBFFBBBLLL",
		"FFFBFBFLRL",
		"BBFFFFBRRR",
		"FFBFBFBLRL",
		"FBBBFFFLLR",
		"FBBBFFFRRR",
		"BFFFFBBRRL",
		"BFFBBBFLLR",
		"BBBFFBFRLR",
		"FBFBFBFLRR",
		"FFFFBFBLLL",
		"BFBBFFBLLL",
		"FFFFBBFRLL",
		"FFBBFFFRRR",
		"BBFBFBFLRL",
		"FFBBBBBRRR",
		"FBBBFBBLLR",
		"FBBBFBBRRL",
		"FBFBFBFLLR",
		"BFFFBFFLLR",
		"BBBFFBBLRL",
		"FFFFFBBLLL",
		"FBFBBBFLLR",
		"FBFBFBBRRR",
		"BFFFBBFRLL",
		"BFFBFFFLRL",
		"FFFFFBBLRR",
		"BFFBFFBLRL",
		"FBBFFBBRRR",
		"FFBFFBFLRL",
		"FBFFBBBLLR",
		"BBFBBFBRLR",
		"BFBBFFFLLL",
		"FBFBBBFRLL",
		"BFFFFBFLRL",
		"BBFBBFFRRR",
		"BBFBBBFRRR",
		"FFBFFFBRRL",
		"FFFFFFFRRR",
		"FBBFBBBRRR",
		"BBBFFBFLLR",
		"BFFBFFBRLR",
		"FFBFFFBLRR",
		"BBFFFBFLRR",
		"BBBFFFBLRL",
		"FFBBFBFLLL",
		"BBFBFFBRLR",
		"BFBFFBFLRL",
		"FBFFFBBLLL",
		"FBBBBBFLLR",
		"BFBFFFBLRL",
		"FFFBBBBLLL",
		"FBBFBBFRRL",
		"FBBFFBFLLL",
		"FFBBBFFRRL",
		"BFFFBBFRRR",
		"FFBFBBFRLL",
		"FFFBFFFRLL",
		"FBBFFFBLRR",
		"BBFFBBBLLL",
		"FBFFBFFRLR",
		"BBFBFFFRLR",
		"FBFBBFFLLL",
		"BBFFFBBRLL",
		"BBBFFBBLLL",
		"BFBFFFFRLR",
		"FBFBBFBLLR",
		"FBFFFBFLLR",
		"FFBBFBFLRR",
		"BFFBFFFLLR",
		"BBBFFFBRLR",
		"BFBBBBBRRR",
		"FFFBFFFRRL",
		"FFBBBBBRRL",
		"BBFBFBFLLR",
		"BBFFFFFRRR",
		"FBFFBBFRRL",
		"FBFFBFBLRR",
		"BFBFFFBRRL",
		"FFFBFBFLRR",
		"FFBBFFBRLR",
		"BFFBFBFLRR",
		"FBBBBBFLLL",
		"BFBFFFBRRR",
		"BBFBFBBRLR",
		"BFFBFBBLLL",
		"FBBFFFFRLR",
		"BFBFBFFRRL",
		"FFFFBBBRLR",
		"FFFBBFFRLL",
		"FBFFBBBRLL",
		"FFBBBBBRLL",
		"BFFFFBFRRR",
		"FBBFBBFLRR",
		"FFBFBFBRLR",
		"FBFBFFBRRL",
		"FFFFBFFLRR",
		"BFBFBFFRLR",
		"FFFFFFBRRR",
		"BFBBBBFRLR",
		"FFBFBBBLLR",
		"FBBBFFBLRR",
		"FFBFBFFLRL",
		"BBBFFFBLLL",
		"FFBFFFBLLL",
		"BFBFFFBRLR",
		"BFFFBFFLRR",
		"FFBFBFFRRL",
		"FFFFFBBRRR",
		"FFBBFFFLLR",
		"FBFFBFFRLL",
		"FBFFBBFRLL",
		"FFFFBBFLRL",
		"FFFBFFFLLL",
		"BFFBFBBRLL",
		"FBFFFFFLLR",
		"FFFFFBBRRL",
		"FBFBFFFRRL",
		"FBFBFBBRLR",
		"FFBBFFBLRR",
		"BBFFBFBLLR",
		"BFFBFBFLLL",
		"FBFBFFFLRL",
		"FFFFBBFRRR",
		"FFBFFFFRLL",
		"FBFBBFBRRL",
		"FBFBBFBRLR",
		"BBFFFFBLRL",
		"BFFFFBFRLL",
		"FFBFBBFRLR",
		"FFBFFBBLRR",
		"BFFFFFFRRR",
		"FBBBFBFLRL",
		"FBFFBFBRRR",
		"FBFFBFFRRR",
		"BFBFBFBLLR",
		"FBBBBBBRRL",
		"BFBFBFBLRR",
		"BBFFBFBLLL",
		"BFFBBBBLRL",
		"BFFBBBBLLR",
		"FFBFFBBRLL",
		"BBBFFBBRLR",
		"BBBFFFFLLL",
		"BFBBFBFLRL",
		"BBFBFFBLLR",
		"FFFBBFBRRL",
		"BFBBFBBLRL",
		"FFFFBFFRLL",
		"FFBBBFFLLR",
		"FFBBBFBRRL",
		"FFBFFFFRRL",
		"FBBFFFBLRL",
		"BBFFFBBLRR",
		"FFBBBBBLLR",
		"BBFBBBBRLL",
		"BFFFBFFRRR",
		"FFFFBBBRLL",
		"FFBFFBBLLR",
		"BFBBFBFRRL",
		"FFBFBBFLRL",
		"FBFFFFBRRL",
		"BFFFFFBLRL",
		"FFFBBFBLLL",
		"FBFFFFBLRL",
		"BFBBFFFLRR",
		"FBBBFBBLRR",
		"BFBBBBBLLR",
		"FFBFFBFRLR",
		"FFBFBBBLRL",
		"FBFFFBFRLR",
		"FFBBFFBLLR",
		"BBFFBBFRLR",
		"BBFFFBBRRR",
		"BBFFBBFRLL",
		"FFBBFFBLLL",
		"FBBBBFBLRL",
		"FFFFBBBLRL",
		"BBFBBBBRRR",
		"FFBFBFBLLL",
		"BFFFFBBLLR",
		"BFFBFFFRLR",
		"BFBFBFFLRL",
		"FFFBBBBRLR",
		"FFBBBBBLRL",
		"BFBBBBBLRL",
		"BBFFFFFLRR",
		"FBBBFFFLRL",
		"FBFBFFBRLR",
		"BFFBFFFLRR",
		"FFFFFBFLLR",
		"BFBBBBFLRR",
		"BFBBBFBLLL",
		"BBFBBFBRRL",
		"BBFFBFFLRL",
		"BFBBBBBRLL",
		"FBBFBBBRLR",
		"BBFFBBBLRR",
		"FFFBBFBLLR",
		"BFFFBBBLRL",
		"FFFBFBBRLL",
		"BBFBBFFRLR",
		"BFBFFBBRRR",
		"FFFBFBFRRL",
		"FFFBFFFLLR",
		"BBBFBFFRLR",
		"FFFBFFFRLR",
		"FBBFBFBRRR",
		"FFBBBBFRRR",
		"FBBBFBFLLR",
		"BBBFBFFLRL",
		"FFBBFFFRLR",
		"FFFBFFFRRR",
		"FFBFFFFLLR",
		"BFFBBFBLRR",
		"FBFFBFBLRL",
		"BBFBFBFRRR",
		"BBBFFFFLLR",
		"FBFFBFFLRR",
		"BFFFFFFLLL",
		"FBFBBFBRLL",
		"FFBFBFFRLL",
		"FBFFBFBLLL",
		"FFBBBBBLLL",
		"FFFFBFFLLL",
		"FBBBBFBRLR",
		"FFBBBBFLLL",
		"FFBBBFFRLL",
		"FFFBFBFLLL",
		"BFBBBBBLLL",
		"FBBFFFFRRR",
		"BFFBBFBRLR",
		"FBFFFBBLRL",
		"FBBFBFBLRR",
		"BBFFFFBLLR",
		"FFBBBBFLRR",
		"FFBFBBFLRR",
		"BBFBBFBRRR",
		"FBFBFBFRLL",
		"BFBFBBBLLL",
		"BFBBBFBRLR",
		"FFFBFBFRLR",
		"BFBBBFFRRR",
		"FFFFBBBLLL",
		"BFBFBBBRRR",
		"FBBBBFFRRL",
		"BBFBFFFLLL",
		"FBBBFBFRLR",
		"BFBBBFFLLR",
		"FBFFFFFLRL",
		"BFBFFBFLLL",
		"BFFFFBFLLL",
		"BFBBFFBLLR",
		"FBBFBBBRLL",
		"FFFBBBFLRR",
		"FBBBBFFLLL",
		"FFBBBBFLLR",
		"BFBFBFBLLL",
		"BFBFBBFRLR",
		"FBBFBBFRLL",
		"FBFFFBFLRR",
		"BFFBBFFRRL",
		"FFFBBFBLRL",
		"FBFFFFFRLL",
		"BFFFFBFRRL",
		"FFFBBBBRLL",
		"BFFBFFBRRL",
		"FBBFFFFLLL",
		"FFBBFBBLRR",
		"BFBFFFBLLL",
		"BFBFFFFLLR",
		"BBFBFFBRRR",
		"BBFBBFFRLL",
		"FFFBBBFLLR",
		"BFFBBBBRRR",
		"FBBBBBBLRR",
		"FFBFFBBLRL",
		"FBBFFBBRLR",
		"BFFFBFFRLR",
		"FBBBFFBLLL",
		"FFFBFBFRLL",
		"BFFBFFFRRL",
		"BFFFBFBRRR",
		"BFBFFFFLRR",
		"FFFBFBBLRR",
		"BBFBBBFLLL",
		"FBBFBFFRLR",
		"BBFFBBFLLL",
		"FBFFBBFRRR",
		"BFFFBFBLRL",
		"BFFFFBFLRR",
		"BFFFFBFRLR",
		"BBFFBBBRLR",
		"FBBFBFBRLL",
		"FBFBBFFRRL",
		"BBFFBFBLRR",
		"FBBFFBBLRR",
		"BBFFBFBRRL",
		"FFBBBBFLRL",
		"FFFBFBFLLR",
		"BBBFFFFRLR",
		"BFBFFBBRLR",
		"BFFBBFFRLR",
		"BFFFFFFLRR",
		"BBFFFFBLRR",
		"FFFFBFFLRL",
		"FBBBBBFLRR",
		"BFBFFFFRRR",
		"FBBBFBFLRR",
		"BFBFBBFRLL",
		"FBBFBBFLLR",
		"FBFFFFFRRR",
		"FBBFFBFRLL",
		"FBFBFFFRLR",
		"FFBBBFBLLR",
		"FBBBBFFLRL",
		"BBFFFFBRLL",
		"FBBBBBFRRL",
		"FBBBBFFRLL",
		"BBFFBFBRLR",
		"FBFBFBBRRL",
		"FBBFBFBLLL",
		"FBFFBFBLLR",
		"BFBBBFFLLL",
		"FFBFFBBRRL",
		"BBFBFBBLLL",
		"FBBBFFFLLL",
		"FBFBBBBLLL",
		"FBFFBFFLLL",
		"FFFBBFFLRL",
		"BBFFBBBLRL",
		"BFFFBFBRLR",
		"BBFFFFBRLR",
		"BBFBBBBLLR",
		"BFFBBFBLLR",
		"FFFBBFBRLL",
		"BBFFFBFRRL",
		"FFBFFFBRRR",
		"BBFBFBBRLL",
		"FBFBFBBLLR",
		"FBBFFBFRRR",
		"FBBBFFBLLR",
		"BFFFBBBRRL",
		"BFFBBFBLRL",
		"FBFFBBFLLL",
		"BFBFBFFRLL",
		"BFBBBFBLLR",
		"FBFFBFFLLR",
		"FBBFBFFLLR",
		"BFBFFFBLRR",
		"FBBFFBBLLL",
		"FFBFBFFLLL",
		"FFBBFFBRLL",
		"FFBFFBFRRR",
		"FBFBFFFRLL",
		"BBFBBFFLLL",
		"FBFBBBBRLR",
		"FFFBBBFRLL",
		"FFBFFBFLLR",
		"BFFFFBBRLR",
		"FFBFBBBRRL",
		"FFFFBFFRLR",
		"FFBBFFFLLL",
		"FBFFFFBLRR",
		"FBBBBFBRLL",
		"FBFFBBBLRR",
		"FFFBBFBRRR",
		"BFBBFBFRRR",
		"BFFFBFBLRR",
		"BFBFFBFRRL",
		"FFFBBBBRRR",
		"FBBFBFFRRL",
		"BFBBFFBLRR",
		"FBBFBBBLRR",
		"BFBBFBBRRR",
		"FFFFFBFLRR",
		"FBFBBBFLRR",
		"BBBFFFFRRL",
		"BBFFFBFLLL",
		"BBBFFFFLRL",
		"FFBBBBBLRR",
		"BBBFFBFLLL",
		"FBFBFBBLRR",
		"FFFBFFBLRR",
		"FFBBBFBLLL",
		"BBFFFBFLLR",
		"FFFFBBFRRL",
		"FBFBBFBLRL",
		"BBFBBFFLRR",
		"BFBFBFBRLR",
		"FFBFFBFRLL",
		"BFBBBFFRRL",
		"FFBBFBBLRL",
		"FBFFFFFRRL",
		"FBFFFFBLLR",
		"FFBFBFFRLR",
		"BFBBFBFRLL",
		"FBFBBBFRRR",
		"FBFBBBBLRL",
		"FFFBFFBRRL",
		"BFFFBFBLLR",
		"BFBFBBFLRL",
		"BBFBFBBLLR",
		"BBFFFFFLRL",
		"FFFBBFFLRR",
		"BFFBFBBLRR",
		"BBFFBBBRLL",
		"BFBBFBBRLL",
		"BFFBBBFRRR",
		"FBFBFFFRRR",
		"FBFBFFFLLR",
		"FFFBBBFLRL",
		"BBFBBFFRRL",
		"BFFFFFFRLR",
		"FFBBBFBRLR",
		"FFFFBBBRRR",
		"FFFBFBBRLR",
		"FBFBFFBLLL",
		"BBFBFFBLRR",
		"FBFFFFFLRR",
		"FFFBFBBLRL",
		"FBBBBFBLLR",
		"FBBBFBBLLL",
		"FFBBBBFRLL",
		"FBFFFBFRRR",
		"FFFBFFFLRR",
		"BFFBFFBLLR",
		"BBFBBBFRLR",
		"BFBFFBBLRR",
		"FFFBBFBRLR",
		"BFBBFBFRLR",
		"FBFFFBBLLR",
		"FBFBFFFLRR",
		"BFFFFBBRRR",
		"BBFFFFBLLL",
		"BFFBFFBLRR",
		"BFBFFBFLLR",
		"FBFBFBBLRL",
		"BFFBBBFRLL",
		"FFFFBFBRLL",
		"FFBFFFFLRR",
		"FBBFBBFRRR",
		"BFFFBFBRRL",
		"BFFFFBBLRR",
		"FFFFFBBRLL",
		"FBFFBBBRRR",
		"FFFBBFFLLL",
		"FFBFBFBRLL",
		"BFFBFBBRRR",
		"FFFFBBFLRR",
		"FBBFBBFLRL",
		"BBFFBBFLRL",
		"FBBBFBFRRL",
		"FFFBFBBLLL",
		"FFFBFFBRLR",
		"FFFFFBFLRL",
		"BFFFFFBLLL",
		"BFFBBFFLLL",
		"FBBFBFBRLR",
		"FBFBFBFRLR",
		"FBBBBFBRRR",
		"BFFFFFFLRL",
		"BFBFBBBRLR",
		"FBFBBBBRRL",
		"BFBBBFFLRR",
		"BFBFFFFRLL",
		"BBFFFBBLRL",
		"BBFFFFBRRL",
		"BBFBFBBRRL",
		"BFFBBBFLRR",
		"BBBFFFBLLR",
		"BBFFBFBRLL",
		"FBBFFBFRRL",
		"BFFFFFFLLR",
		"FFFFFBBLLR",
		"FBFBBFFLRL",
		"BBFBFBFLLL",
		"BBFBBBBLRR",
		"FFBFFFFLLL",
		"FBFFFBBRRR",
		"BBFBFBBLRL",
		"BFBBBBBRLR",
		"FBBFBBBLRL",
		"BBFBBBFRRL",
		"BBFBFFFLRL",
		"FFBFFFFRLR",
		"FFFFBFFLLR",
		"FBFBBBBLLR",
		"BFBBFBFLLR",
		"FBFFBBFRLR",
		"BFFFBFBLLL",
		"FBFBBBBLRR",
		"BBFBFFFRRL",
		"FBFBBBFLRL",
		"BFFBBFBLLL",
		"BFFBBBBRLR",
		"FBBBFBBLRL",
		"BFBBBFFRLL",
		"BFBBBFBLRR",
		"BFBFBBFRRL",
		"BFBBFBFLRR",
		"FBFFBBFLRR",
		"BBBFFBFRLL",
		"BBFBBFBLRL",
		"BBFBFFFLLR",
		"FBBBBBFRLL",
		"FBFBFFFLLL",
		"FFBFBFBLRR",
		"FBBBFFFRRL",
		"FFFFBBFRLR",
		"FFBFBBBLLL",
		"FBBFBFFLLL",
		"BBBFFFBRLL",
		"BFBFBBBLLR",
		"BBFBBFBLLR",
		"FFFFBFFRRL",
		"FBFBBBFRLR",
		"BFFBBFBRRR",
		"BFBFBFFLLL",
		"BFBBBFBRRR",
		"FBFFBBBRLR",
		"BFBBFFBRLR",
		"BBFBBFFLLR",
		"FFBBFBFRRR",
		"BBFFFFFRRL",
		"FBBFBBBLLR",
		"BBBFFFFRLL",
		"FBFFBFBRRL",
		"BFFFFFFRLL",
		"FBBBBBFRLR",
		"FBBBBBBLLL",
		"BFFFFFBLLR",
		"BBBFFBFLRR",
		"BFFFFBBRLL",
		"BFBBFFFLRL",
		"BBFBBBBRLR",
		"FBFFBBBRRL",
		"BBFFBFFLLR",
		"BFFFBBBRLR",
		"BFBBFBBLRR",
		"BBBFBFFRLL",
		"FBFFFFBRRR",
		"BFBBBFFLRL",
		"FBBFFFFRLL",
		"FFBBFBBLLR",
		"BFFBFFFRRR",
		"BFBFFBBLRL",
		"FBFBBBFLLL",
		"FBBFFBBLLR",
		"FBBBFBBRLL",
		"FBFFFFBRLL",
		"FBFBBFBRRR",
		"FFBFFBBRRR",
		"FBBBFFBRRL",
		"FFBFBBFLLL",
		"FFBFBFBRRR",
		"FFBBFBFRLR",
		"FFBBBBFRRL",
		"FBBFFBFLLR",
		"FBBFBFBLRL",
		"FFBBBFFRRR",
		"FFBFBFFLLR",
		"BBFFBFBRRR",
		"BFFBBBBRRL",
		"FFFFFBFRRL",
		"FBFFBFFLRL",
		"FBBBFBFRLL",
		"FFBBBFBLRR",
		"FFFBFFBLLR",
		"BFFBFBFRLL",
		"FFFBFBBRRL",
		"BFFBFFFRLL",
		"FBBBFFBRLR",
		"FFFBFBBRRR",
		"BBFBFFFRLL",
		"BBFFBFFLRR",
		"BFFBFBFRRL",
		"FFFBFFBLRL",
		"BBBFFBFLRL",
		"BFFBFBBLLR",
		"FFBFBFBLLR",
		"FFFBFBFRRR",
		"FFBBFFBLRL",
		"BBFFBBFLLR",
		"FFBBFBBRLL",
		"FFBBBBFRLR",
		"FFFFBFBLRR",
		"FFBFBFFLRR",
		"BFBBBBBLRR",
		"FBBFBFFLRL",
		"FFFFFFBLRR",
		"BFBBBBFLRL",
		"BBBFFBBLLR",
		"BFFFBBFRRL",
		"FFFFBBBRRL",
		"FBFFFBFLRL",
		"BBFBBBBLLL",
		"BFBBBFFRLR",
		"BFFBBBBLLL",
		"BFFFFFBRLL",
		"BBFBBBBRRL",
		"BFBFBBBLRR",
		"FBFBBBFRRL",
		"BFBFFFBRLL",
		"BFFBBFBRRL",
		"FBBBBFBLRR",
		"BFBBFFBLRL",
		"FFFFFFFRRL",
		"BFBFBBBRRL",
		"BFBBFBBRRL",
		"FFBFBFFRRR",
		"FFBBFFBRRR",
		"FFFBBBBLLR",
		"FBBFBFBLLR",
		"BBFFFBBLLR",
		"FFFBBBFLLL",
		"FFFBBFFRRL",
		"FFFBBFFRRR",
		"FFBBFFFLRL",
		"FBFBBFBLRR",
		"BFFBBFBRLL",
		"FFBBFBFLRL",
		"FFFBBBFRLR",
		"BBFBBFBRLL",
		"FBFBBFFRRR",
		"BFFBBFFLRL",
		"BBFFBFFRRR",
		"BBFBBBFLRR",
		"FFFBBBFRRL",
		"BBFFBFFRRL",
		"FFBFBBFRRR",
		"BBFFFBBRLR",
		"FFFFBBFLLR",
		"FFFFFFBLRL",
		"BBFBFFFRRR",
		"BFBFFFBLLR",
		"FBFFFFBLLL",
		"FBBBBFFRRR",
		"BFFFBBFLRR",
		"FFBBFBBRLR",
		"BFFFBFFRRL",
		"BBFBFFBLLL",
		"FBBFBFFRLL",
		"BFBFFBBRRL",
		"BFFBBBFLLL",
		"FBFBFBFRRR",
		"BBFFBFFLLL",
		"BFBFBBFLLR",
		"BBFBFBFLRR",
		"BFBBFBBLLR",
		"FBBBFBBRLR",
		"BFFFBBBLLL",
		"BFBBBFBLRL",
		"BBBFFBFRRL",
		"FFFFFFBLLR",
		"BFFFBBBLLR",
		"BFBBBBFLLL",
		"BBFBFBBLRR",
		"FBBFBBBLLL",
		"BBFFBFFRLR",
		"FFFBBBBLRR",
		"BBBFFFFRRR",
		"BFBBBBFRRL",
		"BBBFBFFLRR",
		"BFBBBBFLLR",
		"BFFBBBFLRL",
		"BBFBBBFRLL",
		"FFFFFBFRRR",
		"BBBFBFFLLL",
		"BFFFBBFLLL",
		"BFFBFFFLLL",
		"FFBFFBFLLL",
		"BBFBFBFRLR",
		"FFBBFBFRRL",
		"BBFBFFBLRL",
		"FBBFFBBRRL",
		"BFFBFBFLLR",
		"BFBFBFFLLR",
		"BBBFFBBLRR",
		"FBBBBBBLRL",
		"FFBBBFBLRL",
		"FFBFFBBRLR",
		"BBBFFBBRRL",
		"BFBBFBBLLL",
		"FBFFBFBRLL",
		"BFBBFBFLLL",
		"BFFFBFFLLL",
		"FBFFFBBRLR",
		"BBBFFFBLRR",
		"BBFFBBFRRR",
		"BFFBBFFLRR",
		"BFBFFFFRRL",
		"FFFFFBFRLL",
		"FBFBBBBRLL",
		"FBFBFBBLLL",
		"FFFFBFFRRR",
		"FFBFFFFRRR",
		"FBFFFBBLRR",
		"FFFFBFBRLR",
		"BFBFBBBLRL",
		"FBBFFFFLLR",
		"BFFBFBBLRL",
		"FBBFBFBRRL",
		"BBFFBFFRLL",
		"BBFFFBFLRL",
		"FFFBBBFRRR",
		"BBBFFBBRRR",
		"BFFBBBBRLL",
		"BBFFFBBRRL",
		"BFBFFBBLLR",
		"FFBBBFFLLL",
		"BFBBBBFRLL",
		"FFBBFFFRRL",
		"FBBBFFBLRL",
		"BFFBFBFRLR",
		"BBFBFFBRRL",
		"FBBBBBBRLL",
		"FBBBBBFRRR",
		"BFFBBFFRLL",
		"BBFFFFFLLL",
		"BBBFFBBRLL",
		"FFFBFFBLLL",
		"FFFBFFBRRR",
		"FFBFBBBRLR",
		"FFFFFFBRLR",
		"FBFFFBBRRL",
		"BFFFFBFLLR",
		"BFBFBBFRRR",
		"FBBBFBBRRR",
		"BFBFFFFLLL",
		"BBFBBFBLRR",
		"BFBFBBFLRR",
		"FFFFFBBLRL",
		"FBBFFFBRRR",
		"FFBBFBBRRL",
		"BFFBBBBLRR",
		"BBFBBBFLRL",
		"FBFFBBFLRL",
		"BBBFFFBRRR",
		"BBFBFBFRLL",
		"BFBFFBFRLR",
		"BFBFFFFLRL",
		"BBFBBBFLLR",
		"BFFBBBFRLR",
		"BFBBBBBRRL",
		"BFBFFBFRLL",
		"BBFFFBBLLL",
		"FBBBBFBRRL",
		"FFBFFFFLRL",
		"FFBBBFFLRL",
		"FBBBFFFRLR"
	};

	int inputLength = sizeof(input) / sizeof(char*);		// The length of the input array
	int highestSeatID = 0;									// The highest seat ID

	// Loop through every boarding pass and calculate the seat ID
	for (int i = 0; i < inputLength; i++)
	{
		int temp = calculateSeatID(input[i]);
		if (highestSeatID < temp) highestSeatID = temp;
	}

	printf("Highest seat ID is %d", highestSeatID);
}