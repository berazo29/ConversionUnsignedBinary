#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FOUR 4

int hex_char_int(char hex );

// Transform decimal to hexadecimal integers and return a string of hexadecimal representation
char *decimalToHexadecimal(unsigned long decimal){

    // Allocate memory for max 20
    char *hex= malloc(20 * sizeof(char *));

    int i = 0;
    while(decimal != 0){

        unsigned long temp  = 0;
        temp = decimal % 16;

        // check if temp < 10 and return the number
        if(temp < 10){
            hex[i] = (temp + 48);
            i++;
        }
        // otherwise, return a letter to the specific 10-16 representation as A-F
        else{

            hex[i] = temp + 55;
            i++;
        }
        decimal = decimal / 16;
    }
    // Return 0 if empty array
    if (strcmp(hex, "") == 0){
        return "0";
    }
    return hex;
}
// Gives back a binary from 0 to 16;
char *binaryHexadecimalInteger(int index){
    if (index < 0 || index > 15){
        perror("only integer 0-15 inclusive\n");
        return NULL;
    }
    char *arr[16];
    arr[0]= "0000";
    arr[1]= "0001";
    arr[2]= "0010";
    arr[3]= "0011";
    arr[4]= "0100";
    arr[5]= "0101";
    arr[6]= "0110";
    arr[7]= "0111";
    arr[8]= "1000";
    arr[9]= "1001";
    arr[10]="1010";
    arr[11]="1011";
    arr[12]="1100";
    arr[13]="1101";
    arr[14]="1110";
    arr[15]="1111";

    return arr[index];
}

// Utility function to transform hex char to decimal
int hex_char_int(char hex ){
    switch (hex) {
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return hex - '0';
    }
}

int main( int argc, char *argv[argc+1]) {

    //File name from arguments
    if (argc != 2 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data
    unsigned long inputDecimal;
    unsigned int inputSize;
    char *hex = NULL;

    while ( fscanf( fp, "%ld %d", &inputDecimal, &inputSize ) != EOF ){
        hex = decimalToHexadecimal(inputDecimal); // decimal in hexadecimal string
        int lenHex = strlen(hex);
        int lenBinHex = FOUR*lenHex;
        char *bin=NULL;
        int index;
        // Check for error
        if (inputSize == 0){
            perror("Please enter only valid values for size greater than 0\n");
            return EXIT_FAILURE;
        }
        if (lenHex == 1){
            // the same size
            index = hex_char_int(hex[0]);
            bin = binaryHexadecimalInteger(index);
            if (inputSize == FOUR){
                // Print the value
                //printf(" %c %s",hex[i], bin); // test print
                printf("%s",bin);
            } else if (inputSize < FOUR){
                // Smaller than
                for (int i = FOUR-inputSize; i < lenBinHex; ++i) {
                    //printf(" %c %s",hex[i], bin); // test print
                    printf("%c",bin[i]);
                }

            } else{
                //bigger than
                //Print zeros before
                for (int i = 0; i < inputSize-lenBinHex; ++i) {
                    printf("0");
                }
                //print the binary
                for (int i = 0; i < lenBinHex; ++i) {
                    //printf(" %c %s",hex[i], bin); // test print
                    printf("%c",bin[i]);
                }
            }
            printf("\n");
            continue;
        }

        // If input file is multiple of 4 display print each set of binaries
        if (lenHex > 1){

            // when is a 4 bites representation print each one
            if ( lenBinHex == inputSize){
                // Print in reverse order
                for (int i = lenHex-1; i >= 0; --i) {
                    index = hex_char_int(hex[i]);
                    bin = binaryHexadecimalInteger(index);
                    //printf(" %c %s",hex[i], bin); // test print
                    printf("%s",bin);
                }
                printf("\n");
                continue;
            }else if ( lenBinHex < inputSize){
                //printf("small\n");
                for (int i = 0; i < inputSize-lenBinHex; ++i) {
                    printf("0");
                }
                for (int i = lenHex-1; i >= 0; --i) {
                    index = hex_char_int(hex[i]);
                    bin = binaryHexadecimalInteger(index);
                    //printf(" %c %s",hex[i], bin); // test print
                    printf("%s",bin);
                }

            } else{
                //bigger than
                //printf("bigger\n");
                //print the remainder
                // If input is multiple of 4 the print the bytes
                if (inputSize % FOUR == 0){
                    for (int i = ((int)inputSize / FOUR)-1; i >= 0; --i) {
                        index = hex_char_int(hex[i]);
                        bin = binaryHexadecimalInteger(index);
                        //printf(" %c %s",hex[i], bin); // test print
                        printf("%s",bin);
                    }
                } else{
                    //bigger Number
                    unsigned int tmp = inputSize/FOUR;
                    // smaller input
                    if (tmp == 0){
                        index = hex_char_int(hex[0]);
                        bin = binaryHexadecimalInteger(index);
                        for (int i = FOUR - inputSize; i < FOUR; ++i) {
                            printf("%c",bin[i]);
                        }
                        printf("\n");
                        continue;
                    } else{
                        unsigned int integerSection = inputSize/FOUR;
                        unsigned int offsetSection = inputSize%FOUR;
                        index = hex_char_int(hex[integerSection]);
                        bin = binaryHexadecimalInteger(index);
                        for (int i = FOUR - offsetSection; i < FOUR; ++i) {
                            printf("%c",bin[i]);
                        }
                        for (int i = (int)integerSection-1; i >= 0; --i) {
                            index = hex_char_int(hex[i]);
                            bin = binaryHexadecimalInteger(index);
                            //printf(" %c %s",hex[i], bin); // test print
                            printf("%s",bin);
                        }

                    }
                }
            }
            printf("\n");

        }

    }
     //Close the file memory allocations
    fclose(fp);

    return EXIT_SUCCESS;
}