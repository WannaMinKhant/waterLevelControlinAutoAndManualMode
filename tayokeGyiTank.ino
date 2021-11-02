
int trig = 12; // for ultrasonic trig
int echo = 11; // for ultrasonic echo
int push = 8; // for push button
int switchB = 7; // for on off switch
int relay = 9; // for relay
int ledMred = 6;
int ledMgreen = 5;
int led_pump_on = 4;
int led_low = 3;
int led_full = 2;

int manualMode;
float water level;
int onOffMode;

bool changeMode = false;
bool runPoint = false;


void setup() {
  //first declare pin for our usage

  pinMode(INPUT, echo); // for ultrasonic echo is input pin for nano
  pinMode(INPUT, push); // to detect push button is activated and is for input for nano
  pinMode(INPUT, switchB); // manual on/off for pump and is input for nano

  pinMode(OUTPUT, trig); //for ultrasonic trig is output pin for nano
  pinMode(OUTPUT, relay); // to drive pump
  pinMode(OUTPUT, ledMred);
  pinMode(OUTPUT, ledMgreen);
  pinMode(OUTPUT, led_pum_on);
  pinMode(OUTPUT, led_low);
  pinMode(OUTPUT, led_full);

}

void loop() {
  level = getLevel(trig, echo);
  manualMode = digitalRead(push);
  if (manualMode == 1) {
    changeMode = !changeMode;
  }

  if (changeMode) {
    digitalWrite(ledMred, HIGH);
    digitalWrite(ledMgreen, LOW);
    onOffMode = digitalRead(switchB); // reading on/off mode switching

    // 
    if (onOffMode == 1) { // switching on 
      runPoint = true;
    } else {              // switching off
      runPoint = false;
    }

  } else {
    digitalWrite(ledMred, LOW);
    digitalWrite(ledMgreen, HIGH);
    // water is low and pump is running
    if (level < 31) {
      runPoint = true;
    }
    // full state in stop pump
    if (level > 110) {
      runPoint = false;
    }
  }
  RunningMode(level);
}


// it will give distance value in cm, so we estiamte in 30 cm may be 1 foot;
float getLevel(int Tx, int Rx)
{
  float distance = 0;
  float duration;
  digitalWrite(Tx, LOW);
  delayMicroseconds(2);
  digitalWrite(Tx, HIGH);
  delayMicroseconds(3);

  duration = pulseIn(Rx, HIGH);
  distance = (duration / 2) / 28.57;
  return distance;
}

void RunningMode(level lvl) {
  if (runPoint) {
    digitalWrite(relay, HIGH);
    digitalWrite(led_low, HIGH);
    digitalWrite(led_pump_on, HIGH);
    digitalWrite(led_full, LOW);
  } else if( !runPoint || lvl > 110){
    digitalWrite(relay, LOW);
    digitalWrite(led_low, LOW);
    digitalWrite(led_pump_on, LOW);
    digitalWrite(led_full, HIGH);
  }
}
