const int DO = 9; 
 
void setup() { 
  Serial.begin(9600); 
  pinMode(DO, INPUT); 
} 
 
void loop() { 
  int alarm = 0; 
  float sensor_volt; 
  float RS_gas; 
  float ratio; 
  float R0 = 0.11; 
  int sensorValue = analogRead(A1); 
  sensor_volt = ((float)sensorValue / 1024) * 5.0; 
  RS_gas = (5.0 - sensor_volt) / sensor_volt;
  ratio = RS_gas / R0;
 
  Serial.print("Sensor_volt = "); 
  Serial.println(sensor_volt); 
  Serial.print("RS_ratio = "); 
  Serial.println(RS_gas); 
  Serial.print("Rs/R0 = "); 
  Serial.println(ratio); 
  alarm = digitalRead(DO); 
  if (alarm == 0){
    Serial.println("The levels of MO are normal.\n");
  } else if (alarm == 1){
    Serial.println("The limit of MO allowed was reached!\n");
  }
  delay(1000);
}
