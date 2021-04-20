#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define MQ2pin (0)
int smoke[3];

RF24 radio(9, 8);

const uint64_t pipe = 0xE8E8F0F0E1LL;
int MQ2_SensorValue;

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}
void loop()
{
  MQ2_SensorValue = analogRead(MQ2pin);
  smoke[0] = MQ2_SensorValue;
  radio.write(smoke, 3);
  delay(2000);
}
