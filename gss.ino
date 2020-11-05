/*
   Generator auto start with power Source Switching (GSS) by
   Fertrius
   stardate: 20201106-001750
*/

// TEMPERATURE
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int deviceCount = 0;
float tempC0;
float tempC1;

//  INPUTS
const int outside = 8;  //  outside   - main power line control
const int inside = 9; //  inside    - generator power line control

//  OUTPUTS SERVO
const int airpump = 6;  //  airpump   - air pump on generator needs to be closed during startup

//  OUTPUTS TO 4-RELAY
const int swoutside = 2;  //  swoutside - connect/disconnect main power contartor
const int swinside = 3; //  swinside  - connect/disconnect generator power contartor
const int ignition = 4; //  ignition  - generator standby switch, switch it off to turn geneator off
const int starter = 5;  //  starter   - turns on generator, only few seonds for start sequnce

//  CONSTANTS
int out = 0;  //  main power
int ins = 0;  //  generator power
int sta = 0;  //  starter counter - show many time generator try to start
int war = 0;  //  warning counter - show waring light

void setup() {
  pinMode(outside, INPUT);
  pinMode(inside, INPUT);
  pinMode(airpump, OUTPUT);
  pinMode(starter, OUTPUT);
  pinMode(ignition, OUTPUT);
  pinMode(swoutside, OUTPUT);
  pinMode(swinside, OUTPUT);
  digitalWrite(ignition, LOW);
  digitalWrite(airpump, LOW);
  digitalWrite(swoutside, HIGH); // NC mode
  digitalWrite(swinside, LOW);  // NO mode
  Serial.begin(9600);

  // TEMPERATURE
  sensors.begin();
  tempC0 = sensors.getTempCByIndex(0);
  tempC1 = sensors.getTempCByIndex(1);
  Serial.println("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount);
  Serial.println(" devices");
}

void loop() {
  Serial.println(">>> NEW LOOP START <<<");
  
  // TEMPERATURE
  sensors.requestTemperatures();
  Serial.print("Temperature is: ");
  Serial.print(tempC0);
  Serial.print(" \xC2\xB0");
  Serial.print("C | ");
  Serial.print(tempC1);
  Serial.print(" \xC2\xB0");
  Serial.println("C");
  
  // READ DATA
  out = digitalRead(outside);
  ins = digitalRead(inside);
  Serial.println("INPUTS: ");
  Serial.print("OUTSIDE = ");
  Serial.println(out);
  Serial.print("INSIDE = ");
  Serial.println(ins);
  Serial.print("STARTER = ");
  Serial.println(sta);
  Serial.print("WARNING = ");
  Serial.println(war);
  Serial.print("STATUS: ");

  //  POWER FROM OUTSIDE
  if (out == HIGH && ins == LOW)
  {
    Serial.println("power from outside");
    digitalWrite(swinside, LOW);  //  turn off inside switch
    delay(2000);
    digitalWrite(swoutside, HIGH); //  turn on outside switch
    digitalWrite(ignition, LOW);  //  turn off ignition
  }

  //  OUTSIDE POWER LOSSE
  if (out == LOW && ins == LOW && sta < 3)
  {
    Serial.println("turn on generator");
    digitalWrite(swoutside, LOW); //  turn off outside switch
    digitalWrite(swinside, LOW);  //  turn off inside switch
    digitalWrite(ignition, HIGH); //  turn on ignition
    digitalWrite(airpump, HIGH);  //  close air pump
    delay(2000);
    digitalWrite(starter, HIGH);  //  switch starter on
    delay(2000);
    digitalWrite(starter, LOW); //  switch starter off
    delay(2000);
    digitalWrite(airpump, LOW); //  open air pump
    delay(2000);  //  need to be set like told in geerators manual
    sta++;
  }

  //  WARNINGS
  if (sta >= 3)
  {
    Serial.println("war++");
    war++;
    delay(2000);
    digitalWrite(swoutside, HIGH);  //  turn on outside switch
    digitalWrite(LED_BUILTIN, HIGH);
  }

  //  SWITCH POWER TO GENERATOR - switch off outside and switch on inside in 2 minutes
  if (out == LOW && ins == HIGH)
  {
    Serial.println("switch to inside");
    digitalWrite(ignition, HIGH); //  turn on ignition relay
    digitalWrite(swoutside, LOW); //  turn off outside switch
    delay(2000);
    digitalWrite(swinside, HIGH); //  turn on inside switch
  }

  // OUTSIDE POWER RESTORED - switch off inside, switch on outside and turn off generator
  if (out == HIGH && ins == HIGH)
  {
    Serial.println("outside restored");
    delay(2000);
    digitalWrite(swinside, LOW);  // turn of generator power line
    delay(2000);
    digitalWrite(ignition, LOW);  // turn off generator
    digitalWrite(swoutside, HIGH);  // turn on outside power line
  }

  //  RESET WARNING COUNTER
  if (out == HIGH && ins == LOW || out == LOW && ins == HIGH || out == HIGH && ins == HIGH)
  {
    Serial.println("war/sta reset");
    war = 0;  //  reset warning counter
    sta = 0;  //  reset starter counter
    digitalWrite(LED_BUILTIN, LOW);
  }
}
