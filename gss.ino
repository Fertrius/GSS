

//  //  //  //  //  //  //  //  //  //  //  //  //  //
//  GSS (Generator auto Start with power Switching) by
//  Fertrius
//  //  //  //  //  //  //  //  //  //  //  //  //  //

//  ledr      - LED Red
//  ledy      - LED Yellow
//  ledg      - LED Green

const int local = 1;              //  local     - outgoing power line control
const int outside = 2;            //  outside   - main power line control
const int inside = 3;             //  inside    - generator power line control
const int starter = 4;            //  starter   - turns on generator, only few seonds for start sequnce
const int airpump = 5;            //  airpump   - air pump on generator needs to be closed during startup
const int ignition = 6;           //  ignition  - generator standby switch, switch it off to turn geneator off
const int swoutside = 7;          //  swoutside - connect/disconnect main power contartor
const int swinside = 8;           //  swinside  - connect/disconnect generator power contartor
const int buzzer = 12;            //  buzzer    - buzzer, to see that it's alive and make a noice in garage
const int temperature = 11;       //  temp      - generator temperature
const int manual = 10;            //  manual    - manual control, STOP button.
//  manual, STOP button switch system to state where power is from main power line and
//  all other items idle, generator turned off etc. Like it every day when geneator not needed.
//  Lets call it default state.

int out = 0;                      //  main power on(1)/off(0)
int ins = 0;                      //  generator power on(1)/off(0)
int loc = 0;                      //  outgoing power on(1)/off(0)
int sta = 0;                      //  counter how many time generator try to start
int gon = 0;                      //  generator status online(1)/offline(0)
int man = 0;                      //  stop button on(1)/off(0)
int tem = 0;                      //  generator temperature

void setup() {
  pinMode(local, INPUT);
  pinMode(outside, INPUT);
  pinMode(inside, INPUT);
  pinMode(starter, OUTPUT);
  pinMode(airpump, OUTPUT);
  pinMode(ignition, OUTPUT);
  pinMode(swoutside, OUTPUT);
  pinMode(swinside, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(temperature, INPUT);
  pinMode(manual, INPUT);

  // set default state parameters
  digitalWrite(ignition, LOW);
  digitalWrite(airpump, LOW);
  digitalWrite(swoutside, HIGH);
  digitalWrite(swinside, LOW);
  /* digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000); */
}

void loop() {
  loc = digitalRead(local);
  out = digitalRead(outside);
  ins = digitalRead(inside);
  tem = digitalRead(temperature);

  if (loc == LOW && out == LOW && ins == LOW && sta != 3)
  {
    /* if (sta == 0)
    {
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
    } */
    digitalWrite(ignition, HIGH);               //  relay, so it can be at this state all time when geneator needs to work
    digitalWrite(airpump, HIGH);                //  close air pump
    digitalWrite(swoutside, LOW);               //  generator starter on
    delay(2000);
    digitalWrite(starter, HIGH);
    delay(2500);
    digitalWrite(starter, LOW);                 //  generator starter off
    delay(2500);
    digitalWrite(airpump, LOW);                 // open air pump
    sta++;
  }
  if (loc == HIGH && out == HIGH && ins == LOW && sta != 3)
  {
  sta == 0;
  }
}
