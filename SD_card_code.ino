/*
 * code for sanitizer dispenser
 * includes the SD card initialisaiton code
 * by Janvi Gupta
 */

//include libraries
#include <SD.h>
#include <SPI.h>
#include <Servo.h>

File sanitizerDispenser;

Sd2Card card;

#define blueWire 7 //trigger pin from the sensor - blue wire
#define purpleWire 6                                                                 
Servo servo; 
const int chipSelect = 10;

void setup() {
Serial.begin(9600); //passing value to speed parameter

//setting digital pins as outputs
pinMode(blueWire, OUTPUT);
pinMode(purpleWire, INPUT);

servo.attach(3); //servo attachment pin
servo.write(0);

//intiialise sd card
if(SD.begin())
{
  Serial.println("card is ready to use");
}
else
{
  Serial.println("card not initalised");
  return;
}

sanitizerDispenser = SD.open("example.txt", FILE_WRITE);
if(sanitizerDispenser)
{
  sanitizerDispenser.println("working on file");
  sanitizerDispenser.close();
}
else
{
  Serial.println("error opening file");
}

if(SD.begin())
while(!Serial)
{
  ;
}
Serial.println("initalising SD card");
if(!card.init(SPI_HALF_SPEED, chipSelect))
{
  Serial.println("sd card not initalised");
  while(1);
}
else
{
  Serial.println("sd card ready to use - has been initialised");
}

sanitizerDispenser = SD.open("example.txt", FILE_WRITE);
sanitizerDispenser.close();

if (SD.exists("emample.txt"))
{
  Serial.println("example.txt exists");
}
else
{
  Serial.println("file doesn't exist");
}

}

void loop() 
{

sanitizerDispenser = SD.open("example.txt", FILE_WRITE);
if(sanitizerDispenser)
{
  Serial.println("writing to file");
  sanitizerDispenser.println("is a test file");
}
else
{
  Serial.println("error opening test.tst");
}
delay(1000);

long duration, distance;
digitalWrite(blueWire, LOW); //low voltage level
delayMicroseconds(2);
digitalWrite(blueWire, HIGH); //high voltage level
delayMicroseconds(10);
digitalWrite(blueWire, LOW);
duration = pulseIn(purpleWire, HIGH);
distance = (duration/2) / 29.1;

if (distance < 10) //if the distance is less than 10cms
{
  Serial.println("active");
  Serial.println(distance);
  servo.write(90); //moves the servo at a 90 degree angle
  delay(2000); //delays be 3 seconds
  servo.write(0); //servo moves back to a 0 degree angle this pulls the pump back up
}
else
{    
  Serial.println("inactive");
}
delay(500);

}
