/*
  Titre      : AHT20
  Auteur     : Anis Aliouachene
  Date       : 08/09/2022
  Description: Tester AHT20 et capter la temperature et humidity 
  Version    : 0.0.1
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_AHTX0.h>
#include <Fonts/FreeSans9pt7b.h>


Adafruit_AHTX0 aht;

void setup() {

  Serial.begin(9600);

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.

  delay(3000);


  if (aht.begin()) {
    Serial.println("Found AHT20");
  } else {
    Serial.println("Didn't find AHT20");
  }  
  


}

void loop() {
  sensors_event_t humidity, temp;
  
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

  Serial.println(temp.temperature);

  delay(5000);
}