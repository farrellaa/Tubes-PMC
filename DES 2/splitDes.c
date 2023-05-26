#include "des.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void hex64ToString (uint64_t hex, unsigned char* output, char addNull) {
    
    // Left-align hex bits before conversion (to avoid leading null terminator in string)
    int j = 0;
    while (((hex >> 8*15) == 0) && j<16) {
        hex <<= 8;
        j++;
    }
    
    // Assign every byte (left to right) to a char in string
    for(int i=0; i<8; i++) {
        output[i] = (hex >> 8*(7-i));
    }
    
    if (addNull) output[8] = 0;
}

uint64_t stringToHex64 (unsigned char* input) {
    
    // Note: max size 8 bytes
    
    uint64_t hex = 0; // Returned hex will be left-zero-padded
    
    // hex value added from string characters, left-to-right
    for(int i=0; i<MIN(8,strlen(input)); i++) {
        hex |= ((uint64_t) input[i]) << 8*(MIN(8,strlen(input))-1-i);
    }
    
    return hex;
}

void splitDes(unsigned char* input, unsigned char* output, uint64_t key, char mode) {
    
    // Note: mode = 'e' for encryption or 'd' for decryption
    
    // Define temp variables
    uint64_t temp = 0;
    
    // Divide string into blocks of 8 chars
    int len = (int) ceil(strlen(input)/8.0);
    printf("%d %d\n",strlen(input),len);
    for (int i=0; i<len; i++) {
        temp = stringToHex64(input+8*i); // string -> uint64_t
        printf("in: %llx\n", temp);
        temp = des(temp,key,mode); // encryption
        printf("out: %llx\n", temp);
        if (i < len-1) hex64ToString(temp,output+8*i,0); // uint64_t -> string
        else hex64ToString(temp,output+8*i,1); // add null terminator on last iteration
    }
    
}

/* testing only
int main() {
    uint64_t key = 0xabcdabcdabcdabcd;
    
    // Note: char array size at least +2 to accommodate trailing newline & null terminator
    unsigned char input[34] = {0};
    unsigned char output[34] = {0};

    printf("Input: ");
    fgets(input, sizeof input, stdin);
    input[strlen(input)-1] = 0; // Remove trailing newline
    
    splitDes(input,output,key,'e');
    splitDes(output,output,key,'d');
    
    printf("%s\n", output);
} */
