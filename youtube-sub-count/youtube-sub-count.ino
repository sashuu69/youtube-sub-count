#include <YoutubeApi.h> // Library to get data from youtube
#include <ESP8266WiFi.h> // Library for Wifi communication
#include <WiFiClientSecure.h> // Library for Server - Client communication
#include <ArduinoJson.h> // Library to work on JSON input from youtube
#include <Wire.h> // Library for OLED display
#include <SSD1306.h> // Library for OLED display

#define API_KEY "" // Paste your youtube API inside the quotes
#define CHANNEL_ID "" // Paste your channel's ID inside the quotes

char ssid[] = ""; // Enter your WiFi's SSID
char password[] = ""; // ENter your WiFi's password

SSD1306  display(0x3c, 4,5); // For OLED display
WiFiClientSecure client; // For Client Server communication
YoutubeApi api(API_KEY, client); // To get data from youtube

unsigned long api_mtbs = 1000; //Increase the number to increase the API refresh rate. At present set to every 1 sec.
unsigned long api_lasttime;
int subs_count; // To store subscriber count
int view_count; // To store view count

void setup() {
  Serial.begin(115200); // For serial print
  display.init(); // For OLED display
  display.flipScreenVertically(); // For OLED display
  display.setFont(ArialMT_Plain_24); // For OLED display

  //For establishing WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  //For OLED boot screen
  display.drawString(0,6, "ZenoModiff"); // Replace text with your name
  display.display();
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
