#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 5
#define RST_PIN 21


MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
const int greenLEDPin = 12;  // Green LED connected to digital pin 12
const int redLEDPin = 32;    // Red LED connected to digital pin 32
const int buzzerPin = 26;    // Buzzer connected to digital pin 26

//Card UID: 0A E6 5B B2  <--- this is the ucid for the blue key 
bool ledState = HIGH;     // Stores which LED is ON
void setup()
{
    pinMode(greenLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

 Serial.begin(115200); // Initiate a serial communication
 SPI.begin(); // Initiate SPI bus
 mfrc522.PCD_Init(); // Initiate MFRC522
 Serial.println("Please tap your card....");
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
 Serial.println("Searching...");
 delay(3000); // takes 3 secs to display the UID 
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
  if (content.substring(1) == "0A E6 5B B2" ) //change here the UID of the card/cards that you want to give access
 {
  digitalWrite(greenLEDPin, HIGH); // access granted will display green light
    delay(100);
 Serial.println("Authorized access");
 Serial.println();
  delay(3000);
  digitalWrite(greenLEDPin, LOW);
 }
else {
  digitalWrite(redLEDPin, HIGH); // access rejected will display red light
  digitalWrite(buzzerPin, HIGH); // Turn on Buzzer
  delay(1000);
  digitalWrite(redLEDPin, LOW); //red light off
  digitalWrite(buzzerPin, LOW); // Turn off Buzzer
  delay(1000);
  digitalWrite(redLEDPin, HIGH);//red light on
  digitalWrite(buzzerPin, HIGH); // Turn on Buzzer
  delay(1000);
  digitalWrite(redLEDPin, LOW); //red off
  digitalWrite(buzzerPin, LOW); // Turn off Buzzer
  delay(1000);
  digitalWrite(buzzerPin, HIGH); // Turn on Buzzer
  digitalWrite(redLEDPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW); // Turn on Buzzer
  delay(3000);
  digitalWrite(redLEDPin, LOW); // turn off led
  Serial.println(" Access denied");

 delay(3000);
 }
}