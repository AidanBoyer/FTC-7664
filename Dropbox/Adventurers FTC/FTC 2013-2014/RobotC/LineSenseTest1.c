#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     LightSensor,    sensorLightActive)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_1, RightFrontDrive, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, RightRearDrive, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, LeftFrontDrive, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, LeftRearDrive, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void moveAllMotors(int power) // sets the power of all the motors to the value passed to this function
{
	motor[RightFrontDrive] = power;
  motor[RightRearDrive] = power;
  motor[LeftFrontDrive] = power;
  motor[LeftRearDrive] = power;
} // end of the "moveAllMotors" function

task main()
{
	while(SensorValue[LightSensor] < 50)
	{
		moveAllMotors(100);
	}

	moveAllMotors(-100);
	wait10Msec(2);

	while(SensorValue[LightSensor] < 50)
	{
		moveAllMotors(-50);
	}

	moveAllMotors(30);
	wait10Msec(4);
}