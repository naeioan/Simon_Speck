
#include "cipher.h"
#include "constants.h"
#include "speck_macro.h"

/*
 * key schedule
 * inputKey: the original keys
 * keys: round keys
 */
void encryptKeySchedule(const uint8_t * inputKey, uint8_t * keys ) {
	
	uint32_t *rk = (uint32_t*)keys;
	const uint32_t *ik = (const uint32_t*)inputKey;
	
	u32 l[SPECK_ROUNDS+SPECK_KEY_WORDS-2];
	rk[0] = ik[0];
	l[0] = ik[1];
	l[1] = ik[2];
	#if defined(SPECK_KEY_WORDS) && (SPECK_KEY_WORDS==4)
		l[2] = ik[3];
	#endif
	
	int i;
	for ( i = 0; i < SPECK_ROUNDS-1; i++ ) {
		l[i+SPECK_KEY_WORDS-1] = (rk[i] + ror(l[i], SPECK_A)) ^ (u32)i;
		rk[i+1] = rol(rk[i], SPECK_B) ^ l[i+SPECK_KEY_WORDS-1];
	}
}

/*
 * encrypt
 * plainText: plainText has just one block.
 * keys: round keys
 */
void encrypt(uint8_t * plainText, const uint8_t * keys ) {
	uint64_t *plain = (uint64_t*)plainText;
	const uint64_t* rk = (const uint64_t*)keys;
	
	int i;
	for ( i = 0; i < SPECK_ROUNDS; i++ ) {
		roundFunction(plain[1], plain[0], rk[i]);
	}
}

/*
 * decrypt
 * cipherText: cipherText has just one block.
 * keys: round keys
 */
void decrypt(uint8_t * cipherText, const uint8_t * keys ) {
	uint64_t *cipher = (uint64_t*)cipherText;
	const uint64_t* rk = (const uint64_t*)keys;
	
	int i;
	for ( i = SPECK_ROUNDS-1; i >= 0; i-- ) {
		invertRoundFunction(cipher[1], cipher[0], rk[i]);
		//cipher[0] = ror(cipher[1] ^ cipher[0], SPECK_B);
		//cipher[1] = rol(((cipher[1] ^ rk[i]) - cipher[0]), SPECK_A);
	}
}

//Helpers

void getUserInput(char buffer[],uint8_t maxSize){
  memset(buffer,0,maxSize);
  while(Serial.available()==0)
  {
    delay(1);
   }
  uint8_t count=0;
  do
  {
    count += Serial.readBytes(buffer+count,maxSize);
    delay(1);
  }while((count<maxSize) && !(Serial.available()==0));
  }

void printArr(uint8_t arr[],char* txt){
    Serial.print(txt);
    
     for(int i=0;i<16;i++){
        Serial.print(arr[i],HEX);
        Serial.print(" ");
        }
        Serial.println("");
   }
