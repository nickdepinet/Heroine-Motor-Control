
#include <Sabertooth.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
char xbGet[2];

SoftwareSerial xbee = SoftwareSerial(rxPin, txPin);
Sabertooth ST(128); 

void setup()
{
  Serial.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  xbee.begin(9600);  
  ST.drive(0); // The Sabertooth won't act on mixed mode packet serial commands until
  ST.turn(0);  // it has received power levels for BOTH throttle and turning, since it
               // mixes the two together to get diff-drive power levels for both motors.
}

void loop()
{
  int power;
  if (xbee.available() >= 2) {
    for (int i = 0; i <= 1; i++) {
      xbGet[i] = xbee.read();
    }
    xbGet[2] = '\0';
  }
  while (strcmp(xbGet, "LT")  == 0) {      
    ST.turn(-127);
    if (xbee.available() >= 2) {
    for (int i = 0; i <= 1; i++) {
      xbGet[i] = xbee.read();
    }
    xbGet[2] = '\0';
    }
  }
  while (strcmp(xbGet, "RT")  == 0) {      
    ST.turn(127);
    if (xbee.available() >= 2) {
    for (int i = 0; i <= 1; i++) {
      xbGet[i] = xbee.read();
    }
    xbGet[2] = '\0';
    }
  }
  if (strcmp(xbGet, "ST")  == 0) {      
    ST.turn(0);
  }
  while (strcmp(xbGet, "FG")  == 0) {      
    ST.drive(127);
    if (xbee.available() >= 2) {
    for (int i = 0; i <= 1; i++) {
      xbGet[i] = xbee.read();
    }
    xbGet[2] = '\0';
    }
  }
  if (strcmp(xbGet, "BG")  == 0) {      
    ST.drive(-127);
    if (xbee.available() >= 2) {
    for (int i = 0; i <= 1; i++) {
      xbGet[i] = xbee.read();
    }
    xbGet[2] = '\0';
    }
  }
  if (strcmp(xbGet, "SG")  == 0) {      
    ST.drive(0);
  }
}
