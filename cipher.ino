#include "cipher.h"
#include "simon_macro.h"

static uint8_t z[5][64] = {
	{1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0},
	{1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0},
	{1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,1},
	{1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1},
	{1,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1}
			};


void encryptKeySchedule(const uint8_t * inputKey, uint8_t * keys ) {

	const uint32_t *ik = (const uint32_t*)inputKey;
	uint32_t *rk = (uint32_t*)keys;

	int i;
	for ( i = 0; i < SIMON_KEY_WORDS; i++ )  {
		rk[i] = ik[i];
	}

	uint32_t temp;
	for ( i = SIMON_KEY_WORDS; i < SIMON_ROUNDS; i++ ) {
		temp = ror(rk[i-1], 3);

   /*This needs to be re-evaluated*/
		#if defined(SIMON_KEY_WORDS) && (SIMON_KEY_WORDS==4)
			temp ^= rk[i-3];
		#endif
    
		temp ^= ror(temp, 1);
   
   /*my piece, to get rid of SIMON_CONST_C ? */
    rk[i] = ~rk[i-SIMON_KEY_WORDS] ^ temp ^ z[SIMON_SEQUENCE_NUMBER][(i-SIMON_KEY_WORDS)%62] ^ 3 ;
   
   /*
		rk[i] = SIMON_CONST_C ^ rk[i-SIMON_KEY_WORDS] ^ temp;
		if ( z[SIMON_SEQUENCE_NUMBER][(i-SIMON_KEY_WORDS)%62] == 1 ) {
			rk[i] ^=  0x1;
		}
   */
   	}
}

void encrypt(uint8_t * plainText, const uint8_t * keys ) {

	uint64_t *plain = (uint64_t*)plainText;
	const uint64_t *rk = (const uint64_t*)keys;

	int i;
	for ( i = 0; i < SIMON_ROUNDS; i+=2 ) {
		plain[0] = plain[0] ^ rk[i] ^ f(plain[1]);
		plain[1] = plain[1] ^ rk[i+1] ^ f(plain[0]);
	}

}


void decrypt(uint8_t * cipherText, const uint8_t * keys ) {

	uint64_t *cipher = (uint64_t*)cipherText;
	const uint64_t *rk = (const uint64_t*)keys;    
	
	int i;
	for ( i = SIMON_ROUNDS-1; i >= 0; i-=2 ) {
		cipher[1] = cipher[1] ^ rk[i] ^ f(cipher[0]);
		cipher[0] = cipher[0] ^ rk[i-1] ^ f(cipher[1]);
	}
}

//////Helpers


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

