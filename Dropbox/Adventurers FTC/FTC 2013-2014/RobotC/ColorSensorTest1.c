#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Hubs,  S2, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S3,     LightSensor,    sensorLightActive)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S2_1, motorH,        tmotorMatrix, openLoop)
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

// from include file
// Define the variables and constants to be used with LineFollowing.
//
const string sFileName = "LightRange.txt";
TFileIOResult nIoResult;
TFileHandle hFileHandle;
int nFileSize = 20;
long tLowLight = 300;
long tHighLight = 600;
//
// Declare the Methods to be performed.
//
float getLightPortion() {
  float result;
  long numerator, denominator;
  numerator = (long) SensorRaw[sensorLightActive] - tLowLight;
  denominator = tHighLight - tLowLight;
  result = (float)  numerator / denominator;
  if(result < 0) { result=0; }
  if(result > 1) { result=1; }
  return result;
}
int getLightPercent() { return 100 * getLightPortion(); }
//

void initLightSensor() {
  SensorType[S3] = sensorLightActive;  // Turn light 'on' if it is currently 'off'
  CloseAllHandles(nIoResult);
  OpenRead(  hFileHandle, nIoResult, sFileName, nFileSize);
  ReadLong(hFileHandle, nIoResult, tLowLight);
  ReadLong(hFileHandle, nIoResult, tHighLight);
  Close(hFileHandle, nIoResult);
}
// end of include

void showSensorValues()
{
		// clearDebugStream();
    writeDebugStreamLine("Light sensor value is %i", SensorValue[LightSensor]);
    writeDebugStreamLine("Light sensor raw is %i", SensorRaw[LightSensor]);
		wait10Msec(100);
}


task main()
{
	while(true)
	{
	}
}