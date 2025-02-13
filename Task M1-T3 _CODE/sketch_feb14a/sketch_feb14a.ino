#define TILT_PIN 3
#define TILT_LED_PIN 12
#define PIR_PIN 2
#define PIR_LED_PIN 13

volatile bool tiltState = LOW;
volatile bool pirState = LOW;

void setup() {
  pinMode(TILT_LED_PIN, OUTPUT);
  pinMode(PIR_LED_PIN, OUTPUT);
  pinMode(TILT_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(TILT_PIN), tiltChanged, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), motionDetected, CHANGE);
  Serial.println("System initialized. Tilt the sensor or move to see changes.");
}

void loop() {
}

void tiltChanged() {
  tiltState = digitalRead(TILT_PIN);
  digitalWrite(TILT_LED_PIN, tiltState);
  if (tiltState == HIGH) {
    Serial.println("Tilt sensor: OFF (upright position).");
  } else {
    Serial.println("Tilt sensor: ON (tilted position).");
  }
}

void motionDetected() {
  pirState = digitalRead(PIR_PIN);
  digitalWrite(PIR_LED_PIN, pirState);
  if (pirState == HIGH) {
    Serial.println("Motion detected! PIR LED ON.");
  } else {
    Serial.println("No motion. PIR LED OFF.");
  }
}