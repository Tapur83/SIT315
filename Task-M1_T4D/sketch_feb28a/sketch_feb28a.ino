#include <avr/io.h>
#include <avr/interrupt.h>

// Pin Definitions
const int lightSensorPin = A0;  // Ambient light sensor connected to A0
const int ledPin = 11;          // LED connected to D11
#define TILT_PIN 3
#define TILT_LED_PIN 12
#define PIR_PIN 2
#define PIR_LED_PIN 13

// Threshold for ambient light (adjust as needed)
const int lightThreshold = 300;

// Variables to store sensor values and LED states
volatile int lightValue = 0;
volatile bool ledState = false;
volatile bool tiltState = LOW;
volatile bool pirState = LOW;

// Timer interrupt setup
void setupTimer() {
  // Set Timer1 to normal mode
  TCCR1A = 0; // Clear Timer1 control register A
  TCCR1B = 0; // Clear Timer1 control register B

  // Set prescaler to 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Initialize Timer1 counter to 0
  TCNT1 = 0;

  // Enable Timer1 overflow interrupt
  TIMSK1 |= (1 << TOIE1);
}

// Timer1 overflow interrupt service routine
ISR(TIMER1_OVF_vect) {
  // Read the ambient light sensor value
  lightValue = analogRead(lightSensorPin);

  // Control the LED based on the light sensor value
  if (lightValue > lightThreshold) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    ledState = true;
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED
    ledState = false;
  }

  // Reset Timer1 counter
  TCNT1 = 0;
}

// Tilt sensor interrupt service routine
void tiltChanged() {
  tiltState = digitalRead(TILT_PIN);
  digitalWrite(TILT_LED_PIN, tiltState);
  if (tiltState == HIGH) {
    Serial.println("Tilt sensor: OFF (upright position).");
  } else {
    Serial.println("Tilt sensor: ON (tilted position).");
  }
}

// PIR sensor interrupt service routine
void motionDetected() {
  pirState = digitalRead(PIR_PIN);
  digitalWrite(PIR_LED_PIN, pirState);
  if (pirState == HIGH) {
    Serial.println("Motion detected! PIR LED ON.");
  } else {
    Serial.println("No motion. PIR LED OFF.");
  }
}

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Set the LED pins as outputs
  pinMode(ledPin, OUTPUT);
  pinMode(TILT_LED_PIN, OUTPUT);
  pinMode(PIR_LED_PIN, OUTPUT);

  // Set the sensor pins as inputs
  pinMode(lightSensorPin, INPUT);
  pinMode(TILT_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);

  // Set up the timer interrupt
  setupTimer();

  // Attach external interrupts
  attachInterrupt(digitalPinToInterrupt(TILT_PIN), tiltChanged, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), motionDetected, CHANGE);

  // Enable global interrupts
  sei();

  Serial.println("System initialized. Tilt the sensor or move to see changes.");
}

void loop() {
  // Print the sensor values and LED states to the Serial Monitor
  Serial.print("Light Sensor Value: ");
  Serial.print(lightValue);
  Serial.print(" | LED State: ");
  Serial.println(ledState ? "ON" : "OFF");

  // Delay for stability (adjust as needed)
  delay(500);
}