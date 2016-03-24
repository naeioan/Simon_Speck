#include <Arduino.h>
#include <stdio.h>
#include "constants.h"
#include "cipher.h"
#define BUFSIZE    2 

void setup() {
  while(!Serial);
  delay(500);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(">1.Simon Test[128/128]");
Serial.println(">2.Speck Test[128/128]");
char txt[BUFSIZE+1];
getUserInput(txt,BUFSIZE);

if(txt[0]=='1'){
  Serial.println(">Start simon test");
  speck_128_128();
  }
  else
  if(txt[0]=='2'){
    //not implemented yet
  }
  else{
    Serial.println(">Invalid choice");
    }
}

uint8_t speck_128_128 (void){
    /*  
     * Speck128/128
     */
    uint8_t inputKey[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 ,0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    uint8_t keys[SPECK_BLOCK_SIZE/16*SPECK_ROUNDS];
    uint8_t plainText[] = {0x20, 0x74, 0x72, 0x61, 0x76, 0x65, 0x6c, 0x6c, 0x65, 0x72, 0x73, 0x20, 0x64, 0x65, 0x73, 0x63};

    encryptKeySchedule(inputKey, keys);
    printArr(plainText,"PlainText: ");
    
    encrypt(plainText, keys);
    printArr(plainText,"After encryption: ");

    decrypt(plainText, keys);
    printArr(plainText,"After decryption: ");
    Serial.println("###################################################################################################");
     
  return 1;
}
