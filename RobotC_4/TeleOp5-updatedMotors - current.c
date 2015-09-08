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
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
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
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{

	motor[RightFrontDrive] = 0;
  motor[RightRearDrive] = 0;
  motor[LeftFrontDrive] = 0;
  motor[LeftRearDrive] = 0;
  motor[LiftMotorRight] = 0;
	motor[LiftMotorLeft] = 0;
	motor[GathererMotor] = 0;
	motor[ConveyorDrive] = 0;

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

const float scaledJoyConst = 0.0062387;

int scaledJoyDrive(float i_joyY)
{
	float joyValueSign = sgn(i_joyY);
	i_joyY = i_joyY * i_joyY;
	i_joyY = i_joyY - 100;
	i_joyY = i_joyY * scaledJoyConst;

	if(i_joyY > 0)
	{
		i_joyY = i_joyY * joyValueSign;
	}
	else
	{
		i_joyY = 0;
	}
	return i_joyY;
} // end scaled drive function


task main()
{
	initializeRobot();

	float AvgNXTbatteryLevel;
	float AvgExtBatteryLevel;
	const float thousand = 1000;

	int LeftRearDriveValue;
	int RightRearDriveValue;
	int LeftFrontDriveValue;
	int RightFrontDriveValue;
	int ConveyorDriveValue;
	int GathererDriveValue;
	int LiftMotorRightValue;
	int LiftMotorLeftValue;

	int gripTarget = 0;

	bool driveReversed = false;
	bool wasReverseButton = false;

	waitForStart();   // wait for start of tele-op phase

	while(true) // infinite loop:
	{
		getJoystickSettings(joystick); // update buttons and joysticks

		LeftRearDriveValue = scaledJoyDrive(joystick.joy1_y1);
		RightRearDriveValue = scaledJoyDrive(joystick.joy1_y2);
		LeftFrontDriveValue = scaledJoyDrive(joystick.joy1_y1);
		RightFrontDriveValue = scaledJoyDrive(joystick.joy1_y2);
		ConveyorDriveValue = scaledJoyDrive(joystick.joy2_y1);
		GathererDriveValue = scaledJoyDrive(joystick.joy2_y2);


		switch (joystick.joy1_TopHat)
		{
		case 0:
			LeftRearDriveValue =  100;
			RightRearDriveValue = 100;
			LeftFrontDriveValue =  100;
			RightFrontDriveValue = 100;
			break;
		case 4:
			LeftRearDriveValue =  -100;
			RightRearDriveValue = -100;
			LeftFrontDriveValue =  -100;
			RightFrontDriveValue = -100;
			break;
		case 6:
			LeftRearDriveValue =  -50;
			RightRearDriveValue = 50;
			LeftFrontDriveValue =  -50;
			RightFrontDriveValue = 50;
			break;
		case 2:
			LeftRearDriveValue =  50;
			RightRearDriveValue = -50;
			LeftFrontDriveValue =  50;
			RightFrontDriveValue = -50;
			break;
		}



		if(joy1Btn(6) == 0)
		{

			LeftRearDriveValue = LeftRearDriveValue / 2;
			RightRearDriveValue = RightRearDriveValue / 2;
			LeftFrontDriveValue = LeftFrontDriveValue / 2;
			RightFrontDriveValue = RightFrontDriveValue / 2;
		}

		if(joy1Btn(8) == 1)
		{

			LeftRearDriveValue = LeftRearDriveValue / 2;
			RightRearDriveValue = RightRearDriveValue / 2;
			LeftFrontDriveValue = LeftFrontDriveValue / 2;
			RightFrontDriveValue = RightFrontDriveValue / 2;
		}

		if(joy1Btn(5) == 1)
		{
			if(!wasReverseButton)
			{
				if(driveReversed == false) {driveReversed = true;}
				else {driveReversed = false;}
			}
			wasReverseButton = true;
		}
		else
		{
			wasReverseButton = false;
		}

		if(driveReversed == true)
		{
			int RR = RightRearDriveValue;
			int LR = LeftRearDriveValue;
			int RF = RightFrontDriveValue;
			int LF = LeftFrontDriveValue;

			LeftRearDriveValue = RR * -1;
			RightRearDriveValue = LR * -1;
			LeftFrontDriveValue = RF * -1;
			RightFrontDriveValue = LF * -1;
		}

		if(joy2Btn(5) == 1)	{LiftMotorLeftValue = 99;}
		if(joy2Btn(6) == 1) {LiftMotorRightValue = 99;}
		if(joy2Btn(7) == 1)	{LiftMotorLeftValue = -99;}
		if(joy2Btn(8) == 1) {LiftMotorRightValue = -99;}

		if(joy2Btn(5) == 0 && joy2Btn(7) == 0)
		{
			LiftMotorLeftValue = 0;
		}

		if(joy2Btn(6) == 0 && joy2Btn(8) == 0)
		{
			LiftMotorRightValue = 0;
		}

		switch (joystick.joy2_TopHat)
		{
		case 0:
			LiftMotorLeftValue =  100;
			LiftMotorRightValue = 100;

			break;
		case 4:
			LiftMotorLeftValue =  -100;
			LiftMotorRightValue = -100;
			break;
		case 6:
			LiftMotorLeftValue =  -50;
			LiftMotorRightValue = 50;
			break;
		case 2:
			LiftMotorLeftValue =  50;
			LiftMotorRightValue = -50;
			break;
		}

		//Update grip motors
		if(joy1Btn(2) == 1)
		{
			gripTarget = 230;
		}
		if(joy1Btn(4) == 1)
		{
			gripTarget = 0;
		}

		//Maintain grip motors
		if(nMotorEncoder[RollingGoalGripperRight] > gripTarget+1)
		{
			motor[RollingGoalGripperRight] = -25;
		}
		else if(nMotorEncoder[RollingGoalGripperRight] < gripTarget-1)
		{
			motor[RollingGoalGripperRight] = 25;
		}
		else
		{
			motor[RollingGoalGripperRight] = 0;
		}
		if(nMotorEncoder[RollingGoalGripperLeft] > gripTarget+8) //adjusted for asymmetry
		{
			motor[RollingGoalGripperLeft] = -25;
		}
		else if(nMotorEncoder[RollingGoalGripperLeft] < gripTarget+6)
		{
			motor[RollingGoalGripperLeft] = 25;
		}
		else
		{
			motor[RollingGoalGripperLeft] = 0;
		}

		motor[LeftRearDrive] = LeftRearDriveValue;
		motor[RightRearDrive] = RightRearDriveValue;
		motor[LeftFrontDrive] = LeftFrontDriveValue;
		motor[RightFrontDrive] = RightFrontDriveValue;
		motor[GathererMotor] = GathererDriveValue;
		motor[ConveyorDrive] = ConveyorDriveValue;
		motor[LiftMotorRight] = LiftMotorRightValue;
		motor[LiftMotorLeft] = LiftMotorLeftValue;

		AvgNXTbatteryLevel = nAvgBatteryLevel;
		AvgNXTbatteryLevel = AvgNXTbatteryLevel / thousand;
		AvgExtBatteryLevel = externalBatteryAvg;
		AvgExtBatteryLevel = AvgExtBatteryLevel / thousand;
		displayCenteredBigTextLine(0, "NXT batt:");
		displayCenteredBigTextLine(2, "%.3fv", AvgNXTbatteryLevel);
		displayCenteredBigTextLine(4, "Ext batt:");
		displayCenteredBigTextLine(6, "%.3fv", AvgExtBatteryLevel);


	} // end of infinite loop
} // end of task main