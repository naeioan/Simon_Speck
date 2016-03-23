/*
 *
 * The input is from right to left. 
 * The rightmost byte is the least significant byte.
 * The leftmost byte is the most significant byte.
 */

#ifndef CIPHER
#define CIPHER

#include <stdint.h>


/*
 * key schedule
 * inputKey: the original keys
 * keys: round keys
 */
void encryptKeySchedule(const uint8_t * inputKey, uint8_t * keys );

/*
 * encrypt
 * plainText: plainText has just one block.
 * keys: round keys
 * Rk(x, y) = (y ⊕ f(x) ⊕ k, x)
 */
void encrypt(uint8_t * plainText, const uint8_t * keys );

/*
 * decrypt
 * cipherText: cipherText has just one block.
 * keys: round keys
 * R−1k(x, y) = (y, x ⊕ f(y) ⊕ k) 
 */
void decrypt(uint8_t * cipherText, const uint8_t * keys );

////Helpers
void getUserInput(char buffer[],uint8_t maxSize);
void printArr(uint8_t arr[],char* txt);
#endif
