/*
  Toggle the button (when pressed) using Interrupt
*/

// Pin definitions
const int buttonPin = 2;
const int ledPin = 13;

// Global variables
volatile int ledState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Define interrupt pin, callback function (ISR), and its mode
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggle, RISING);
  
  // RISING: 0 -> 1: when the button is pressed
  // FALLING: 1 -> 0: when let the button go off
}

void loop()
{
  Serial.println("Waiting...");
  delay(3000);
} 

// Interrupt function
void toggle()
{
  ledState = !ledState;
  
  // Initial buttonState = 0
  // Once pressed, ledState = !0 = 1, LED ON
  // Once pressed again, ledState = !1 = 0, LED OFF
  digitalWrite(ledPin, ledState);
  Serial.print("LED is "); Serial.println(ledState);
}
