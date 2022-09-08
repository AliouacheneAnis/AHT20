#include <Arduino.h>
#include <Adafruit_AHTX0.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

Adafruit_AHTX0 aht;
const int DELAY = 10000; 

unsigned int TempsAvant; 
float Temperature, Humidity;

void setup() {
  
  Serial.begin(9600);

  wifiConnect();      //Branchement au réseau WIFI
  MQTTConnect();     //Branchement au MQTT

  if (! aht.begin()) {
    Serial.println("Could not find AHT20 Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT20 found");
}

void loop() {

  if (millis() - TempsAvant > DELAY)
  {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); 
  Temperature = temp.temperature;
  Humidity = humidity.relative_humidity;
  Serial.print("Temperature: "); 
  Serial.print(Temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.println("% rH");


    // Envoi de donnees sur ThingsBoard
    appendPayload("Temperature", Temperature);  //Ajout de la donnée Etat Pompe au message MQTT
    appendPayload("Humidity", Humidity); //Ajout de la donnée Conductivity au message MQTT
    sendPayload();  //Envoie du message via le protocole MQTT

     TempsAvant = millis();
  }
  
}