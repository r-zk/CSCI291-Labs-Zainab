#include <stdio.h> //include standard input/output library
#include <stdlib.h> //include standard library for memory allocation and other utilities

#define IMAGE_WIDTH 512 //define the width of image
#define IMAGE_HEIGHT 512 //define the height of image

//function to read a PGM text file
int readPGMText(const char *filename, unsigned char *pixelData, int width, int height) {
    FILE *file = fopen(filename, "r"); //open file in read mode
    if (!file) { //check if file was opened successfully
        printf("Error: Cannot open file %s\n", filename); //print error message if file cannot be opened
        return -1; //return error code
    }

    //read header
    char format[3]; //array to store format
    fscanf(file, "%s\n", format); //read format from file
    if (format[0] != 'P' || format[1] != '2') { //check if format is P2
        printf("Error: Invalid PGM format\n"); //print error message if format is invalid
        fclose(file); //close the file
        return -2; //return error code
    }

    //skip comments
    char c = getc(file); //get a character from the file
    while (c == '#') { //check if character is a comment
        while (getc(file) != '\n'); //skip comment line
        c = getc(file); //get next character
    }
    ungetc(c, file); //put character back to file

    //read dimensions and max value
    int imgWidth, imgHeight, maxVal; //variables to store width, height, and max value
    fscanf(file, "%d %d\n%d\n", &imgWidth, &imgHeight, &maxVal); //read dimensions and max value from file
    
    if (imgWidth != width || imgHeight != height) { //check if dimensions match
        printf("Error: Image dimensions mismatch\n"); //print error message if dimensions do not match
        fclose(file); //close file
        return -3; //return error code
    }

    //read pixel values
    for (int i = 0; i < width * height; i++) { //loop through each pixel
        int pixelValue; //variable to store pixel value
        fscanf(file, "%d", &pixelValue); //read pixel value from file
        *(pixelData + i) = (unsigned char)pixelValue; //store pixel value in array
    }

    fclose(file); //close file
    return 0; //return success code
}

//function to write a PGM text file
int writePGMText(const char *filename, unsigned char *pixelData, int width, int height) {
    FILE *file = fopen(filename, "w"); //open the file in write mode
    if (!file) { //check if file was opened successfully
        printf("Error: Cannot create file %s\n", filename); //print error message if file cannot be created
        return -1; //return error code
    }

    //write header
    fprintf(file, "P2\n"); //write format
    fprintf(file, "# Created by LSB Steganography\n"); //write a comment
    fprintf(file, "%d %d\n", width, height); //write dimensions
    fprintf(file, "255\n"); //write max value

    //write pixel values
    for (int i = 0; i < width * height; i++) { //loop through each pixel
        fprintf(file, "%d", pixelData[i]); //write the pixel value to the file
        if ((i + 1) % width == 0) //check if end of row is reached
            fprintf(file, "\n"); //write a newline character
        else
            fprintf(file, " "); //write a space character
    }

    fclose(file); //close file
    return 0; //return success code
}

int writePGMBinary(const char *filename, unsigned char *pixelData, int width, int height) {
    FILE *file = fopen(filename, "wb"); //open file in binary write mode
    if (!file) { //check if file was opened successfully
        printf("Error: Cannot create file %s\n", filename); //print error message if file cannot be created
        return -1; //return error code
    }

    //write header
    fprintf(file, "P5\n"); //write format
    fprintf(file, "# Created by LSB Steganography\n"); //write a comment
    fprintf(file, "%d %d\n", width, height); //write dimensions
    fprintf(file, "255\n"); //write max value

    //write pixel values in binary
    fwrite(pixelData, sizeof(unsigned char), width * height, file); //write pixel values to file in binary format

    fclose(file); //close file
    return 0; //return success code
}

