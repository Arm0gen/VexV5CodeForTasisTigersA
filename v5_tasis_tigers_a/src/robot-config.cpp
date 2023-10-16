#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;



// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorFront = motor(PORT1, ratio18_1, false);
motor leftMotorBack = motor(PORT10, ratio18_1, false);
motor rightMotorFront = motor(PORT11, ratio18_1, true); 
motor rightMotorBack = motor(PORT20, ratio18_1, true); 

motor clawMotor = motor(PORT12, ratio36_1, false);

motor_group LeftDrive = motor_group(leftMotorFront, leftMotorBack);
motor_group RightDrive = motor_group(rightMotorFront, rightMotorBack);

drivetrain DriveTrain = drivetrain(LeftDrive, RightDrive);


controller user_input = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}