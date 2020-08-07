#define indicator 13
volatile byte red, blue, green = 0;

void setup()
{
  // Setup Direction of pins on ports
  DDRD = B00000000; // Pin0-7 are inputs
  DDRB = B00111100; // Pin10-13 are outputs
  
  // Setup Interrupt
  PCICR |= 0b00000100; // Enable interrupts for port D (pin0-7)
  PCMSK2 |= 0b00011100; // Choose pin2,3,4 on port D to interrupt
  
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // 0.5 Hz = every 2 seconds = (16,000,000/((31249+1)*1024))
  OCR1A = 31249;
  
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  //Output Compare Match A Interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // CTC
  TCCR1B |= (1 << WGM12);
  
  
  interrupts();
  
  Serial.begin(9600);
}

void loop()
{
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(indicator, digitalRead(indicator) ^ 1);
  Serial.println("Blink every 2 seconds ...");
}

ISR(PCINT2_vect)
{
  red = PIND & B00001000; // Read the pin3 on port D
  blue = PIND & B00000100; // Read the pin2 on port D
  green = PIND & B00010000; // Read the pin 4 on port D
  
  digitalWrite(10, blue);
  digitalWrite(11, red);
  digitalWrite(12, green);
  
  if (red | blue | green != 0)
    Serial.println("Interrupted!");
}
