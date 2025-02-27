const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  

  startTimer(0.5);
}

void loop()
{}

void startTimer(double timerFrequency) {
  noInterrupts(); // Disable interrupts
  
  // Reset Timer1 control registers
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