#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// --- CONFIG ---
const char* ssid = "bla bla";
const char* password = "090900//hahaha";
const char* mqtt_server = "12.uuccuu"; 

#define PIN_RGB 48 
Adafruit_NeoPixel pixels(1, PIN_RGB, NEO_GRB + NEO_KHZ800);
Adafruit_MPU6050 mpu;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    pixels.begin();
    pixels.setBrightness(30);
    
    // Status: Purple (Initializing)
    pixels.setPixelColor(0, pixels.Color(150, 0, 255)); 
    pixels.show();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    
    Serial.println("\nWiFi Connected!");
    client.setServer(mqtt_server, 1883);
    Wire.begin(8,9); // SDA, SCL pins for MPU6050
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red (Error)
        pixels.show();
        while (1) { delay(10); }
    }
    // Status: Green (All Systems Go)
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); 
    pixels.show();
}

void reconnect() {
    while (!client.connected()) {
        if (client.connect("ESP32_Vibration_Client")) {
            Serial.println("MQTT Connected!");
        } else {
            delay(5000);
        }
    }
}

void loop() {
    if (!client.connected()) reconnect();
    client.loop();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    String payload = "{\"x\":" + String(a.acceleration.x) + 
                     ",\"y\":" + String(a.acceleration.y) + 
                     ",\"z\":" + String(a.acceleration.z) + "}";
    
    client.publish("motor/vibration", payload.c_str());
    Serial.println("Sent: " + payload);
    delay(100); 
}
