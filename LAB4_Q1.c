#include <stdio.h>  //imports standard i/o operations
#include <stdlib.h> //imports standard library

//function to process input file and extract valid floats
void processFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r"); //open input file for reading
    if (!inputFile) { //check if input file opened successfully
        perror("Error opening input file");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w"); //open output file for writing
    if (!outputFile) { //check if output file opened successfully
        perror("Error opening output file");
        fclose(inputFile); //close input file if output file fails
        return;
    }

    char word[32];          //buffer for each token from file
    int invalidValueCount = 0; //counter for invalid floats

    //read and process tokens from input file
    while (fscanf(inputFile, "%31s", word) == 1) { //read a token - max 31 chars
        char *conversionCheck; //pointer to validate float conversion
        float floatValue = strtof(word, &conversionCheck); //attempt to convert to float

        if (*conversionCheck == '\0') { //check if token is a valid float
            fprintf(outputFile, "%.6f\n", floatValue); //write valid float to output file
        } else {
            invalidValueCount++; //increment count for invalid floats
        }
    }

    if (ferror(inputFile)) { //check for reading errors
        perror("Error reading input file");
    }

    if (fseek(inputFile, 0, SEEK_SET) != 0) { //reset file pointer to start
        perror("Error resetting file pointer");
    } else {
        printf("File pointer reset successfully.\n");
    }

    if (fgetc(inputFile) == EOF && !feof(inputFile)) { //check for hardware issues
        perror("Hardware failure detected");
    }

    fclose(inputFile); //close input file
    fclose(outputFile); //close output file
    printf("Number of invalid float values: %d\n", invalidValueCount); //print results
}

int main() {
    const char *sourceFileName = "data.txt";        //input file name
    const char *outputFileName = "valid_floats.txt"; //output file name

    processFile(sourceFileName, outputFileName); //process input and output files

    return 0; //exit
}
