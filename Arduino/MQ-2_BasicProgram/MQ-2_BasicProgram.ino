#define MQ2pin (0)

float sensorValue;  //variable to store sensor value

void setup()
{
  Serial.begin(9600);
  Serial.println("Gas sensor warming up!");
  delay(20000);
}

void loop()
{
  sensorValue = analogRead(MQ2pin);
  
  Serial.print("The current measure of smoke is: ");
  Serial.print(sensorValue);
  Serial.print(" ppm.");
  
  if(sensorValue > 500)
  {
    Serial.print(" | Smoke detected!");
  }
  
  Serial.println("");
  delay(2000);
}
