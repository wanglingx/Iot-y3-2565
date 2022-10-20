#include "DHT.h"
#define DHTPIN 4
#define ledRed 3
#define ledBlue 2
#define LEDTest 6
#define DHTTYPE DHT22

float temp_c;
float temp_f;
float humidity;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(ledRed,OUTPUT);
  pinMode(ledBlue,OUTPUT);
  pinMode(LEDTest,OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

// the loop function runs over and over again forever
void loop() { 
  temp_c = dht.readTemperature();
  temp_f = dht.readTemperature(true);
  humidity = dht.readHumidity();

  Serial.print("Temperature is ");
  Serial.print(temp_c);
  Serial.print(" C : : ");
  Serial.print(temp_f);
  Serial.print(" F >> Humidity ");
  Serial.print(humidity);
  Serial.println(" %");
  digitalWrite(LEDTest, LOW);
  delay(2000);

  if(temp_c > 30){
    Serial.print(temp_c);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, LOW);
  }
  if(temp_c < 26){
    Serial.print(temp_c);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
  }
  else{
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
  }
               // wait for a second
}
