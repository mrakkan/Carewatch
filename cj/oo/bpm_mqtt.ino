// TODO import library
//// ^ import library : oled
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //animation
#include <Adafruit_SH110X.h>
#include <Adafruit_SSD1306> //animation
#include <Fonts/FreeSans18pt7b.h>

//// ^ import library : pulseSensor
    //$ เข้า analog pin 0
    //$ from PulseSensor Playground Getting_BPM_to_Monitor
    //$ ยังไม่ได้เอาโค้ดขึ้นจอ

#include <PulseSensorPlayground.h>




#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "Nokia Lumia 149+";          // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "123123123";  // CHANGE TO YOUR WIFI PASSWORD

const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "999";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                                            // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";                                            // CHANGE IT IF REQUIRED, empty if not required

// The MQTT topics that Arduino should publish/subscribe
const char PUBLISH_TOPIC[] = "testtopic/999157";    // CHANGE IT AS YOU DESIRE
const char SUBSCRIBE_TOPIC[] = "testtopic/999157";  // CHANGE IT AS YOU DESIRE
+
const int PUBLISH_INTERVAL = 60 * 1000;  // 60 seconds

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;







//aniamation
#define SCREEN_I2C_ADDR 0x3C //
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

#define FRAME_DELAY (42)
#define FRAME_WIDTH (null)
#define FRAME_HEIGHT (null)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
const byte PROGMEM frames[][350] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,7,227,96,195,49,254,0,7,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,0,99,96,195,49,254,0,0,35,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,0,25,128,192,0,0,0,4,49,128,192,0,0,0,6,49,129,224,0,0,0,6,49,129,224,0,0,0,6,49,129,224,0,0,0,3,112,193,176,0,0,0,3,96,195,49,254,0,0,3,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,0,25,128,192,0,0,0,0,49,128,192,0,0,0,0,49,129,224,0,0,0,0,49,129,224,0,0,0,0,49,129,224,0,0,0,0,112,193,176,0,0,0,0,96,195,49,254,0,0,0,96,195,49,254,0,0,0,96,195,27,0,0,0,0,96,198,31,0,0,0,0,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,0,1,128,192,0,0,0,0,1,128,192,0,0,0,0,1,129,224,0,0,0,0,1,129,224,0,0,0,0,1,129,224,0,0,0,0,0,193,176,0,0,0,0,0,195,49,254,0,0,0,0,195,49,254,0,0,0,0,195,27,0,0,0,0,0,198,31,0,0,0,0,0,198,30,0,0,0,0,0,102,12,0,0,0,0,0,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,1,128,0,0,0,0,0,1,128,192,0,0,0,0,1,128,192,0,0,0,0,1,129,224,0,0,0,0,1,129,224,0,0,0,0,1,129,224,0,0,0,0,0,193,176,0,0,0,0,0,195,49,254,0,0,0,0,195,49,254,0,0,0,0,195,27,0,0,0,0,0,198,31,0,0,0,0,0,198,30,0,0,0,0,0,102,12,0,0,0,0,0,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,0,0,0,0,0,0,192,0,0,0,0,0,1,224,0,0,0,0,0,1,224,0,0,0,0,0,1,224,0,0,0,0,0,1,176,0,0,0,0,0,3,49,254,0,0,0,0,3,49,254,0,0,0,0,3,27,0,0,0,0,0,6,31,0,0,0,0,0,6,30,0,0,0,0,0,102,12,0,0,0,0,0,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,0,0,0,0,0,0,192,0,0,0,0,0,1,224,0,0,0,0,0,1,224,0,0,0,0,0,1,224,0,0,0,0,0,1,176,0,0,0,0,0,3,49,254,0,0,0,0,3,49,254,0,0,0,0,3,27,0,0,0,0,0,6,31,0,0,0,0,0,6,30,0,0,0,0,0,6,12,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,254,0,0,0,0,0,17,254,0,0,0,0,0,27,0,0,0,0,0,0,31,0,0,0,0,0,0,30,0,0,0,0,0,0,12,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,12,0,0,0,0,0,0,30,0,0,0,0,0,0,30,0,0,0,0,0,0,52,0,0,0,0,0,0,48,0,0,0,0,0,31,224,0,0,0,0,0,31,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,12,0,0,0,0,0,0,30,32,0,0,0,0,0,30,48,0,0,0,0,0,54,48,0,0,0,0,0,51,96,0,0,0,0,31,227,96,0,0,0,0,31,227,96,0,0,0,0,0,1,224,0,0,0,0,0,1,224,0,0,0,0,0,1,192,0,0,0,0,0,0,192,0,0,0,0,0,0,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,14,0,0,0,0,0,0,12,0,0,0,0,0,0,28,0,0,0,0,0,0,24,0,0,0,0,0,0,24,0,0,0,0,0,0,24,0,0,0,0,0,12,24,0,0,0,0,0,12,48,0,0,0,0,0,30,48,0,0,0,0,0,30,48,0,0,0,0,0,54,48,0,0,0,0,0,51,112,0,0,0,0,31,227,96,0,0,0,0,31,227,96,0,0,0,0,0,1,224,0,0,0,0,0,1,224,0,0,0,0,0,1,192,0,0,0,0,0,0,192,0,0,0,0,0,0,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,0,0,0,0,12,49,128,0,0,0,0,30,49,128,0,0,0,0,30,49,128,0,0,0,0,54,49,128,0,0,0,0,51,112,192,0,0,0,31,227,96,192,0,0,0,31,227,96,192,0,0,0,0,1,224,192,0,0,0,0,1,224,192,0,0,0,0,1,192,192,0,0,0,0,0,192,0,0,0,0,0,0,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,0,0,0,0,12,49,128,0,0,0,0,30,49,128,0,0,0,0,30,49,128,0,0,0,0,54,49,128,0,0,0,0,51,112,192,0,0,0,31,227,96,192,0,0,0,31,227,96,192,0,0,0,0,1,224,192,0,0,0,0,1,224,192,0,0,0,0,1,192,192,0,0,0,0,0,192,96,0,0,0,0,0,192,96,0,0,0,0,0,0,96,0,0,0,0,0,0,104,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,0,0,0,0,12,49,128,0,0,0,0,30,49,129,128,0,0,0,30,49,129,128,0,0,0,54,49,129,128,0,0,0,51,112,193,128,0,0,31,227,96,195,0,0,0,31,227,96,195,0,0,0,0,1,224,195,0,0,0,0,1,224,198,0,0,0,0,1,192,198,0,0,0,0,0,192,102,0,0,0,0,0,192,108,0,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,48,0,0,31,227,96,195,48,0,0,0,1,224,195,24,0,0,0,1,224,198,24,0,0,0,1,192,198,0,0,0,0,0,192,102,0,0,0,0,0,192,108,0,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,48,0,0,31,227,96,195,49,0,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,248,0,31,227,96,195,49,248,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,14,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,15,0,0,0,0,0,0,31,0,0,0,0,0,0,27,0,0,0,0,0,0,27,0,0,0,0,0,0,25,128,0,0,0,0,12,25,128,192,0,0,0,12,49,128,192,0,0,0,30,49,129,224,0,0,0,30,49,129,224,0,0,0,54,49,129,224,0,0,0,51,112,193,176,0,0,31,227,96,195,49,254,0,31,227,96,195,49,254,0,0,1,224,195,27,0,0,0,1,224,198,31,0,0,0,1,192,198,30,0,0,0,0,192,102,12,0,0,0,0,192,108,12,0,0,0,0,0,108,0,0,0,0,0,0,108,0,0,0,0,0,0,120,0,0,0,0,0,0,120,0,0,0,0,0,0,56,0,0,0,0,0,0,56,0,0,0,0,0,0,48,0,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


