#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
//Config DHT
#include "DHT.h"
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   
 //Connect Accesspoint
#define WIFI_SSID "avocado"
#define WIFI_PASSWORD "01162001"
//Config Connection InfluxDB
 #define INFLUXDB_URL "https://europe-west1-1.gcp.cloud2.influxdata.com"
  #define INFLUXDB_TOKEN "TMy1dPFe251bvuvC6ducp8KY26OcrUqI9hFF4br92sslfLFIyey9oi_dWiCphYQZydIxHQCl0mBAQVibM1K4Hg=="
  #define INFLUXDB_ORG "6538cf76ff632f43"
  #define INFLUXDB_BUCKET "Data_ESP"
  // Time zone info
  #define TZ_INFO "UTC7"
// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
// Create your Data Point here
Point sensor("climate");
// Set up the DHT connection
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
// Setup wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  // Add tags. Here we will track which device our data is coming from
  sensor.addTag("device", DEVICE);
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
}

void loop() {
 sensor.clearFields();
// Check server connection
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP()); 
    if (client.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }
   float h = dht.readHumidity();
  float t = dht.readTemperature();
  sensor.addField("humidity_Val", h);
  sensor.addField("temp_Val", t);
  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());
  // If no Wifi signal, try to reconnect it
  if ((WiFi.RSSI() == 0) && (wifiMulti.run() != WL_CONNECTED)) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  Serial.println("Wait 10s");
  delay(5000);
}