#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Hubs,  S2, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          RollingGoalGripperRight, tmotorNXT, PIDControl)
#pragma config(Motor,  motorB,          RollingGoalGripperLeft, tmotorNXT, PIDControl)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_1, RightFrontDrive, tmotorMatrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, RightRearDrive, tmotorMatrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, LeftFrontDrive, tmotorMatrix, PIDControl, driveLeft, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, LeftRearDrive, tmotorMatrix, PIDControl, driveLeft, encoder)
#pragma config(Motor,  mtr_Matrix_S2_1, LiftMotorRight, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S2_2, motorI,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S2_3, LiftMotorLeft, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S2_4, GathererMotor, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_1, servo5,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_2, servo6,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_3, servo7,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_4, servo8,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	float AvgNXTbatteryLevel;
	float AvgExtBatteryLevel;
	const float thousand = 1000;
	while(true)
	{
		AvgNXTbatteryLevel = nAvgBatteryLevel;
		AvgNXTbatteryLevel = AvgNXTbatteryLevel / thousand;
		AvgExtBatteryLevel = externalBatteryAvg;
		AvgExtBatteryLevel = AvgExtBatteryLevel / thousand;
		displayCenteredBigTextLine(0, "NXT batt:");
		displayCenteredBigTextLine(2, "%f", AvgNXTbatteryLevel);
		displayCenteredBigTextLine(4, "Ext batt:");
		displayCenteredBigTextLine(6, "%f", AvgExtBatteryLevel);
    wait1Msec(100);
	}
}
