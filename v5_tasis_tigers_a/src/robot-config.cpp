#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

int percent_increment = 20;
double gap = 0.01;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

controller user_input = controller(primary);

// VEXcode device constructors

// VEXcode device constructors
motor leftMotorFront = motor(PORT1, ratio18_1, false);
motor leftMotorBack = motor(PORT10, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorFront, leftMotorBack);

motor rightMotorFront = motor(PORT11, ratio18_1, true); 
motor rightMotorBack = motor(PORT20, ratio18_1, true); 
motor_group RightDriveSmart = motor_group(rightMotorFront, rightMotorBack);

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 165, mm, 1);


// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.startCalibration(1);
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}