//// ^ variables : pulseSensor
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;

PulseSensorPlayground pulseSensor;

int bpm_val = 0;  // ตัวแปรสำหรับทดสอบแสดงผล

//// ^ variables : gy521
const int MPU_ADDR = 0x68;

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;

char tmp_str[7];

int steps = 0;

char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


void pulseSetup() {
  Serial.begin(115200);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
   }
}

void ledSetup() {
  // Serial.begin(9600);
  if (!display.begin(i2c_Address, true)) {  // สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
    Serial.println("SSD1306 allocation failed");
  } else {
    Serial.println("OLED Start Working !!!");
  }

  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

//animation
void animationloop(){
  display.clearDisplay();
  display.drawBitmap(64, 32, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  delay(FRAME_DELAY);
}

//////////////////////////////////////////////////////////// TODO

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageHandler);

  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino UNO R4 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT() { //* ค่าเข้าตรงนี้
  // int val = millis();
  // //int val = analogRead(A0);
  // String val_str = String(val);

  // // Convert the string to a char array for MQTT publishing
  // char messageBuffer[10];
  // val_str.toCharArray(messageBuffer, 10);

  // // Publish the message to the MQTT topic
  // mqtt.publish(PUBLISH_TOPIC, messageBuffer); //* ส่งขึ้น mqtt ตรงนี้

  // // Print debug information to the Serial Monitor in one line
  // Serial.println("Arduino UNO R4 - sent to MQTT: topic: " + String(PUBLISH_TOPIC) + " | payload: " + String(messageBuffer));


  String jsonPayload = "{\"bpm\":" + String(bpm_val) + ",\"steps\":" + String(steps) + "}";
  mqtt.publish(PUBLISH_TOPIC, jsonPayload);
  Serial.println("Sent: " + jsonPayload);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("Arduino UNO R4 - received from MQTT: topic: " + topic + " | payload: " + payload);

  // You can process the incoming data , then control something
  /*
  process something
  */
}

//////////////////////////////////////////////////////////// TODO
//////////////////////////////////////////////////////////// TODO
//////////////////////////////////////////////////////////// TODO

void setup() {
  //animation


  pulseSetup();
  ledSetup();

  Serial.begin(9600);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Arduino UNO R4 - Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  connectToMQTT();
}

int frame = 0; //animation

void loop() {
  mqtt.loop();

//// ^ loop : oled
  display.clearDisplay();              // ลบภาพในหน้าจอทั้งหมด

//// ^ loop : gy521
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true);

  accelerometer_x = Wire.read()<<8 | Wire.read();
  accelerometer_y = Wire.read()<<8 | Wire.read();
  accelerometer_z = Wire.read()<<8 | Wire.read();

  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();

  if (gyro_x > 1000 || gyro_y > 1000 || gyro_z > 1000) {
    steps++;
  }

//// ^ loop : pulse
  pulseSensor.sawStartOfBeat();
  bpm_val = pulseSensor.getBeatsPerMinute();
  bpm_val = bpm_val / 2;

//// ^ loop : oled (continue)
  display.setCursor(0, 0);
  display.setFonts(&FreeSans18pt7b);
  display.setTextColor(SH110X_BLACK, SH110X_WHITE);  //กำหนดข้อความสีดำ ฉากหลังสีขาว
  display.print("  CareWear  ");

  display.setCursor(0, 20);
  display.print("🤍");
  // display.setTextSize(1);
  display.setCursor(20, 20);
  display.setTextColor(SH110X_WHITE);  //กำหนดข้อความสีดำ ฉากหลังสีขาว
  // display.print(bpm_val, DEC);
  display.print(bpm_val);   //^ bmp value

  display.setCursor(40, 20); 
  display.print(" BPM");  //^ bmp text

  display.setCursor(0, 40);
  // display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);  //กำหนดข้อความสีดำ ฉากหลังสีขาว
  // display.print(bpm_val, DEC); //send step from gyro
  display.print(steps); //^ steps value

  display.setCursor(40, 40); 
  display.print(" Step(s)");  //^ steps text

  display.display();  // สั่งให้จอแสดงผล
  
  sendToMQTT();
  delay(500);

}





