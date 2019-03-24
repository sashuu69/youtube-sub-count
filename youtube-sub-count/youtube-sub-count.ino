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

  // For WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // For OLED boot screen
  display.drawString(0,6, "ZenoModiff"); // Replace text with your name
  display.display(); // For displaying the content
  delay(2000); // Set delay for 2 seconds
  display.clear(); // Clear display
  
  // OLED second screen
  display.drawString(0,6, "Youtube");
  display.drawString(0,32, "Sub Count");
  display.display(); // For displaying the content
  delay(2000); // Set delay for 2 seconds
  display.clear(); // Clear display

  Serial.print("Connecting Wifi: "); // print text to serial monitor
  
  // OLED third screen
  display.drawString(0,6, "Connecting ");
  display.drawString(0,32, "  Wifi... ");
  display.display(); // For displaying the content
  delay(250);
  display.clear(); // Clear display

  Serial.println(ssid); // Print WiFi SSID to serial monitor

  WiFi.begin(ssid, password); // Establish connection to given SSID

  // WiFi connection process
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print("."); // To know in serial monitor that the connection process is going on
  delay(500);
  }
  // Print content to Serial monitor
  Serial.println("");
  Serial.println("WiFi");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP(); // To get IP address
  Serial.println(ip); // Print IP address to Serial monitor

  // OLED forth screen
  display.drawString(0,6, "Connected ");
  display.display(); // For displaying the content
  display.clear(); // Clear display
  delay(1000); // Set delay for 1 seconds

  // OLED fifth screen
  display.drawString(0,6, "Getting");
  display.drawString(0,32, "Data.....");
  display.display(); // For displaying the content
  display.clear(); // Clear display
  delay(250);

}

void loop() {
  if (millis() - api_lasttime > api_mtbs)  {
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      subs_count = api.channelStats.subscriberCount ; // Store subscriber count in subs_count
      view_count = api.channelStats.viewCount ; // Store view count in view_count

      // OLED sixth screen
      display.clear();
      display.drawString(0,8, "S: ");
      display.drawString(24,8, subs_count);
      display.drawString(0,32,"V: ");
      display.drawString(24,32, view_count);
      display.display();

      // Print content to Serial monitor
      Serial.println("---------Status---------");
      Serial.println("Zeno_Modiff"); // Replace with your name
      Serial.print("S: ");
      Serial.println(subs_count); 
      Serial.print("V: ");
      Serial.println(view_count);
      Serial.println("------------------------");
    }
    api_lasttime = millis();
  }
}
