/*
   GSS (Generator auto Start with power Switching) by
   Fertrius
*/

//  INPUTS
const int outside = 2;  //  outside   - main power line control

const int inside = 3; //  inside    - generator power line control

//  OUTPUTS SERVO
const int airpump = 4;  //  airpump   - air pump on generator needs to be closed during startup

//  OUTPUTS TO 4-RELAY
const int starter = 5;  //  starter   - turns on generator, only few seonds for start sequnce

const int ignition = 6; //  ignition  - generator standby switch, switch it off to turn geneator off

const int swoutside = 7;  //  swoutside - connect/disconnect main power contartor

const int swinside = 8; //  swinside  - connect/disconnect generator power contartor

//  CONSTANTS
int out = 0;  //  main power on(1)/off(0)

int ins = 0;  //  generator power on(1)/off(0)

int sta = 0;  //  counter how many time generator try to start

int war = 0;  //  warning

void setup() {
  pinMode(outside, INPUT);
  pinMode(inside, INPUT);
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
    delay(120000);
    digitalWrite(swinside, HIGH); //  turn on inside switch
  }
  
  //-------------------------------------------------------------------------------------
  // OUTSIDE POWER RESTORED - switch off inside, switch on outside and turn off generator
  //-------------------------------------------------------------------------------------
  if (out == HIGH && ins == HIGH)
  {
    digitalWrite(swinside, LOW);  // turn of generator power line
    delay(2000);  //  140ms maybe
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
