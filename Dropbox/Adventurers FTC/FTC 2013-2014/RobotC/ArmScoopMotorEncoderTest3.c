#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Hubs,  S2, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          ScoopLeft,     tmotorNXT, reversed)
#pragma config(Motor,  motorB,          ScoopRight,    tmotorNXT, reversed)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S2_1, ArmUpDown,     tmotorMatrix, openLoop, encoder)
#pragma config(Motor,  mtr_Matrix_S2_2, motorI,        tmotorMatrix, openLoop)
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

int scaledJoyDrive(int i_joyY)
{
	// add Y offset to the joystick input and scale to 100; handle both positive and negative
	const float Yoffset = 13;
	// create a dead zone
	const int joyDead = 3;

	float joyY;
	int scaledY;
	joyY = (float)i_joyY;
	// part after "?" is positive joyY; part after ":" handles negative joyY
	if (abs(joyY)<joyDead)
  {
    scaledY = 0;
  }
  else
  {
    	scaledY = (joyY>0) ? (int)((joyY + Yoffset) / (127 + Yoffset) * 100) : (int)((joyY - Yoffset) / (-128 - Yoffset) * -100);
  }

	return scaledY;
}

void scoopNudge(int moveAngle)
{
		// press button Y (#4) to make scoop go up 15 degrees
		// press button A (#2) to make scoop go down 15 degrees

			int startTime1;
    	nMotorEncoderTarget[ScoopLeft] = nMotorEncoder[ScoopLeft] + moveAngle;
			nMotorEncoderTarget[ScoopRight] = nMotorEncoder[ScoopRight] + moveAngle;

			motor[ScoopLeft] = 75 * moveAngle/abs(moveAngle);
			motor[ScoopRight] = 75 * moveAngle/abs(moveAngle);

			ClearTimer(T1);  //Resets the value of Timer "T1" back to zero seconds.
			startTime1 = time1[T1];
			while(nMotorRunState[ScoopLeft] != runStateIdle && time1[T1] < 500)  // while Motor B is still running:
			{
  			// do not continue
			}
			motor[ScoopLeft] = 0;
			motor[ScoopRight] = 0;
}

task main()
{

	while(true)                        // infinite loop:
	{
 	 	getJoystickSettings(joystick);     // update buttons and joysticks

		motor[ArmUpDown] = scaledJoyDrive(joystick.joy1_y1);
		motor[ScoopLeft] = scaledJoyDrive(joystick.joy1_y2);
		motor[ScoopRight] = scaledJoyDrive(joystick.joy1_y2);

		// press button Y to make scoop go up 15 degrees
		if(joy1Btn(4) == 1)                  // If Joy1-Button1 is pressed:
			scoopNudge(15);

		// press button A to make scoop go down 15 degrees
		if(joy1Btn(2) == 1)                  // If Joy1-Button1 is pressed:
			scoopNudge(-15);

		}
}