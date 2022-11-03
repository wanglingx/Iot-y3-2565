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
  //Connect Accesspoint
  #define WIFI_SSID "avocado"
  #define WIFI_PASSWORD "01162001"
  //Config Connection InfluxDB
 #define INFLUXDB_URL "https://europe-west1-1.gcp.cloud2.influxdata.com"
  #define INFLUXDB_TOKEN "VEe-z7GoJUWb-wCVe6iYf4bCAex2oOpOCCskQynkPrG-0y05XWsoVoTBPy5VZncUK14c6EpxvegENqQd8gdsfg=="
  #define INFLUXDB_ORG "6538cf76ff632f43"
  #define INFLUXDB_BUCKET "Data_esp"
  // Time zone info
  #define TZ_INFO "UTC7"
  // Declare InfluxDB client instance with preconfigured InfluxCloud certificate
  InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  // Declare Data point
  Point sensor("wifi_status");
    void setup() {
    Serial.begin(115200);
  // Setup wifi
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to wifi");
    while (wifiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
    }
    Serial.println();
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  }
  void loop() 
  {
     Serial.print("IP Address : ");
     Serial.println(WiFi.localIP()); 
    if (client.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }
  }
