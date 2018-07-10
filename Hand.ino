/*
 * Hand
 * 
 * Code for controlling the hardware of the project
 * Reads the controller information from the rx pin, and move the fingers accordingly
 * 
 * Created by Paul Bersee
 */

#include <Servo.h>

#define THUMB 1
#define INDEXFINGER 2
#define MIDDLEFINGER 3
#define RINGFINGER 4
#define PINKFINGER 5

Servo thumb, ringfinger, pink, middlefinger, indexfinger; 

void setup() {
  Serial.begin(9600);

  //attach finger pins to the servo objects
  ringfinger.attach(11);
  pink.attach(10);
  thumb.attach(9);
  middlefinger.attach(6);
  indexfinger.attach(5);
}

void loop() {
  
  String buff;
  buff = Serial.readStringUntil('\n');

  //Does the same thing as buff[0].toInt(), but faster
  //Limits the amount of available fingers to 10
  byte finger = buff[0] - '0';
  
  //Reads all values after the ':' char, and converts it to a number
  byte value = buff.substring(2).toInt();
  
  Serial.println(buff);
  switch(finger){
    case THUMB:
      setThumb(value);
      break;
    case INDEXFINGER:
      setIndexfinger(value);
      break;
    case MIDDLEFINGER:
      setMiddlefinger(value);
      break;
    case RINGFINGER:
      setRingfinger(value);
      break;
    case PINKFINGER:
      setPink(value);
      break;
    default:
      break;
  }
}


void setThumb(byte x)
{
  //when servo set to 45, thumb is closed. when servo is 145, thumb is opened
  //same system applies to all other fingers
  byte val = map(x, 0, 255, 45, 145);
  thumb.write(val);
}

void setIndexfinger(byte x)
{
  byte val = map(x, 0, 255, 35, 155);
  indexfinger.write(val);
}

void setMiddlefinger(byte x)
{
  byte val = map(x, 0, 255, 0, 130);
  middlefinger.write(val);
}

void setRingfinger(byte x)
{
  byte val = map(x, 0, 255, 10, 120);
  ringfinger.write(val);
}

void setPink(byte x)
{
  byte val = map(x, 0, 255, 125, 10);
  pink.write(val);
}
