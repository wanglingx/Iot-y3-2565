int ledPin1 = 3;
int ledPin2 = 4;
int ledPin3 = 5;
int ledPin4 = 6;
int con = 1023/4;
int analogPin = 5;
int val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analogPin);
  Serial.print("LDR = ");
  Serial.println(val);

  if(val < con ){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED ON 1");
    Serial.println();
  }
  else if(val < con*2){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED ON 1,2");
    Serial.println();
  }
  else if(val < con*3){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED ON 1,2,3");
    Serial.println();
  }
  else{
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    Serial.println("LED ON 1,2,3,4");
    Serial.println();
  }
  delay(1000);
}
