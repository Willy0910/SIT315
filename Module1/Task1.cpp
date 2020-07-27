/*
  Read the motion sensor state,
  Light the LED and write "Sensor Activated!" when detected
*/

int sensorState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // digitalRead: Read the value from the digital pin 7, either HIGH or LOW
  sensorState = digitalRead(2);
  
  // If the motion sensor is activated, the sensorState is HIGH
  if (sensorState == HIGH) {
    // digitalWrite: Set the digital pin 13 (LED) ON (HIGH)
    digitalWrite(13, HIGH);
    Serial.println("Sensor Activated!");
    delay(1000);
  } else {
    digitalWrite(13, LOW);
    Serial.println("Not Detected :(");
    delay(1000);
  }
  
  delay(10); // Delay a little bit to improve simulation performance
}
