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


int angle = 400;
int direction_horizontal = 0, direction_vertical = 0;
turnType turn;
//Measure the chasi length and width before running the code!!!!!!!
double chasi_width = 220, chasi_length = 191; // in MILIMETERS
double wheel_radius = 90; // in MILIMETERS
double distance_wheel_to_center = sqrt(chasi_width*chasi_width+chasi_length*chasi_length);
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

//Converting functions
void convert(double& distance, vex::distanceUnits distance_units){
   switch(distance_units){
    case vex::distanceUnits::cm: distance*=10; break; // transforming cm to mm
    case vex::distanceUnits::in: distance*=0.03937; break; // transfoming in to mm
    case vex::distanceUnits::mm: break; // mm are used as default units of measure, so no change needed
    default: break; // mm are default units of measure
  }
}

void convert(double& time, vex::timeUnits time_units){
  switch(time_units){
      case vex::timeUnits::msec: time/=1000; break; // transformin to sec
      case vex::timeUnits::sec: break; // default units of measure
  }
}
//Converting functions

//Creating functions deadlocking several values of joystick inputs

double deadlock(double range, double& value, int partitions = sensitivity_part){
	double increment = range/partitions;

	for(int i = 0; i < range; i += increment){
		if(std::abs((int)(i-value))<=increment/2)
			value = i;
			return i;
	}
	
	value = 0;
	return 0;
}

//Finished creating deadlocking functions

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

void moveBot(double distance, vex::distanceUnits distance_units = vex::distanceUnits::mm, vex::directionType direction =vex::directionType::fwd, bool wait_for_completition = true){
  convert(distance, distance_units);// see convertation functions, changes tp 
  DriveTrain.driveFor(direction, distance, vex::distanceUnits::mm, wait_for_completition);
 // LeftDrive.spinFor(direction, time, vex::timeUnits::sec, degrees/time, vex::velocityUnits::dps);
 // RightDrive.spinFor(direction, time, vex::timeUnits::sec, degrees/time, vex::velocityUnits::dps);
}

void rotate(double degrees, double time = 100, vex::timeUnits time_units = vex::timeUnits::msec){
  //convert(time, time_units);

  bool is_clockwise = true;

  switch((int)degrees){
    case 180 ... 360: is_clockwise = false; break;
    default: break;
  }

  double velocity = distance_wheel_to_center * degrees / (wheel_radius * time); // refer to the engineering notebook/photo in the chat to see as to why this formula


  if(is_clockwise){ // spining clockwise 
    LeftDrive.spinFor(vex::directionType::rev, degrees, vex::rotationUnits::deg, velocity, vex::velocityUnits::dps, false);
    RightDrive.spinFor(vex::directionType::fwd, degrees, vex::rotationUnits::deg, velocity, vex::velocityUnits::dps, false);
  }else{ // spining counter clockwise
    LeftDrive.spinFor(vex::directionType::fwd, degrees, vex::rotationUnits::deg, velocity, vex::velocityUnits::dps, false);
    RightDrive.spinFor(vex::directionType::rev, degrees, vex::rotationUnits::deg, velocity, vex::velocityUnits::dps, false);
  }

}

void autonomous(void){
  
  DriveTrain.turnFor(55, vex::rotationUnits::deg);
  DriveTrain.driveFor(vex::directionType::rev, 300, vex::distanceUnits::mm, true);
  clawMotor.spinFor(directionType::fwd, 1, sec, claw_motor_speed, dps);
  DriveTrain.driveFor(fwd, 500, vex::distanceUnits::mm, true);
  DriveTrain.turnFor(vex::turnType::right, 10, vex::rotationUnits::deg);
  DriveTrain.driveFor(fwd, 700, vex::distanceUnits::mm, true);
  clawMotor.spinFor(vex::directionType::rev, 0.6, sec, claw_motor_speed/4, dps);
  
  /*
  DriveTrain.driveFor(fwd, 1200, mm);
  DriveTrain.turnFor(vex::turnType::left, 65, vex::rotationUnits::deg);
  clawMotor.spinFor(directionType::fwd, 0.5, sec, claw_motor_speed/2, dps);
  DriveTrain.driveFor(vex::directionType::rev, 250, mm);*/

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

    speed = user_input.Axis3.position();

    
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
    /*
    direction_horizontal = deadlock(200, x);
    direction_vertical = deadlock(200, y);

    direction_horizontal -=100;
    direction_vertical -=100;*/

    RightDrive.spin(fwd, (direction_vertical-direction_horizontal)*speed, pct);
    LeftDrive.spin(fwd, (direction_vertical+direction_horizontal)*speed, pct);

   /* switch((int)x){
      case -100 ... -25:
        DriveTrain.turn(turnType::left,  speed/2, velocityUnits::pct);
        break;
      case 25 ... 100:
        DriveTrain.turn(turnType::right, speed/2, velocityUnits::pct);
        break;
      default:
        break;
    }

    DriveTrain.drive(fwd, speed, velocityUnits::pct);*/
    
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
  autonomous();

  
  usercontrol();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
