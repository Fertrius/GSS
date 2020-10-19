/*
   Generator auto start with power Source Switching (GSS) by
   Fertrius
   stardate: 202010192037 IF-ELSE
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

  out = digitalRead(outside);
  ins = digitalRead(inside);


  if (out == HIGH && ins == LOW)
  {
    digitalWrite(swinside, LOW);
    digitalWrite(swoutside, HIGH);
  }
  else if (out == LOW && ins == HIGH)
  {
    digitalWrite(swoutside, LOW);
    digitalWrite(swinside, HIGH);
  }
  else if (out == LOW && ins == LOW && sta < 3)
  {
    digitalWrite(ignition, HIGH); //  turn on ignition relay
    digitalWrite(airpump, HIGH);  //  close air pump
    digitalWrite(starter, HIGH);  //  switch starter on
    digitalWrite(starter, LOW); //  switch starter off
    digitalWrite(airpump, LOW); //  open air pump
    sta++;
  }
  else
  {
    digitalWrite(swinside, LOW);  // turn of generator power line
    digitalWrite(ignition, LOW);  // turn off generator
    digitalWrite(swoutside, HIGH);  // turn on outside power line
    sta = 0;
  }
}
