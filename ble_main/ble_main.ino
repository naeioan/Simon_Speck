#include <Arduino.h>
#include <stdio.h>
#include "constants.h"
#include "cipher.h"

//BLE includes
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#define BUFSIZE    16 

#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"


/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void)
{
  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Command <-> Data Mode Example"));
  Serial.println(F("------------------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();
/*
  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter characters to send to Bluefruit"));
  Serial.println();
*/
  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  Serial.println("Waiting for connection...\n");
  while (! ble.isConnected()) {
      delay(500);
  }
Serial.println("[OK] Connected!\n");
  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));
}



//Main

void loop()
{
  Serial.println(F(">>Enter message to send..."));
  char txt[BUFSIZE+1];
  getUserInput(txt,BUFSIZE);
  
for(int i = 0; i < sizeof(txt)-1 ; i++){
  Serial.println(uint8_t(txt[i]));
  }
  
  // encrypt

  char msg_enc_snd[BUFSIZE+1];
    
    uint8_t inputKey[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 ,0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    uint8_t keys[SIMON_BLOCK_SIZE/16*SIMON_ROUNDS];
    uint8_t plainText[BUFSIZE+1]; 
    
    for(int i = 0 ; i < 16 ; i++ ){
      plainText[i] = uint8_t(txt[i]);
      }
      
    encryptKeySchedule(inputKey, keys);
    
    printArr(plainText,"PlainText: ");
    
    encrypt(plainText, keys);
    printArr(plainText,"After encryption: ");
  
  for(int i = 0;i < 16 ;i++){
    msg_enc_snd[i] = char(plainText[i]);
    Serial.println(plainText[i]);
    } 
  
  // send over ble

  //msg_enc_snd[16]=0;
  ble.print(msg_enc_snd);
  
  }



