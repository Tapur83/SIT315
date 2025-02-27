const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  
  startTimer();
}

void loop()
{}

void startTimer(){
  noInterrupts(); // Disable interrupts
  
  // Reset Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  
  OCR1A = 31249; 
  
  TCCR1B |= (1 << WGM12);
  
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  TIMSK1 |= (1 << OCIE1A);
  
  interrupts(); // Enable interrupts
}

ISR(TIMER1_COMPA_vect){
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1); // Toggle the LED
}