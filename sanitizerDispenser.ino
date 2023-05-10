/*
 * code for sanitizer dispenser
 * assignment 2 SIT123
 * by Janvi Gupta
 */

//include libraries
#include <SD.h>
#include <SPI.h>
#include <Servo.h>

#define blueWire 7 //trigger pin from the sensor - blue wire
#define purpleWire 6                                                                 
Servo servomotor; 

void setup() {
Serial.begin(9600); //passing value to speed parameter

//setting digital pins as outputs
pinMode(blueWire, OUTPUT);
pinMode(purpleWire, INPUT);

servomotor.attach(3); //servo attachment pin
servomotor.write(0);
}

void loop() 
{
long duration, distance; //variables
digitalWrite(blueWire, LOW); //low voltage level
delayMicroseconds(2);
digitalWrite(blueWire, HIGH); //high voltage level
delayMicroseconds(10);
digitalWrite(blueWire, LOW);
duration = pulseIn(purpleWire, HIGH);
distance = (duration/2) / 29.1; //obtain distance

if (distance < 10) //if the distance is less than 10cms
{
  Serial.println("active");
  Serial.println(distance);
  servomotor.write(90); //moves the servo at a 90 degree angle
  delay(2000); //delays be 2 seconds
  servomotor.write(0); //servo moves back to a 0 degree angle this pulls the pump back up
}
else
{    
  Serial.println("inactive");
}

delay(1000); //delay by 1 second
}
