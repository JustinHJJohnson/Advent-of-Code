import os

file = "Day13Part2"

inputFile = open("input.txt", "r")
if not os.path.isdir(f"AdventOfCode/{file}"):
    os.mkdir(f"AdventOfCode/{file}")
outputFile = open(f"AdventOfCode/{file}/{file}.c", "w")

outputFile.write('#include <stdio.h>\n#include <stdbool.h>\n\n')
outputFile.write('int main(int argc, char* argv[])\n{\n')
#outputFile.write('\tchar* input[] =\n    {\n')
outputFile.write('\tchar input[] =\n    {\n')
for line in inputFile:
    outputFile.write('\t\t\"' + line.strip('\n') + '\",\n')
    #outputFile.write('\t\t\"' + line.strip('\n')[:-1] + '\",\n')
    #outputFile.write('\t\t' + line.strip('\n') + ',\n')
outputFile.write("\t};\n};")

outputFile.close()
inputFile.close()