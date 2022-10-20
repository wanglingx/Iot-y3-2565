const int e18Pin =3;
int statusVal = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(e18Pin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  statusVal = digitalRead(e18Pin);
  if(statusVal == LOW){
    Serial.println("Collection Detected. ");
  }else{
    Serial.println("No Collection Detected. ");
  }
}
