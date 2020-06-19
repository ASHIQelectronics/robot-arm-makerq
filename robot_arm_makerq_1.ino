#include <AccelStepper.h>

int arm1_stepperA_enable_pin = 8;
int arm1_stepperB_enable_pin = 8;
int arm1_stepperC_enable_pin =8;
int home_switch_arm1_stepperA = 9;
int home_switch_arm1_stepperB = 10;
int home_switch_arm1_stepperC = 12;
int allDistanceToGo =1;
long initial_homing =-1;



AccelStepper arm1_stepperA(1, 2, 5);
AccelStepper arm1_stepperB(1, 3, 6);
AccelStepper arm1_stepperC(1, 4, 7);


void setup() {
  Serial.begin(9600);
  pinMode(arm1_stepperA_enable_pin, OUTPUT);
  pinMode(arm1_stepperB_enable_pin, OUTPUT);
  pinMode(arm1_stepperC_enable_pin, OUTPUT);
  pinMode(home_switch_arm1_stepperA, INPUT_PULLUP);
  pinMode(home_switch_arm1_stepperB, INPUT_PULLUP);
  pinMode(home_switch_arm1_stepperC, INPUT_PULLUP);
  
  arm1_stepperA.setEnablePin(arm1_stepperA_enable_pin);
  arm1_stepperB.setEnablePin(arm1_stepperB_enable_pin);
  arm1_stepperC.setEnablePin(arm1_stepperC_enable_pin);
  
  

 arm1_stepperA.setPinsInverted(false,false,true);
 arm1_stepperA.setAcceleration(100);
 arm1_stepperA.setMaxSpeed(100);
 arm1_stepperA.enableOutputs();

 arm1_stepperB.setPinsInverted(false,false,true);
 arm1_stepperB.setAcceleration(100);
 arm1_stepperB.setMaxSpeed(100);
 arm1_stepperB.enableOutputs();

 arm1_stepperC.setPinsInverted(false,false,true);
 arm1_stepperC.setAcceleration(100);
 arm1_stepperC.setMaxSpeed(100);
 arm1_stepperB.enableOutputs();

  while(digitalRead(home_switch_arm1_stepperA)) {
    arm1_stepperA.moveTo(initial_homing);
    initial_homing--;
    arm1_stepperA.run();
    delay(5);
    Serial.println(" homing one  ");
  }

  arm1_stepperA.setCurrentPosition(0);
  arm1_stepperA.setMaxSpeed(100);
  arm1_stepperA.setAcceleration(100);
  initial_homing=1;

  while(!digitalRead(home_switch_arm1_stepperA)) {
    arm1_stepperA.moveTo(initial_homing);
    arm1_stepperA.run();
    initial_homing++;
    delay(5);
    Serial.println("homing two  ");
  }

  arm1_stepperA.setCurrentPosition(0);
  arm1_stepperA.setMaxSpeed(100);
  arm1_stepperA.setAcceleration(100);
  initial_homing=-1; 

 }


void loop(){


  
  Serial.println(" moving motor  ");
  arm1_stepperA.moveTo(230);
  allWaitForPosition();
  arm1_stepperA.moveTo(0);  


  
}


void allWaitForPosition(){
  while(allDistanceToGo != 0) {
    allDistanceToGo = arm1_stepperA.distanceToGo()+ arm1_stepperB.distanceToGo() + arm1_stepperC.distanceToGo();
    arm1_stepperA.run();
    arm1_stepperB.run();
    arm1_stepperC.run();
        
  }
  allDistanceToGo =1;
}
