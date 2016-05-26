/*

project: drop tower ride modifications 

Description: turns servos in alternating directions with 1 push button, and 
makes stepper motor go 2 directions with 2 push buttons and has variable speed 
on the second direction 

Author: Kaustav Sharma
DAte
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h> 
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);


 // Set digital pin numbers:
 const int servoPin1 = 9;  // The first servo pin 
 const int servoPin2 = 10; // The second servo pin 
 const int servoButtonPin = 11;  // The push button that changes the servo direstion 
 const int stepperButtonPin=2;

 int sPeed =25; // delay between steps (low=fast)
 int fullRev=200; //the number of steps that make a full rotation
 int distance=0;

//BUTTONS 
 int button1State = 0;  // Variable for reading the pushbutton status
 int directionState = 0;  // Variable for reading direction of the servo

int button2State =0;
int OnOff=0;



 Servo servo1;// First servo object 
 Servo servo2; // second servo object 
 int pos = 0;  // Variable to store the servo position 


 void setup() {
 pinMode (stepperButtonPin,INPUT); // initialize the stepper pushbutton pin as an input
 

  
  servo1.attach(9); // attaches the servo on pin 9 to the servo object 
  servo2.attach(10); // attaches the servo on pin 10 to the servo object 
  pinMode(servoButtonPin, INPUT);  // initialize the servo pushbutton pin as an input
  

  //LED TURNS ON
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   // turns the LED on 
   
   
 }

 void loop(){

  /*
   * 
   * SERVO PART 
   * 
   * 
   * 
   */
  
   // read the state of the pushbutton value:
   button1State = digitalRead(servoButtonPin);

   if (directionState == 0){
     //The button is pushed
     if (button1State == HIGH) {
       directionState = 1;// The direction for the servo is clockwise

    // goes from 0 degrees to 180 degrees in steps of 1 degree
       for(pos = 0; pos < 180; pos=pos+1)
      {
        servo2.write(pos); // tell servo to go to position in variable ‘pos’ 
        servo1.write(pos);
         delay(15);  // waits 15ms for the servo to reach the position 
       }
     }

   } else if (directionState == 1) {
     // The button is pushed
     if (button1State == HIGH) {
      directionState = 0;  // The direction for the servo is anti-clockwise 

       // goes from 180 degrees to 0 degrees in steps of 1 degree 
       for(pos = 180; pos>=1; pos=pos-1)
       {
        servo2.write(pos);  // tell servo to go to position in variable ‘pos’ 
        servo1.write(pos);
         delay(15);  // waits 15ms for the servo to reach the position 
       }
     }
   }

/*
 * STEPPER PART
 * 
 * 
 */

 myMotor->setSpeed(100);  // 10 rpm   
 
 button2State= digitalRead(stepperButtonPin);
if (button2State == LOW) 
{
  OnOff=1; //should run when it is 1
}

while (OnOff ==1)
{
   myMotor->step(100, FORWARD, SINGLE); 
   distance= distance + 1;

   if (distance == fullRev){
    OnOff=0;
   }
}







   
 }
