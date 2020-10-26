#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hex_char_int(char hex );

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

// Returns a string of binaries from a given decimal in 4 bytes alignment
char *decimalToBinary(int decimal){

    int hex  = 0x00;
    int len = 0;

    // Transform decimal to hexadecimal
    for (int i = 0; i < decimal; i++){
        hex++;
    }

    //printf("hex store: %x %d",hex, decimal);

    char buffer[10]; // malloc this one
    snprintf(buffer, 10, "%x", hex);
    len = (int)strlen(buffer);
    char *binary = malloc(len*sizeof(char *));
    for (int i = 0; i < len; ++i) {
        int index = hex_char_int(buffer[i]);
        char *temp = binaryHexadecimalInteger(index);
        strcat(binary, temp);
    }

    return binary;
}
// Utility function to transform hex char to decimal
int hex_char_int(char hex ){
    switch (hex) {
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        default:
            return hex - '0';
    }
}
// String binary trimmer for given size
void printRequiredBinaryFormat(char *binaryString, int len, int size_required){

    if (size_required == len){
        printf("%s",binaryString);
    }
    else if (size_required > len){
        // add zeros;
        for (int i = 0; i < size_required-len; ++i) {
            printf("0");
        }
        printf("%s",binaryString);
    } else{
        for (int i = len-size_required; i < len; ++i) {
            printf("%c",binaryString[i]);
        }
    }
    printf("\n");
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
    int matrixGrid;

    while ( fscanf( fp, "%d", &matrixGrid ) != EOF ){
        printf("%d", matrixGrid);

        char *binary;
        binary = decimalToBinary(27);
        unsigned long strLenBin = strlen(binary);
        printRequiredBinaryFormat(binary,(int)strLenBin,3);
        binary=NULL;
        free(binary);
    }

     //Close the file and destroy memory allocations
    fclose(fp);









    return EXIT_SUCCESS;
}