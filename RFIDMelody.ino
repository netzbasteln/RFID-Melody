/*
RST = D0
SCK = D5
MISO = D6
MOSI = D7
SDA/SS = D8
*/

#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         D0         // Configurable, see typical pin layout above
#define SS_PIN          D8        // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
  Serial.println("Ein herzliches Hallo mit einer kleinen Melodie!");
    tone(D3, 262);
    delay(200);
    noTone(D3);
    delay(100);
    
    tone(D3, 294);
    delay(200);
    noTone(D3);
    delay(100);
    
    tone(D3, 330);
    delay(200);
    noTone(D3);
    delay(100);
    
    tone(D3, 349);
    delay(200);
    noTone(D3);
    delay(100);
    
    tone(D3, 392);
    delay(400);    
    noTone(D3);
    delay(100);
    
    tone(D3, 392);
    delay(400);    
    noTone(D3);
    delay(200);
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
  tone(D3, 5000, 100);
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println("-- RESET -- ");
}
