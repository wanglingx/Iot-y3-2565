#include <ESP8266WiFi.h> 
const char* ssid = "avocado123";
const char* pass = "01162001";
void setup () {
  Serial.begin(230400); //
  WiFi.begin(ssid, pass); 
while (WiFi.status() != WL_CONNECTED) { 
    Serial.println("Connecting...  ");  
    Serial.printf("Connection Status: %d\n", WiFi.status()); 
    delay(1000);
  }
  Serial.print("Wi-Fi connected."); 
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());  
}
void loop () { 
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());  
  Serial.printf("Connection Status: %d\n", WiFi.status());
delay(2000);
}