void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) { //loop through each pixel
        *(coverPixels + i) &= 0xF0; //clear 4 LSBs of cover pixel
        
        unsigned char secretMSB = (*(secretPixels + i) & 0xF0) >> 4; //get 4 MSBs of secret pixel and shift right
        
        *(coverPixels + i) |= secretMSB; //combine with cover pixel
    }
}

void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) { //loop through each pixel
        unsigned char lsb = *(coverPixels + i) & 0x0F; //get 4 LSBs from stego pixel
        
        *(outputPixels + i) = lsb << 4; //shift left to become MSBs
    }
}

int main() {
    const char *coverImageFile = "baboon.pgm"; //cover image file name
    const char *secretImageFile = "farm.pgm"; //secret image file name
    const char *stegoImageFile = "stego_image_bin.pgm"; //stego image file name
    const char *extractedSecretFile = "extracted_secret.pgm"; //extracted secret image file name

    unsigned char *coverPixelData, *secretPixelData, *outputPixelData; //pointers to store pixel data
    int coverWidth = IMAGE_WIDTH, coverHeight = IMAGE_HEIGHT; //cover image dimensions
    int secretWidth = IMAGE_WIDTH, secretHeight = IMAGE_HEIGHT; //secret image dimensions

    coverPixelData = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char)); //allocate memory for cover image
    if (!coverPixelData) { //check if memory allocation was successful
        printf("Error: Memory allocation failed for cover image\n"); //print error message if memory allocation failed
        return -1; //return error code
    }

    if (readPGMText(coverImageFile, coverPixelData, coverWidth, coverHeight) != 0) { //read cover image
        free(coverPixelData); //free allocated memory
        return -2; //return error code
    }

    secretPixelData = (unsigned char *)malloc(secretWidth * secretHeight * sizeof(unsigned char)); //allocate memory for secret image
    if (!secretPixelData) { //check if memory allocation was successful
        printf("Error: Memory allocation failed for secret image\n"); //print error message if memory allocation failed
        free(coverPixelData); //free allocated memory
        return -3; //return error code
    }

    if (readPGMText(secretImageFile, secretPixelData, secretWidth, secretHeight) != 0) { //read secret image
        free(coverPixelData); //free allocated memory
        free(secretPixelData); //free allocated memory
        return -4; //return error code
    }

    if (coverWidth != secretWidth || coverHeight != secretHeight) { //check if dimensions match
        printf("Error: Image dimensions do not match\n"); //print error message if dimensions do not match
        free(coverPixelData); //free allocated memory
        free(secretPixelData); //free allocated memory
        return -5; //return error code
    }

    embedLSB(coverPixelData, secretPixelData, coverWidth, coverHeight); //embed secret image into cover image

    if (writePGMBinary(stegoImageFile, coverPixelData, coverWidth, coverHeight) != 0) { //save stego image
        free(coverPixelData); //free allocated memory
        free(secretPixelData); //free allocated memory
        return -6; //return error code
    }

    outputPixelData = (unsigned char *)malloc(coverWidth * coverHeight * sizeof(unsigned char)); //allocate memory for output image
    if (!outputPixelData) { //check if memory allocation was successful
        printf("Error: Memory allocation failed for output image\n"); //print error message if memory allocation failed
        free(coverPixelData); //free allocated memory
        free(secretPixelData); //free allocated memory
        return -7; //return error code
    }

    extractLSB(coverPixelData, outputPixelData, coverWidth, coverHeight); //extract secret image

    if (writePGMText(extractedSecretFile, outputPixelData, coverWidth, coverHeight) != 0) { //save extracted secret image
        free(coverPixelData); //free allocated memory
        free(secretPixelData); //free allocated memory
        free(outputPixelData); //free allocated memory
        return -8; //return error code
    }

    free(coverPixelData); //free allocated memory
    free(secretPixelData); //free allocated memory
    free(outputPixelData); //free allocated memory

    printf("Steganography process completed successfully!\n"); //print success message
    return 0; //return success code
}
