using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftMotorFront;
extern motor leftMotorBack;
extern motor rightMotorFront;
extern motor rightMotorBack;
extern motor clawMotor;

extern motor_group RightDrive;
extern motor_group LeftDrive;
extern drivetrain DriveTrain;

extern controller user_input;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );