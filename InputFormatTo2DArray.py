inputFile = open("Day 2 Input.txt", "r+")
for line in inputFile:
    #inputFile.write('\"' + line.strip('\n') + '\",')
    print('\"' + line.strip('\n') + '\",')
inputFile.close()