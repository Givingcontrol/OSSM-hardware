//
//
//Based on accellStepper demo - Make a single stepper bounce from one limit to another
//
//Modified to work with OSSM sex machine
//
//This is a very simple method of control that only updates the speed and stroke after each move completes
//This means it responds to potentiometer changes at each end of stroke.
//
//

#include <AccelStepper.h>

#define enable 12
String myString;
int speed;

const int analogSpeedPin = A0;//connect your potentiometer for speed here
//const int analogStrokePin = A1;//connect your potentiometer for stroke length here

//you will need to change these parameters based on your stroke length, stepper capability, and step resolution
//if stepper is skipping while moving, lower max speed
//if stroke is too short, increase strokeLimit
//if speed and stroke are low, increase both (likely variance in microsteps) These settings were used with 200 steps/rev, but with cheap driver this will be noisy
const long speedLimit = 50000;
const long speedMin = 100;
const long strokeLimit = 3200;
const long strokeMin = 1800;

float analogSpeed = 0;
float speedValue = 0;

float analogStroke = 0;
float strokeValue = 0;


// Define a stepper and the pins it will use
AccelStepper stepper(1, 14, 16); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{
  Serial.begin(9600);
  // Change these to suit your stepper if you want
  analogSpeed = analogRead(analogSpeedPin);
  speedValue = map(analogSpeed, 0, 1023, speedMin, speedLimit);
//  analogStroke = analogRead(analogStrokePin);
  strokeValue = map(analogSpeed, 0, 1023, strokeMin, strokeLimit);

  stepper.setMaxSpeed(8000);
  stepper.setAcceleration(3000);
  stepper.moveTo(10000);
}

void loop()
{
// If at the end of travel go to the other end
//Serial.println(speedValue);
//Serial.println(stepper.speed());
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();
  stepper.run();


}


void updateSpeedSerial() {
  if (Serial.available()) {
    // get incoming byte:
    myString = Serial.readStringUntil('\n');
    speed = myString.toInt();
    Serial.print("starting ");
    Serial.print(speed);
    Serial.println(" mm/s");
    speedValue = map(speed, 0, 1023, speedMin, speedLimit);
    strokeValue = map(speedValue, 0, 1023, strokeMin, strokeLimit);
    stepper.setMaxSpeed(speedValue);
    stepper.setAcceleration(speedValue * 6);
  }

}

void updateSpeedAnalog() {
  analogSpeed = analogRead(analogSpeedPin);
  speedValue = map(analogSpeed, 0, 1023, speedMin, speedLimit);
//  analogStroke = analogRead(analogStrokePin);
  strokeValue = map(analogStroke, 0, 1023, strokeMin, strokeLimit);
  stepper.setMaxSpeed(speedValue);
  stepper.setAcceleration(speedValue * 60);
}
