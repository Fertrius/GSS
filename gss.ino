/*
   Generator auto start with power Source Switching (GSS) by
   Fertrius
   stardate: 202010191815 IF
*/

//  INPUTS
const int outside = 6;  //  outside   - main power line control
const int inside = 7; //  inside    - generator power line control

//  OUTPUTS SERVO
const int airpump = 5;  //  airpump   - air pump on generator needs to be closed during startup

//  OUTPUTS TO 4-RELAY
const int swoutside = 1;  //  swoutside - connect/disconnect main power contartor
const int swinside = 2; //  swinside  - connect/disconnect generator power contartor
const int ignition = 3; //  ignition  - generator standby switch, switch it off to turn geneator off
const int starter = 4;  //  starter   - turns on generator, only few seonds for start sequnce

//  CONSTANTS
int out = 0;  //  main power
int ins = 0;  //  generator power
int sta = 0;  //  counter how many time generator try to start
int war = 0;  //  warning

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
  digitalWrite(swoutside, LOW); // NC mode
  digitalWrite(swinside, LOW);  // NO mode
}

void loop() {
  //-------------------------------------------------------------------------------------
  // READ DATA
  //-------------------------------------------------------------------------------------
  out = digitalRead(outside);
  ins = digitalRead(inside);

  //-------------------------------------------------------------------------------------
  //  SWITCH POWER TO OUTSIDE - switch off inside and switch on outside
  //-------------------------------------------------------------------------------------
  if (out == HIGH && ins == LOW)
  {
    digitalWrite(swinside, LOW);  //  turn off inside switch
    delay(1000);
    digitalWrite(swoutside, HIGH); //  turn on outside switch
  }

  //-------------------------------------------------------------------------------------
  //  OUTSIDE POWER LOSSE - TURN ON GENERATOR
  //-------------------------------------------------------------------------------------
  if (out == LOW && ins == LOW && sta < 3)
  {
    digitalWrite(ignition, HIGH); //  turn on ignition relay
    digitalWrite(airpump, HIGH);  //  close air pump
    delay(2000);
    digitalWrite(starter, HIGH);  //  switch starter on
    delay(2500);
    digitalWrite(starter, LOW); //  switch starter off
    delay(2500);
    digitalWrite(airpump, LOW); //  open air pump
    sta++;
  }

  //-------------------------------------------------------------------------------------
  //  WARNINGS
  //-------------------------------------------------------------------------------------
  if (sta >= 3)
  {
    war++;
    digitalWrite(ignition, LOW);  //  turn off generator
  }

  //-------------------------------------------------------------------------------------
  //  SWITCH POWER TO GENERATOR - switch off outside and switch on inside in 2 minutes
  //-------------------------------------------------------------------------------------
  if (out == LOW && ins == HIGH)
  {
    digitalWrite(swoutside, LOW); //  turn off outside switch
    delay(1000);                //  need to be set like told in geerators manual
    digitalWrite(swinside, HIGH); //  turn on inside switch
  }

  //-------------------------------------------------------------------------------------
  // OUTSIDE POWER RESTORED - switch off inside, switch on outside and turn off generator
  //-------------------------------------------------------------------------------------
  if (out == HIGH && ins == HIGH)
  {
    delay(2000);
    digitalWrite(swinside, LOW);  // turn of generator power line
    delay(2000);
    digitalWrite(ignition, LOW);  // turn off generator
    digitalWrite(swoutside, HIGH);  // turn on outside power line
    sta = 0;
  }

  //-------------------------------------------------------------------------------------
  //  RESET WARNING COUNTER
  //-------------------------------------------------------------------------------------
  if (out == HIGH && ins == LOW || out == LOW && ins == HIGH)
  {
    war = 0;  //  reset warning counter
  }
}
