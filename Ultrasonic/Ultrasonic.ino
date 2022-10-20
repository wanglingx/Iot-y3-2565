const unsigned int TRIG_PIN=4;
const unsigned int ECHO_PIN=2;
int ledPin1 = 8;
int ledPin2 = 9;
int ledPin3 = 10;
int ledPin4 = 11;
int con = ((450 * 29.1)/74)/4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 74;

  if(distance < con ){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED ON 1");
    Serial.println();
  }
  else if(distance < con*2){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED ON 1,2");
    Serial.println();
  }
  else if(distance < con*3){
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

  Serial.println(duration);
  Serial.println(distance);
  Serial.println();
  delay(1500);
}
