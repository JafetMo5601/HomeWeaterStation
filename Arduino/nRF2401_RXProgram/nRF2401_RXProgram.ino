#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;
const int MQ8_AOpin=0;
const int MQ9_AOpin=1;
const int MQ8_DOpin=7;
const int MQ9_DOpin=6;
const float R0 = 0.11;

int smoke[3];

RF24 radio(9, 8);

void setup(void)
{
  Serial.begin(9600); 
  
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  pinMode(MQ8_DOpin, INPUT);
  pinMode(MQ9_DOpin, INPUT);
}

int getMQ8Values(){
  int value = analogRead(MQ8_AOpin);
  return value;
}

void getMQ8Alarm()
{
  int limit = digitalRead(MQ8_DOpin);
  MQ8Alarm(limit);  
}

void MQ8Alarm(int limitToCheck)
{
  if (limitToCheck == 0){
    Serial.println("The levels of hydrogen are normal.\n");
  } else {
    Serial.println("The limit of hydrogen allowed was reached!\n");
  }
}

int getSensorVoltMQ9(){
  float sensor_volt; 
  int sensorValue = analogRead(A1); 
  sensor_volt = ((float)sensorValue / 1024) * 5.0; 
  return sensor_volt;
}

int getRatioMQ9()
{
  float sensor_volt = getSensorVoltMQ9();
  float RS_gas; 
  float ratio; 
  RS_gas = (5.0 - sensor_volt) / sensor_volt;
  ratio = RS_gas / R0;
  return ratio;
}

void getMQ9Alarm()
{
  int alarm = 0;
  alarm = digitalRead(MQ9_DOpin); 
  MQ9Alarm(alarm);
}

void MQ9Alarm(int alarmToCheck){
  if (alarmToCheck == 0){
    Serial.println("The levels of MO are normal.\n");
  } else if (alarmToCheck == 1){
    Serial.println("The limit of MO allowed was reached!\n");
  }
}

void printOutput()
{
  int value = getMQ8Values();
  Serial.print("The current measure of hydrogen is: ");
  Serial.print(value);
  Serial.println(" ppm.");
  getMQ8Alarm();

  int sensor_volt = getSensorVoltMQ9();
  int ratio = getRatioMQ9();
  Serial.print("Sensor_volt = "); 
  Serial.println(sensor_volt); 
  Serial.print("Rs/R0 = "); 
  Serial.println(ratio); 
  getMQ9Alarm();
}

void loop(void)
{
  if (radio.available())
  {
    radio.read(&smoke[0], 3);
    Serial.print("\n\nThe current measure of smoke is: ");
    Serial.print(smoke[0]);
    Serial.print(" ppm."); 
    if(smoke[0] > 500)
    {
      Serial.print(" | Smoke detected!");
    }
    Serial.println("\n");
  }
  printOutput();
  delay(2000);
}
