#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "../lib/WiFiManager/WiFiManager.h"

const char* BROKER_MQTT = "ip"; // Endereço Broker MQTT
const int PORT_MQTT = 1883; // Porta MQTT
const char* ACCESS_TOKEN = ""; // Acess Token thingsboard
const char* PUB_TOPIC = "";

WiFiClient clientWifi; 
PubSubClient MQTT(clientWifi);

WiFiManager wifiManager;

void conectMQTT(void){
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ACCESS_TOKEN)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");   
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 1s");
            delay(1000);
        }
    }
}
float getTemp(){}

void sendData(){
  conectMQTT();
  char* data = "{'temp':";
  if(MQTT.publish(PUB_TOPIC, data))
    Serial.println('Send data ok');
  else
    Serial.println('Send data error');
    
  MQTT.loop();
}

void setup() {
  Serial.begin(115200);
  wifiManager.autoConnect("Ambient");
  MQTT.setServer(BROKER_MQTT, PORT_MQTT);
  conectMQTT();
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
}