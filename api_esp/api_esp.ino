#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

#define led 4

ESP8266WiFiMulti WiFiMulti;

const String location = "bedroom";
const String device_id = "unknownDevice";

#define SERVER_IP "192.168.247.201"

#ifndef STASSID
#define STASSID "rassAV"
#define STAPSK "12345678"
#endif

void setup() {
  Serial.begin(4800);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(STASSID, STAPSK);
}

void loop() {
  if (WiFiMulti.run() == WL_CONNECTED) {
    if (Serial.available() > 0) {
      String value = "";
      char ch = Serial.read();
      while (ch != '\n' && Serial.available() > 0) {
        value += (String)ch;
        ch = Serial.read();
      }
      post(value);
    }
    get();
  }
}

void post(String value){
  WiFiClient client;
  HTTPClient http;

  http.begin(client, "http://" + SERVER_IP + ":8005/submit_temperature");
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST("{\"value\":\"" + value + "\", \"location\":\"" + location + "\", \"device_id\":\"" + device_id + "\"}");

  if (httpCode > 0) {
    Serial.print("POST... code: ");
    Serial.print(httpCode);
    Serial.println();
    Serial.println(http.getString(););
  }

  http.end();
}

void get(){
  WiFiClient client;
  HTTPClient http;
  
  String url = "http://" + String(SERVER_IP) + ":8005/temperature/" + location;
  
  if (http.begin(client, url)) {
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.print("GET... code: ");
      Serial.print(httpCode);
      Serial.println();

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        DynamicJsonDocument doc(1048);
        deserializeJson(doc, http.getStream());

        float sum = 0;
        int count = std::size(doc["values"]);

        for (int i = 0; i < count; i++)
          sum += doc["values"][i];

        Serial.print("average value = ");
        Serial.println(sum / count);
      }
    }

    http.end();
  }
}
