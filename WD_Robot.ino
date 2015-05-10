/*
http://tangiblecode.org

This sketch is part of "building your own" Tangible Code documentation.
http://tangiblecode.org/make/

Load this file onto the 2WD robot

Tested on Arduino Uno

*/

// Main library for controlling the stepper motor,
#include <AccelStepper.h>
#define HALFSTEP 8

// serial direction
#define LEFT 'L'
#define RIGHT 'R'
#define FORWARD 'F'
#define BACK 'B'

char instruction;

// motor pins
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

#define motorPin5  8     // IN1 on the ULN2003 driver 2
#define motorPin6  9     // IN2 on the ULN2003 driver 2
#define motorPin7  10    // IN3 on the ULN2003 driver 2
#define motorPin8  11    // IN4 on the ULN2003 driver 2

//Assign stepper motor variables
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// Variables setup
int turn = 1480;
int straight = 2100;

//Setup boolean to check if the steppers are running
bool leftStepperIsRunning, rightStepperIsRunning;

void setup() {
   Serial.begin(9600);
    stepper1.setMaxSpeed(1000.0);
    stepper1.setAcceleration(500.0);
    stepper2.setMaxSpeed(1000.0);
    stepper2.setAcceleration(500.0);
    // Stepper motors are disabled to minimise power usage whilst stationary.
    stepper1.disableOutputs();
    stepper2.disableOutputs();
} //-- (end setup)--

void loop() { 
  if (Serial.available() > 0) {
    instruction = Serial.read();
  } 
  switch (instruction) {
  case FORWARD: 
    stepper1.moveTo(straight);
    stepper2.moveTo(-straight);
      runBothSteppers(); 
      
    if (stepper1.currentPosition() == straight) {
      stepper1.stop();
      stepper1.setCurrentPosition(1);
      //Serial.println(stepper1.currentPosition());
      
    }
    
    if (stepper2.currentPosition() == -straight) {
      stepper2.stop();
      stepper2.setCurrentPosition(-1);
      //Serial.println(stepper2.currentPosition());
    }
    break;
    delay(100);
 
 case LEFT: 
    stepper1.moveTo(turn);
    stepper2.moveTo(turn);
      runBothSteppers(); 
      
    if (stepper1.currentPosition() == turn) {
      stepper1.stop();
      stepper1.setCurrentPosition(1);
      //Serial.println(stepper1.currentPosition());
    }
    
    if (stepper2.currentPosition() == turn) {
      stepper2.stop();
      stepper2.setCurrentPosition(-1);
      //Serial.println(stepper2.currentPosition());
    }
     break;
     delay(100);

    case RIGHT: 
    stepper1.moveTo(-turn);
    stepper2.moveTo(-turn);
      runBothSteppers(); 
      
    if (stepper1.currentPosition() == -turn) {
      stepper1.stop();
      stepper1.setCurrentPosition(1);
      //Serial.println(stepper1.currentPosition());
    }
    
    if (stepper2.currentPosition() == -turn) {
      stepper2.stop();
      stepper2.setCurrentPosition(-1);
      //Serial.println(stepper2.currentPosition());
    }
     break;
     delay(100);
     
    case BACK: 
    stepper1.moveTo(-straight);
    stepper2.moveTo(straight);
      runBothSteppers(); 
      
    if (stepper1.currentPosition() == -straight) {
      stepper1.stop();
      stepper1.setCurrentPosition(1);
      //Serial.println(stepper1.currentPosition());
    }
    
    if (stepper2.currentPosition() == straight) {
      stepper2.stop();
      stepper2.setCurrentPosition(-1);
      //Serial.println(stepper2.currentPosition());
    }
     break;
     delay(100);
  }
}

//function to initiate the stepper motors and when disable send a message to the control board
void runBothSteppers()
{
  stepper1.enableOutputs();
  stepper2.enableOutputs();

  bool stepper1IsRunning, stepper2IsRunning;

  do
  {
    // Run both steppers
    stepper1IsRunning = stepper1.run();
    stepper2IsRunning = stepper2.run();
  }
  while (stepper1.run() || stepper2.run());

  stepper1.disableOutputs();
  stepper2.disableOutputs();
  Serial.println('G');
}
