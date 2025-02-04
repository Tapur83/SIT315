const int pirPin = 2;
const int ledPin = 13;

int pirState = LOW;
int pirValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  pirValue = digitalRead(pirPin);
  Serial.println(pirValue);

  if (pirValue == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion detected! LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No motion. LED OFF");
  }

  delay(100);
}