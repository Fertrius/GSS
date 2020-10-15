
//  //  //  //  //  //  //  //  //  //  //  //  //  //
//  GSS (Generator auto Start with power Switching) by
//  Fertrius
//  //  //  //  //  //  //  //  //  //  //  //  //  //

//  ledr      - LED Red
//  ledy      - LED Yellow
//  ledg      - LED Green

const int local = 1       //  local     - outgoing power line control
const int outside = 2     //  outside   - main power line control
const int inside = 3      //  inside    - generator power line control
const int starter = 4     //  starter   - turns on generator, only few seonds for start sequnce
const int airpump = 5     //  airpump   - air pump on generator needs to be closed during startup
const int ignition = 6    //  ignition  - generator standby switch, switch it off to turn geneator off
const int swoutside = 7   //  swoutside - connect/disconnect main power contartor
const int swinside = 8    //  swinside  - connect/disconnect generator power contartor
const int buzzer = 12     //  buzzer    - buzzer, to see that it's alive and make a noice in garage
const int temp = 11       //  temp      - generator temperature
const int manual = 10     //  manual    - manual control, STOP button.
//  manual, STOP button switch system to state where power is from main power line and
//  all other items idle, generator turned off etc. Like it every day when geneator not needed.

int out = 0               //  main power on(1)/off(0)
int ins = 0               //  generator power on(1)/off(0)
int loc = 0               //  outgoing power on(1)/off(0)
int sta = 0               //  counter how many time generator try to start
int gon = 0               //  generator status online(1)/offline(0)
int man = 0               //  stop button on(1)/off(0)

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
