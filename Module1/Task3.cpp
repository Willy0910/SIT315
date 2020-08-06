volatile byte red, blue = 0;

void setup()
{
  // Setup Direction of pins on ports
  DDRD = B00000000; // Pin0-7 are inputs
  DDRB = B00001100; // Pin10,11 are outputs
  
  // Setup Interrupt
  PCICR |= 0b00000100; // Enable interrupts for port D (pin0-7)
  PCMSK2 |= 0b00001100; // Choose pin2,3 on port D to interrupt
  
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Waiting ...");
  delay(3000);
}

ISR(PCINT2_vect)
{
  red = PIND & B00001000; // Read the pin3 on port D
  blue = PIND & B00000100; // Read the pin2 on port D
  
  digitalWrite(10, blue);
  digitalWrite(11, red);
  
  if (red != 0)
	Serial.println("Red On ...");
  
  if (blue != 0)
    Serial.println("Blue On ...");
}
