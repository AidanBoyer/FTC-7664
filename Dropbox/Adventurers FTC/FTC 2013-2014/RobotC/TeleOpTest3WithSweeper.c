#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Hubs,  S2, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          ScoopLeft,     tmotorNXT, PIDControl, reversed)
#pragma config(Motor,  motorB,          ScoopRight,    tmotorNXT, PIDControl, reversed)
#pragma config(Motor,  motorC,          Sweeper,       tmotorNXT, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_1, RightFrontDrive, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, RightRearDrive, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, LeftFrontDrive, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, LeftRearDrive, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S2_1, ArmUpDown,     tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S2_2, FlagRaise,     tmotorMatrix, openLoop, encoder)
#pragma config(Motor,  mtr_Matrix_S2_3, motorJ,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S2_4, motorK,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_1, servo5,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_2, servo6,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_3, servo7,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_4, servo8,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "joystickDriver.c"

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

	//// add Y offset to the joystick input and scale to 100; handle both positive and negative
	//const float Yoffset = 13;
	//// create a dead zone
	//const int joyDead = 5;

	//float joyY;
	//int scaledY;
	//joyY = (float)i_joyY;
	//// part after "?" is positive joyY; part after ":" handles negative joyY
	//if (abs(joyY)<joyDead)
 // {
 //   scaledY = 0;
 // }
 // else
 // {
 //   	scaledY = (joyY>0) ? (int)((joyY + Yoffset) / (127 + Yoffset) * 100) : (int)((joyY - Yoffset) / (-128 - Yoffset) * -100);
 // }
 // This returned a 100 to -100 with a dead zone
 // return scaledY;
	writeDebugStreamLine("%d",i_joyY);
	return i_joyY;
} // end scaled drive function

void scoopNudge(int moveAngle)
{
		// press button Y (#4) to make scoop go up 15 degrees
		// press button A (#2) to make scoop go down 15 degrees

			int startEncoder = nMotorEncoder[ScoopLeft];
			int destinationEncoder = startEncoder + moveAngle;

			motor[ScoopLeft] = 75 * moveAngle/abs(moveAngle);
			motor[ScoopRight] = 75 * moveAngle/abs(moveAngle);

			ClearTimer(T1);  //Resets the value of Timer "T1" back to zero seconds.
			if(moveAngle > 0)
			{
				while(nMotorEncoder[ScoopLeft] < destinationEncoder && time1[T1] < 500)  // while Motor B is still running:
				{
  				// do not continue
				}
			}
			else
			{
				while(nMotorEncoder[ScoopLeft] > destinationEncoder && time1[T1] < 500)  // while Motor B is still running:
				{
  				// do not continue
				}
			}
			motor[ScoopLeft] = 0;
			motor[ScoopRight] = 0;
} // end scoop nudge function

task main()
{
waitForStart();
	while(true)                        // infinite loop:
	{
		if(joy2Btn(7) != 1)
		{
	 	 	getJoystickSettings(joystick);     // update buttons and joysticks
	  	motor[LeftRearDrive] = scaledJoyDrive(joystick.joy1_y1);  // motorB's powerlevel is set to the left stick's current y-value
	  	motor[RightRearDrive] = scaledJoyDrive(joystick.joy1_y2);
	  	motor[LeftFrontDrive] = scaledJoyDrive(joystick.joy1_y1);
	  	motor[RightFrontDrive] = scaledJoyDrive(joystick.joy1_y2);
			motor[ArmUpDown] = scaledJoyDrive(joystick.joy2_y1);
	  	motor[ScoopLeft] = scaledJoyDrive(joystick.joy2_y2);
			motor[ScoopRight] = scaledJoyDrive(joystick.joy2_y2);
			//writeDebugStreamLine("program running");
			// press button Y to make scoop go up 15 degrees
			//if(joy2Btn(4) == 1 && time1[T2] > 500)  // If Joy1-Button1 is pressed:
		//	{
				//scoopNudge(12);
				//ClearTimer(T2);
		//	} // end if

			// press button A to make scoop go down 15 degrees
		//	if(joy2Btn(2) == 1 && time1[T2] > 500)                  // If Joy1-Button1 is pressed:
		//	{
			//	scoopNudge(-12);
			//	ClearTimer(T2);
		//	} // end if
			if(joy1Btn(6) == 1) motor[Sweeper] = 100;
			else if(joy1Btn(5) == 1) motor[Sweeper] = -100;
			else motor[Sweeper] = 0;

			if(joy2Btn(3) == 1) { PlayTone(4000, 5); }
		} // end if
		else
		{
			getJoystickSettings(joystick);     // update buttons and joysticks
	  	motor[LeftRearDrive] = scaledJoyDrive(joystick.joy2_y1);  // motorB's powerlevel is set to the left stick's current y-value
	  	motor[RightRearDrive] = scaledJoyDrive(joystick.joy2_y2);
	  	motor[LeftFrontDrive] = scaledJoyDrive(joystick.joy2_y1);
	  	motor[RightFrontDrive] = scaledJoyDrive(joystick.joy2_y2);
			motor[ArmUpDown] = scaledJoyDrive(joystick.joy2_y1);

			//writeDebugStreamLine("program running");
			// press button Y to make scoop go up 15 degrees
			//if(joy2Btn(4) == 1 && time1[T2] > 500)  // If Joy1-Button1 is pressed:
		//	{
				//scoopNudge(12);
				//ClearTimer(T2);
		//	} // end if

			// press button A to make scoop go down 15 degrees
		//	if(joy2Btn(2) == 1 && time1[T2] > 500)                  // If Joy1-Button1 is pressed:
		//	{
			//	scoopNudge(-12);
			//	ClearTimer(T2);
		//	} // end if
			if(joy2Btn(6) == 1) motor[Sweeper] = 100;
			else if(joy2Btn(5) == 1) motor[Sweeper] = -100;
			else motor[Sweeper] = 0;

			if(joy2Btn(3) == 1) { PlayTone(4000, 5); }
		}
	} // end while loop
} // end Main
