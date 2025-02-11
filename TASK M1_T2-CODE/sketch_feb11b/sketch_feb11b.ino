const int pirPin = 2;
const int ledPin = 13;

volatile int pirState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetected, CHANGE);
}

void loop() {
}

void motionDetected() {
  pirState = digitalRead(pirPin);
  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion detected! LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No motion. LED OFF");
  }
}