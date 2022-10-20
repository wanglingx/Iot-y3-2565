int sensorPin = A0;
int sensorValue;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  Serial.print("Analog Value : ");
  Serial.println(sensorValue);
  delay(1000);
}
