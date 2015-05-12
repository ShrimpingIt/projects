const int analogInPin = A0; // Analog input pin that the potentiometer/sensor is attached to
int sensorValue = 0;        // value read from the pot

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  delay(3);
}
