/*

RFID Melody 1.0 by Gebrüder Metz / Netzbasteln
PINS WEMOS D1 Mini
RST = D0
SCK = D5
MISO = D6
MOSI = D7
SDA/SS = D8
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D0
#define SS_PIN D8
#define PIEZO_PIN D3

#define TONE_LOW 50
#define TONE_HIGH 2000
#define TONE_DURATION 300

uint8_t random_map[256] = {111,179,16,253,81,147,167,206,225,186,42,155,23,239,222,12,235,240,199,59,255,34,211,187,64,205,110,252,180,197,109,45,251,145,234,52,192,31,56,118,5,132,208,233,39,93,87,92,161,124,117,207,142,44,138,140,0,198,67,128,158,78,71,182,217,139,171,150,188,131,157,99,245,174,115,35,144,220,191,126,254,2,18,8,237,168,228,129,37,26,226,215,113,246,238,3,231,66,156,170,114,57,49,98,209,149,134,100,62,232,29,61,133,160,86,94,121,166,38,106,210,63,58,122,201,193,163,236,47,146,60,88,103,21,1,244,229,55,15,190,183,79,153,24,125,32,25,177,120,36,20,102,165,224,218,221,119,95,83,162,108,154,230,7,241,181,213,104,196,90,130,189,248,216,4,53,243,65,13,172,91,175,17,43,28,227,9,203,22,112,148,159,107,77,178,33,96,10,41,152,184,123,137,249,89,247,75,195,185,202,141,169,223,204,6,219,136,97,164,68,85,74,76,101,242,14,105,214,46,72,200,40,127,50,212,69,48,30,27,116,73,135,176,194,151,70,82,173,54,11,51,84,143,250,19,80};

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


void setup() {
	Serial.begin(9600);
	while ( ! Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();
	mfrc522.PCD_Init();
	delay(4);

	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

}


void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  // Read serial number byte by byte.
  byte idByte = 0;
  for (byte i=0; i<mfrc522.uid.size; i++) {
    idByte = mfrc522.uid.uidByte[i];
    // Randomize.
    idByte = random_map[idByte];
    Serial.print(idByte);
    uint16_t freq = map(idByte, 0, 255, TONE_LOW, TONE_HIGH);
    Serial.print("  ");
    Serial.println(freq);
    tone(PIEZO_PIN, freq, TONE_DURATION);
    delay(TONE_DURATION);
    noTone(PIEZO_PIN);
  }

  delay(1000);
  Serial.println("-------");
}
