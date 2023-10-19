/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10, D        
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cstdlib>

using namespace vex;

// A global instance of competition
competition Competition;


int direction_horizontal = 0, direction_vertical = 0;
double claw_motor_speed = 1200*1.75;
double sensitivity_part = 8;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void){
  
  DriveTrain.turnFor(55, vex::rotationUnits::deg);
  DriveTrain.driveFor(vex::directionType::rev, 300, vex::distanceUnits::mm, true);
  clawMotor.spinFor(directionType::fwd, 1, sec, claw_motor_speed, dps);
  DriveTrain.driveFor(fwd, 500, vex::distanceUnits::mm, true);
  DriveTrain.turnFor(vex::turnType::right, 10, vex::rotationUnits::deg);
  DriveTrain.driveFor(fwd, 700, vex::distanceUnits::mm, true);
  clawMotor.spinFor(vex::directionType::rev, 0.6, sec, claw_motor_speed/4, dps);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
 

  while (1) {
    double y, x, speed;
  

    y = user_input.Axis2.position();
    x = user_input.Axis1.position();

    speed = user_input.Axis3.position()/100;

    
    switch((int)x){
      case -100 ... -25:
        direction_horizontal = -100;
        break;
      case 25 ... 100:
        direction_horizontal = 100;
        break;
      default:
        direction_horizontal = 0;
        break;
    }

    switch((int)y){
      case -100 ... -25:
        direction_vertical = -100;
        break;
      case 25 ... 100:
        direction_vertical = 100;
        break;
      default:
        direction_vertical = 0;
        break;
    }

    RightDrive.spin(fwd, (direction_vertical-direction_horizontal)*speed, pct);
    LeftDrive.spin(fwd, (direction_vertical+direction_horizontal)*speed, pct);
    
    if(user_input.ButtonA.pressing()){
      clawMotor.spinFor(directionType::fwd, 0.2, sec, claw_motor_speed, dps);
    }else if(user_input.ButtonB.pressing()){
      clawMotor.spinFor(directionType::rev, 0.2, sec, claw_motor_speed, dps);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
    } 
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
  
  usercontrol();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
