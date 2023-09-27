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

using namespace vex;

// A global instance of competition
competition Competition;

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

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    int left_x, left_y, right_x, right_y;
    double avg_x, avg_y, speed, angle, left_speed, right_speed,
    curr_speed_left, curr_speed_right, increment_left, increment_right;

    left_x = user_input.Axis3.position();
    left_y = user_input.Axis3.position();
    right_x = user_input.Axis1.position();
    right_y = user_input.Axis2.position();

    // Calculate the average displacement (avg_x, avg_y) of the two joysticks:
    avg_x = (left_x + right_x) / 2;
    avg_y = (left_y + right_y) / 2;

    // Calculate the magnitude (speed) and direction (angle) of the displacement:
    speed = sqrt(pow(avg_x,2) + pow(avg_y, 2));
    angle = atan2(avg_y, avg_x); //not in radians
    angle *= 180.0 / M_PI; // now it is in radians

    // Calculate the individual motor speeds for each wheel:
    left_speed = speed * cos(angle);  // Speed for the left wheels
    right_speed = speed * sin(angle); // Speed for the right wheels

    // Asigning the increments by which the speeds of the motor groups will increase by every gap seconds
    // percent_increment is a value defined in robot-config.cpp and defines by what fraction of left/right_speed will current speed increase every gap seconds
    // gap is defined in robot-config.cpp
    increment_left = left_speed / percent_increment;
    increment_right = right_speed / percent_increment;

    curr_speed_right = curr_speed_left = 0;

    while(curr_speed_left < left_speed){
      curr_speed_right += increment_right;
      curr_speed_left += increment_left;

      wait(gap, seconds);
    }
    
    RightDriveSmart.spinFor(0.2, seconds);
    LeftDriveSmart.spinFor(0.2, seconds);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
