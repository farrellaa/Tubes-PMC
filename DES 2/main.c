#include "des.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

void hexToString (uint64_t hex, unsigned char* string) {
    
    //
    int j = 0;
    while (((hex >> 8*15) == 0) && j<16) {
        hex <<= 8;
        j++;
    }
    for(int i=0; i<16; i++) {
        string[i] = (unsigned char) ((hex >> 8*(15-i)) & 0xff);
    }
    string[16] = 0;
}

void stringToHex (uint64_t *hex, unsigned char* string) {
    *hex = 0;
    for(int i=0; i<strlen(string); i++) {
        *hex |= ((uint64_t) string[i]) << 8*(strlen(string)-1-i);
    }
}

int main() {
    
    // Define key & in/out variables
    uint64_t key = 0xabcdabcdabcdabcd;
    uint64_t in = 0;
    uint64_t out = 0;
    

    // Define string variables
    unsigned char cin[] = {0xab, 0xcd, 0xab, 0xcd, 0xab, 0xcd, 0xab, 0xcd, 0};
    unsigned char cout[17] = {0};
    unsigned char text[21] = {'a','u','f','a','r','r'};

    printf("Plaintext: %s\n", text);
    stringToHex(&in,text); // Convert string (max 8 chars) to hex
    out = des(in,key,'e'); // Encryption
    printf("Cipher (hex): %016llx\n", out);
    hexToString(out,text);// Convert hex to string (max 64 bits)
    printf("Cipher (plaintext): %s\n",text);
    out = des(out,key,'d'); // Decryption
    printf("Plaintext (decrypted, hex): %016llx\n", out);
    hexToString(out,text);// Convert hex to string (max 64 bits)
    printf("Plaintext (decrypted): %s\n", text); 
    
}