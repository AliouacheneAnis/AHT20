/*
  Titre      : AHT20
  Auteur     : Anis Aliouachene
  Date       : 08/09/2022
  Description: Tester AHT20 et capter la temperature et humidity 
  Version    : 0.0.1
*/

// Libraires 
#include <Arduino.h>
#include <Adafruit_AHTX0.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

// Declaration Objet aht 
Adafruit_AHTX0 aht;

// Constante intervale du temps 
const int DELAY = 10000; 

//variables 
unsigned int TempsAvant; 
float Temperature, Humidity; 

void setup() {

      Serial.begin(9600); // moniteur serie 

      wifiConnect();      //Branchement au réseau WIFI
      MQTTConnect();     //Branchement au MQTT

    // Test si y a un aht20 brancher en I2C 
      if (! aht.begin()) {
        Serial.println("Could not find AHT20 Check wiring");
        while (1) delay(10);
      }
      Serial.println("AHT20 found");
}

void loop() {

    if (millis() - TempsAvant > DELAY) {

          sensors_event_t humidity, temp; // declaration event 
          aht.getEvent(&humidity, &temp); 
          Temperature = temp.temperature; // capter temperature 
          Humidity = humidity.relative_humidity; // capter humidity  
          Serial.print("Temperature: "); 
          Serial.print(Temperature);  // affichage temperature 
          Serial.println(" C");
          Serial.print("Humidity: ");
          Serial.print(Humidity); // affichage humidity  
          Serial.println("% rH");


          // Envoi de donnees sur ThingsBoard
          appendPayload("Temperature", Temperature);  //Ajout de la donnée temperature au message MQTT
          appendPayload("Humidity", Humidity); //Ajout de la donnée humidity au message MQTT
          sendPayload();  //Envoie du message via le protocole MQTT

          TempsAvant = millis();
    }
  
}