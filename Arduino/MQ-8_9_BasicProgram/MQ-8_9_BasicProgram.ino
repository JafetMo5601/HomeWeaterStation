const int MQ8_AOpin=0;
const int MQ9_AOpin=1;
const int MQ8_DOpin=8;
const int MQ9_DOpin=9;
int limit;
int value;

void setup() {
  Serial.begin(115200);
  pinMode(MQ8_DOpin, INPUT);
  pinMode(MQ9_DOpin, INPUT);
}

void loop()
{
  // MQ-8 variables
  value = analogRead(MQ8_AOpin);
  limit = digitalRead(MQ8_DOpin);
  // MQ-9 variables 
  int alarm = 0; 
  float sensor_volt; 
  float RS_gas; 
  float ratio; 
  float R0 = 0.11; 
  int sensorValue = analogRead(A1); 
  sensor_volt = ((float)sensorValue / 1024) * 5.0; 
  RS_gas = (5.0 - sensor_volt) / sensor_volt;
  ratio = RS_gas / R0;
  
  Serial.print("The current measure of hydrogen is: ");
  Serial.print(value);
  Serial.println(" ppm.");
  if (limit == 0){
    Serial.println("The levels of hydrogen are normal.\n");
  } else {
    Serial.println("The limit of hydrogen allowed was reached!\n");
  }
  Serial.print("Sensor_volt = "); 
  Serial.println(sensor_volt); 
  Serial.print("RS_ratio = "); 
  Serial.println(RS_gas); 
  Serial.print("Rs/R0 = "); 
  Serial.println(ratio); 
  alarm = digitalRead(MQ9_DOpin); 
  if (alarm == 0){
    Serial.println("The levels of MO are normal.\n\n");
  } else if (alarm == 1){
    Serial.println("The limit of MO allowed was reached!\n\n");
  }
  delay(1000);
}
