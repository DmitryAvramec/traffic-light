/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
#define ESP_ID 1 //Set here id of device

#define RED_LED_PIN     14
#define YELLOW_LED_PIN  12
#define GREEN_LED_PIN   13
#define SSID "Wifi_name"
#define SSID_PASS "Wifi_pass"
ESP8266WiFiMulti WiFiMulti;
String MESSAGE = "{\"current_state\":\"off\"}";

void setup() {
    pinMode(RED_LED_PIN , OUTPUT);
    pinMode(GREEN_LED_PIN,OUTPUT);
    pinMode(YELLOW_LED_PIN,OUTPUT);

    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(true);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 14; t >= 12; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        digitalWrite(t, HIGH);
        delay(1000);
        digitalWrite(t, LOW);
    }
    WiFiMulti.addAP(SSID, SSID_PASS);

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        USE_SERIAL.print("[HTTP] begin...\n");
        USE_SERIAL.print("[HTTP] POST...\n");
        // start connection and send HTTP header
        String url = "http://192.168.100.47:3000/light/" + ESP_ID;      
        http.begin(url); // Set path to your server here
        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(MESSAGE);        
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            if(payload.startsWith("{\"action\":\"nothing\"")){
                USE_SERIAL.println(payload);
                delay(10000);
            }
            if(payload.startsWith("{\"action\":\"red\"")){
                lightRed(payload);
            }
            if(payload.startsWith("{\"action\":\"yellow\"")){
                lightYellow(payload);
            }
            if(payload.startsWith("{\"action\":\"green\"")){
                lightGreen(payload);
            }
            if(payload.startsWith("{\"action\":\"off\"")){
                lightOff(payload);
            }
        }
        else {
            USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
            errorBlink();
        }
        http.end();
    }
    delay(10000);
}
void lightRed (String payload) {
    USE_SERIAL.println(payload);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN , HIGH);
    MESSAGE = "{\"current_state\":\"red\"}";
}

void lightYellow (String payload) {
    USE_SERIAL.println(payload);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    MESSAGE = "{\"current_state\":\"yellow\"}";
}

void lightGreen (String payload) {
    USE_SERIAL.println(payload);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    MESSAGE = "{\"current_state\":\"green\"}";
}

void lightOff (String payload) {
    USE_SERIAL.println(payload);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    MESSAGE = "{\"current_state\":\"off\"}";
}

void errorBlink () {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    for(uint8_t t = 14; t >= 12; t--) {
          digitalWrite(t, HIGH);
          delay(1000);
          digitalWrite(t, LOW);
          delay(1000);
    }
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(10000);
}

