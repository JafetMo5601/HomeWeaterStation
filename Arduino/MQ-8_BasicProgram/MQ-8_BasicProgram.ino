const int AOpin=0;
const int DOpin=8;
int limit;
int value;

void setup() {
  Serial.begin(115200);
  pinMode(DOpin, INPUT);
}

void loop()
{
  value = analogRead(AOpin);
  limit = digitalRead(DOpin);
  Serial.print("The current measure of hydrogen is: ");
  Serial.print(value);
  Serial.println(" ppm.");
  if (limit == 0){
    Serial.println("The levels of hydrogen are normal.\n");
  } else {
    Serial.println("The limit of hydrogen allowed was reached!\n");
  }
  delay(1000);
}
