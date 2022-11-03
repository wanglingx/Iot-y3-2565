#include <Wire.h>
#include "DHT.h"
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
 // ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

uint8_t DHTPin = 4;
DHT dht(DHTPin, DHTTYPE);

float temperature_Celsius;
float humidity;

#define WIFI_SSID "Ort.palananda"
#define WIFI_PASSWORD "12345678"
#define INFLUXDB_URL "https://us-central1-1.gcp.cloud2.influxdata.com:8086"
#define INFLUXDB_TOKEN "yxVWTdwdkodt49ZA7c7roFJpXqMQ1zyvWx3Y6GtSs6_34TF4TIFO6G9Kq8B_qK3F354WBm_yFmY_BS2vHsUbXQ=="
#define INFLUXDB_ORG "palananda@webmail.npru.ac.th"
#define INFLUXDB_BUCKET "Data_ESP"

// Set timezone string according to https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
#define TZ_INFO "PKT-5"

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data points
Point sensor("measurements");

void setup() {
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);
  dht.begin();
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
 
  // Add tags
  sensor.addTag("device", DEVICE);
  sensor.addTag("SSID", WiFi.SSID());
  
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  // Store measured values into points
  sensor.clearFields();

  humidity = dht.readHumidity();
  temperature_Celsius = dht.readTemperature();

  sensor.addField("Temperature",temperature_Celsius);
  sensor.addField("Humidity",humidity);
  
  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));

  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  Serial.println("");
  Serial.println("Delay 10s");
  delay(10000);
}