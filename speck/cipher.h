/*
 *
 * The input is from right to left. 
 * The rightmost byte is the least significant byte.
 * The leftmost byte is the most significant byte.
 */

#ifndef CIPHER
#define CIPHER

#include <stdint.h>



void encryptKeySchedule(const uint8_t * inputKey, uint8_t * keys );

void encrypt(uint8_t * plainText, const uint8_t * keys );

void decrypt(uint8_t * cipherText, const uint8_t * keys );

////Helpers
void getUserInput(char buffer[],uint8_t maxSize);
void printArr(uint8_t arr[],char* txt);

#endif
