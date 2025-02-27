const byte LED_PIN = 13;
const byte METER_PIN = A4;
const double MIN_FREQUENCY = 0.1; 
const double MAX_FREQUENCY = 10.0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
 
  updateTimerFrequency();
}

void loop()
{  
  updateTimerFrequency();
  delay(100); // Small delay to avoid excessive updates
}

void updateTimerFrequency() {
  
  int potValue = analogRead(METER_PIN);
  
  double timerFrequency = map(potValue, 0, 1023, MIN_FREQUENCY * 1000, MAX_FREQUENCY * 1000) / 1000.0;
  
  startTimer(timerFrequency);
  
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(", Frequency: ");
  Serial.print(timerFrequency);
  Serial.println(" Hz");
}

void startTimer(double timerFrequency) {
  noInterrupts(); 
  
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  
  unsigned long prescaler = 1024;
  unsigned long timerCount = (F_CPU / (prescaler * timerFrequency)) - 1;
  
  
  if (timerCount > 65535) {
    Serial.println("Error: Frequency too low for Timer1 with prescaler 1024.");
    return;
  }
 
  OCR1A = timerCount;
  
  TCCR1B |= (1 << WGM12);
  
  TCCR1B |= (1 << CS12) | (1 << CS10);
 
  TIMSK1 |= (1 << OCIE1A);
  interrupts(); // Enable interrupts
}

ISR(TIMER1_COMPA_vect) {
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1); // Toggle the LED
}