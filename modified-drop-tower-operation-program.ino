/*
Author: Kaustav Sharma

*/

//objects
#include <Adafruit_MotorShield.h>

#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h> 
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

//Servo objects

Servo servo1;// First servo object 
Servo servo2; // second servo object 
int pos = 0;  // Variable to store the servo position 



 // Set digital pin numbers:
 const int servoPin1 = 9;  // The first servo's pin 
 const int servoPin2 = 10; // The second servo's pin 
 const int button1Pin = 8;  // The button that changes servo direction
 const int button2Pin = 7; // stepper motor button to go up
 // stepper motor button to go down 

//BUTTONS 
 int button1State = 0;  // Variable for reading the pushbutton status
 int direction1State = 0; // Variable for reading direction of the servo
 
 int button2State=0;
 int direction2State=0;
 

 
 void setup() {
   Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
 
servo1.attach(9); // attaches the servo on pin 9 to the servo object 
servo2.attach(10); // attaches the servo on pin 10 to the servo object 


  //LED TURNS ON
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); 

 pinMode(button1Pin, INPUT);   // initialize the servo pushbutton pin as an input
 pinMode(button2Pin, INPUT); 

 }

void loop(){

// SERVO PART 
  
   // read the state of the pushbutton value:
   button1State = digitalRead(button1Pin);

   if (direction1State == 0){
     //The button is pushed
     if (button1State == HIGH) {
       direction1State = 1;// The direction for the servo is clockwise

    // goes from 0 degrees to 180 degrees in steps of 1 degree
       for(pos = 0; pos < 180; pos=pos+1)
      {
        servo2.write(pos); // tell servo to go to position in variable ‘pos’ 
        servo1.write(pos);
         delay(15);  // waits 15ms for the servo to reach the position 
       }
     }

   } 
else if (direction1State == 1) {
     // The button is pushed
     if (button1State == HIGH) {
      direction1State = 0;  // The direction for the servo is anti-clockwise 

       // goes from 180 degrees to 0 degrees in steps of 1 degree 
       for(pos = 180; pos>=1; pos=pos-1)
       {
        servo2.write(pos);  // tell servo to go to position in variable ‘pos’ 
        servo1.write(pos);
         delay(15);  // waits 15ms for the servo to reach the position 
       }
     }
   }

//STEPPER PART

   button2State = digitalRead(button2Pin);

   if (direction2State == 0){
     //The button is pushed
     if (button2State == HIGH) {
       direction2State = 1;// The direction for the servo is clockwise
 myMotor->setSpeed(.1); 
  myMotor->step(1400, FORWARD, INTERLEAVE); 

 
     }
   }

   
else if (direction2State == 1) {
     // The button is pushed
     if (button2State == HIGH) {
      direction2State = 0;  // The direction for the servo is anti-clockwise 
 
 myMotor->setSpeed(10000); 
  myMotor->step(1400, BACKWARD, INTERLEAVE); 
myMotor->setSpeed(1); 
  myMotor->step(100, BACKWARD, INTERLEAVE);
  

     }
}


 
     }

     
   

 
