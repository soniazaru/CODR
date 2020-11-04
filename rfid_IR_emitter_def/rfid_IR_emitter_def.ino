#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#include <IRremote.h>
IRsend irsend;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();


  if (content.substring(1) == "80 39 DC 32") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("va avanti");
    Serial.println();
    irsend.sendSony(0xFF629D, 24);
    delay(3000);
  } else if (content.substring(1) == "F9 4F 09 B3") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("gira a destra");
    Serial.println();
    irsend.sendSony(0xFFC23D, 24);
    delay(3000);
  } else if (content.substring(1) == "E9 F0 15 B3") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("va indietro");
    Serial.println();
    irsend.sendSony(0xFFA857, 24);
    delay(3000);
  } else if (content.substring(1) == "79 C9 15 B3") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("gira a sinistra");
    Serial.println();
    irsend.sendSony(0xFF22DD, 24);
    delay(3000);
  } else if (content.substring(1) == "59 D1 0B B3") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("stop");
    Serial.println();
    irsend.sendSony(0xFF02FD, 24);
    delay(3000);
  } else if (content.substring(1) == "69 E5 10 B3") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("smile");
    Serial.println();
    irsend.sendSony(0xFF42BD, 24);
    delay(3000);
  }
  /*
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
  */
} 
