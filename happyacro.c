#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void sortWordsIntoFile(char prefix, char * wordFile, int printFrequency);

void generateAcronyms(char * acronym, int wordIndex, char * buffer,
    int printFrequency, int * countSoFar, clock_t startTime);

void main(int argc, char *argv[]) {
    
    //since we're dealing with C89, vars have to be declared before we do
    // anything in a function, sigh.
    char * acronym;
    int printFrequency;
    char * wordFile;
    int i;
    char acronymBuffer[1024];
    int countSoFar = 0;
    clock_t startTime;

    if (argc != 4) {
        printf("Usage: happyacro [acronym] [print frequency] [word file]");
        exit(1);
    }

    acronym = argv[1];
    printFrequency = atoi(argv[2]);
    wordFile = argv[3];

    printf("acronym: %s\n", acronym);
    printf("print frequency: %d\n", printFrequency);
    printf("word file: %s\n", wordFile);
    printf("ticks per second: %d\n", CLOCKS_PER_SEC);

    for (i = 0; i < strlen(acronym); i++) {
        sortWordsIntoFile(acronym[i], wordFile, printFrequency);      
    }

    printf("Generating acronyms!\n");

    startTime = clock();    
    generateAcronyms(acronym, 0, &acronymBuffer, printFrequency, &countSoFar, startTime);
}

void sortWordsIntoFile(char prefix, char * wordFile, int printFrequency) {
    FILE * inputFile;
    char * outputFileName = "a.txt";
    FILE * outputFile;
    char line[1024];
    char * readResult;
    int writeResult = 5;
    int count = 0;
    int maxWordLength = 0;
    int oldLength = 0;
    char longestWord[1024];

    outputFileName[0] = prefix;
    prefix = tolower(prefix);

    printf("Sorting words that start with '%c' to file: %s\n", prefix, outputFileName);
    printf("Reading words from file: %s\n", wordFile);

    if ((outputFile = fopen(outputFileName, "r")) != NULL) {
        printf("Word file %s already exists, skipping.\n", outputFileName);
        fclose(outputFile);
        return;
    }

    if ((inputFile = fopen(wordFile, "r")) == NULL) {
        printf("Cannot open file: %s\n", wordFile);
        exit(1);
    }

    if ((outputFile = fopen(outputFileName, "w")) == NULL) {
        printf("Cannot open output file: %s\n", outputFileName);
        exit(1);
    }

    while (!feof(inputFile)) {
        readResult = fgets(line, 1024, inputFile);
        if (readResult == NULL && !feof(inputFile)) {
            printf("Received error while trying to read file :/\n");
            exit(1);
        }

        if (!feof(inputFile) && tolower(readResult[0]) == prefix) {            
            writeResult = fputs(readResult, outputFile);
            if (writeResult == EOF) {
                printf("Received error while writing to output file :/\n");
                exit(1);
            }
            maxWordLength = max(maxWordLength, strlen(line));
            if (oldLength != maxWordLength) {
                strcpy(longestWord, line);
            }
            oldLength = maxWordLength;
            count++;
        }

        if (count % printFrequency == 0 && count > 0) {
            printf("Read word #%d: %s\n", count, line);
        }   
    }
    printf("Closing input file: %s\n", wordFile);
    fclose(inputFile);
    printf("Closing output file: %s\n", outputFileName);
    fclose(outputFile);

    printf("Found %d words that start with '%c'.\n", count, prefix);
    printf("Max word length for a word that starts with '%c': %d\n", prefix, maxWordLength);
    printf("Longest word that starts with '%c': %s\n", prefix, longestWord);
}

void generateAcronyms(char * acronym, int wordIndex, char * buffer,
    int printFrequency, int * countSoFar, clock_t startTime) {

    char acronymCharacter = acronym[wordIndex];
    char * inputFileName = "a.txt";
    FILE * inputFile;
    char line[1024];
    char * readResult;
    //fun fact: bool type doesn't exist until C99 - in other words, 1999.
    int lastLetter = wordIndex == (strlen(acronym) - 1);
    char myBuffer[1024];
    char * pos;
    clock_t timeElapsed;
    float secondsElapsed = 0;
    int debug = 0;
    float generatedPerSecond = 0;

    inputFileName[0] = acronymCharacter;

    if (debug == 1) {
        printf("Opening input file: %s\n", inputFileName);
    }

    if ((inputFile = fopen(inputFileName, "r")) == NULL) {
        printf("Cannot open file: %s\n", inputFileName);
        exit(1);
    }

    while (!feof(inputFile)) {
        readResult = fgets(line, 1024, inputFile);
        if (readResult == NULL && !feof(inputFile)) {
            printf("Received error while trying to read file:%s\n", inputFileName);
            exit(1);
        }

        //remove "\n" at end of string
        if ((pos = strchr(line, '\n')) != NULL) {
            *pos = '\0';
        }
        
        if (wordIndex == 0) {
            strcpy(myBuffer, line);
        } else {
            strcpy(myBuffer, buffer);
            strcat(myBuffer, line);
        }
        strcat(myBuffer, " ");
        
        if (lastLetter == 1) {
            *countSoFar += 1;
            if (*countSoFar % printFrequency == 0 && *countSoFar > 0) {                              
                timeElapsed = clock() - startTime;
                if (((float) timeElapsed) > 0) {
                    secondsElapsed = ((float)timeElapsed) / CLOCKS_PER_SEC;
                }
                if (secondsElapsed > 0) {
                    generatedPerSecond = ((float)*countSoFar) / secondsElapsed;
                }
                printf("Generated %d acronyms, time elapsed: %f sec, per sec: %f\n",
                    *countSoFar, secondsElapsed, generatedPerSecond);
                printf("Latest acronym: %s\n", myBuffer);
            }
        } else {
            generateAcronyms(acronym, wordIndex + 1, myBuffer, printFrequency,
                countSoFar, startTime);
        }        
    }
    if (debug == 1) {
        printf("Closing input file: %s\n", inputFileName);
    }
    fclose(inputFile);    
}
