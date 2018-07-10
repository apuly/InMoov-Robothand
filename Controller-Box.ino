/*
 * Controller Box
 * 
 * Read the input from the switches and potentiometers from the controller box and send it to the hand.
 * 
 * Fingers are set with values between 0 and 255, where 0 is finger closed and 255 is finger opened.
 * Converting the value is handled by Hand.ino.
 * 
 * Created by Paul Bersee
 */

#define THUMB_PIN 5
#define INDEXFINGER_PIN 4
#define MIDDLEFINGER_PIN 6
#define RINGFINGER_PIN 7
#define PINK_PIN 0
#define MODE0_PIN 8
#define MODE1_PIN 9

#define THUMB 1
#define INDEXFINGER 2
#define MIDDLEFINGER 3
#define RINGFINGER 4
#define PINKFINGER 5

byte lastMode;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  byte mode = selectMode();
  if (mode == 0){
    mode0Loop();
    lastMode = mode;
  } else if (mode == 1){
    mode1Loop();
    lastMode = mode;
  } else if (mode == 2){
    mode2Loop();
    lastMode = mode;
  }
  delay(100);
}

byte selectMode(){
  //sets the mode of the robotarm, based on a 3 mode switch
  byte mode;
  if (digitalRead(MODE0_PIN) == HIGH) {
    mode = 0;
  } else if (digitalRead(MODE1_PIN) == HIGH) {
    mode = 1;
  } else {
    mode = 2;
  }
  return mode;
}

void mode0Loop(){
  if (lastMode != 0){ //check if this is the first time entering the loop
    openHand();
    setFinger(THUMB, 80);
  }
  int d = 1000;
  setFinger(PINKFINGER, 0);
  setFinger(INDEXFINGER, 255);
  delay(d);
  setFinger(INDEXFINGER, 0);
  setFinger(MIDDLEFINGER, 255);
  delay(d);
  setFinger(MIDDLEFINGER, 0);
  setFinger(RINGFINGER, 255);
  delay(d);
  setFinger(RINGFINGER, 0);
  setFinger(PINKFINGER, 255);
  delay(d);
}

void mode1Loop(){
  setFinger(THUMB,        analogRead2byte(analogRead(THUMB_PIN)));
  setFinger(INDEXFINGER,  analogRead2byte(analogRead(INDEXFINGER_PIN)));
  setFinger(MIDDLEFINGER, analogRead2byte(analogRead(MIDDLEFINGER_PIN)));
  setFinger(RINGFINGER,   analogRead2byte(analogRead(RINGFINGER_PIN)));
  setFinger(PINKFINGER,   analogRead2byte(analogRead(PINK_PIN)));  
}

void mode2Loop(){
  closeHand();
}


void openHand(){
  setFinger(THUMB, 255);
  setFinger(INDEXFINGER, 255);
  setFinger(MIDDLEFINGER, 255);
  setFinger(RINGFINGER, 255);
  setFinger(PINKFINGER, 255);
}

void closeHand(){
  setFinger(THUMB,        0);
  setFinger(INDEXFINGER,  0);
  setFinger(MIDDLEFINGER, 0);
  setFinger(INDEXFINGER,  0);
  setFinger(PINKFINGER,   0);
}

byte analogRead2byte(int analogval){
  //analogRead returns 10 bit number.
  //right swifting twice makes it fit in a byte
  return analogval >> 2;
}

void setFinger(short fingerindex, byte val){
  //Output format is "<finger index>:<finger value>\n"
  String out = String(fingerindex) + ':' + String(val) + '\n';
  Serial.print(out);
}
