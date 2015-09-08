#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Hubs,  S2, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          RollingGoalGripperRight, tmotorNXT, PIDControl)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          RollingGoalGripperLeft, tmotorNXT, PIDControl)
#pragma config(Motor,  mtr_Matrix_S1_1, LeftFrontDrive, tmotorMatrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, GathererMotor, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, LeftRearDrive, tmotorMatrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, LiftMotorLeft, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S2_1, RightFrontDrive, tmotorMatrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_Matrix_S2_2, ConveyorDrive, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S2_3, LiftMotorRight, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S2_4, RightRearDrive, tmotorMatrix, PIDControl, driveRight, encoder)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_1, servo5,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_2, servo6,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_3, servo7,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_4, servo8,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot() // sets all the wheel encoder values to 0, just to be sure they aren't something different.
{
	nMotorEncoder[RightFrontDrive] = 0;
  nMotorEncoder[RightRearDrive] = 0;
  nMotorEncoder[LeftFrontDrive] = 0;
  nMotorEncoder[LeftRearDrive] = 0;

  return;
} // end of the "initializeRobot" function


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


const float feetToTravel = 3.8;  // tells how many feet we want the robot to move

const float inchesToTravel = feetToTravel * 12; // takes number of feet and turns it into how many inches

const float wheelDiameter = 3.75;  // tells the diameter of our wheels

const float ticksPerRevolution = 757.12;  // tells how many motor encoder ticks there are in a revolution

const float ticksToTravel = inchesToTravel * ticksPerRevolution / (wheelDiameter * PI); // final number of
	// encoder ticks to travel


double feetToTicks(double feet)
{
	return feet*12*ticksPerRevolution /(wheelDiameter*PI);
}

void moveAllMotors(int power) // sets the power of all the motors to the value passed to this function
{
	motor[RightFrontDrive] = power;
  motor[RightRearDrive] = power;
  motor[LeftFrontDrive] = power;
  motor[LeftRearDrive] = power;
} // end of the "moveAllMotors" function

void accelerateGradually() // Accelerates gradually from 0 to 100% power in 0.5 seconds, to keep wheels from
// slipping and throwing off the encoder values
{
	for(int i = 1; i <= 25; i++)
	{
		moveAllMotors(i * 4);
		wait1Msec(20);
	} // end of the for loop
} // end of the "accelerateGradually" function

void setMotors(int left, int right)
{
	motor[RightFrontDrive] = right;
  motor[RightRearDrive] = right;
  motor[LeftFrontDrive] = left;
  motor[LeftRearDrive] = left;
}

void moveForwardFeet(double feet)
{
	nMotorEncoder[LeftFrontDrive] = 0;
	nMotorEncoder[LeftRearDrive] = 0;
	nMotorEncoder[RightFrontDrive] = 0;
	nMotorEncoder[RightRearDrive] = 0;

	while (((nMotorEncoder[LeftFrontDrive] + nMotorEncoder[LeftRearDrive] + nMotorEncoder[RightFrontDrive]
	+ nMotorEncoder[RightRearDrive]) / 4) < feetToTicks(feet)) // repeat this section of code (do not continue sequential
	// execution) until the average of all four motor values is greater than the target number of ticks to move,
	// calculated from the specified number of feet to move.
  {
  	setMotors(50, 50);
  }
  setMotors(0, 0);
}

void moveBackwardFeet(double feet)
{
	nMotorEncoder[LeftFrontDrive] = 0;
	nMotorEncoder[LeftRearDrive] = 0;
	nMotorEncoder[RightFrontDrive] = 0;
	nMotorEncoder[RightRearDrive] = 0;

	while (((nMotorEncoder[LeftFrontDrive] + nMotorEncoder[LeftRearDrive] + nMotorEncoder[RightFrontDrive]
	+ nMotorEncoder[RightRearDrive]) / 4)*-1 < feetToTicks(feet)) // repeat this section of code (do not continue sequential
	// execution) until the average of all four motor values is greater than the target number of ticks to move,
	// calculated from the specified number of feet to move.
  {
  	setMotors(-25, -25);
  }
  setMotors(0, 0);
}

void turnRight(double feet)
{
	nMotorEncoder[LeftFrontDrive] = 0;
	nMotorEncoder[LeftRearDrive] = 0;
	nMotorEncoder[RightFrontDrive] = 0;
	nMotorEncoder[RightRearDrive] = 0;

	while (((nMotorEncoder[LeftFrontDrive] + nMotorEncoder[LeftRearDrive] - nMotorEncoder[RightFrontDrive]
	- nMotorEncoder[RightRearDrive]) / 4) < feetToTicks(feet)) // repeat this section of code (do not continue sequential
	// execution) until the average of all four motor values is greater than the target number of ticks to move,
	// calculated from the specified number of feet to move.
  {
  	setMotors(50, -50);
  }
  setMotors(0, 0);
}

void turnLeft(double feet)
{
	nMotorEncoder[LeftFrontDrive] = 0;
	nMotorEncoder[LeftRearDrive] = 0;
	nMotorEncoder[RightFrontDrive] = 0;
	nMotorEncoder[RightRearDrive] = 0;

	while (((0-nMotorEncoder[LeftFrontDrive] - nMotorEncoder[LeftRearDrive] + nMotorEncoder[RightFrontDrive]
	+ nMotorEncoder[RightRearDrive]) / 4) < feetToTicks(feet)) // repeat this section of code (do not continue sequential
	// execution) until the average of all four motor values is greater than the target number of ticks to move,
	// calculated from the specified number of feet to move.
  {
  	setMotors(-50, 50);
  }
  setMotors(0, 0);
}

task main() // main task
{

  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase

  //accelerateGradually();

  moveForwardFeet(40);
  moveBackwardFeet(2);
  turnRight(1);
  moveForwardFeet(1.6);
  turnLeft(1);
  moveForwardFeet(3.5);


  /*motor[RightFrontDrive] = 99;
  motor[RightRearDrive] = 99;
  motor[LeftFrontDrive] = 0;
  motor[LeftRearDrive] = 0;

  wait1Msec(600);*/

  moveAllMotors(0); // sets all the motors to 0% power (off)

} // end of main function
